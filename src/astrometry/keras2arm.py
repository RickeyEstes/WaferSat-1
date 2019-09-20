from keras.models import Model
from keras.models import load_model
import enum
import numpy as np

"""
Note: If using as a shell script, writes output to stdout. This can then be piped 
into a header file.
"""

def keras2arm(model):
    """
    Acts as an interpreter between a keras model and the CMSIS neural network
    library. 

    @param model        Reads from this model
    @param filepath     Writes the generated code to this filepath
    """
    for layer in mnist_model.layers:
        wrapper = _LayerWrapper(layer)
        wrapper.convert_weights()
        wrapper.quantize_weights()
        wrapper.print_converted_weights()

    return None

class _LayerWrapper:
    """
    Stores the relevant info from a given keras layer and its ARM counterpart
    """
    def __init__(self, layer):
        """
        @param layer        A layer within a keras model
        """
        # Keeps a copy of the original layer
        self.layer = layer

        # Unique name assigned to layer
        self.layer_name = layer.name.upper()

        # Converted and quantized weights, for ARM
        self.new_weights = []
        self.new_bias = []

        # Number of bits per weight (either 8 or 16)
        self.weight_size = 8

        # Number of decimal bits per image pixel (we recast from 0-255 to 0-1)
        # This may be dependent on the network architecture.
        self.image_q_shift = 8

        # Shifts for fixed point arithmetic (calculated after quantization)
        self.bias_shift = 0
        self.output_shift = 0

        # If convolution:
        #  - (# output channels, height, width, # input channels)
        # If dense:
        #  - (# output channels, # input channels)
        self.data_format = []

    def _has_weights(self):
        """
        Many keras layers do not have any weights (like Flatten, Activation,
        etc.), so it is worthwhile to check if the given layer does
        """
        return len(self.layer.get_weights()) > 0

    def _is_convolution_layer(self):
        return "conv" in self.layer.name

    def _is_dense_layer(self):
        return "dense" in self.layer.name

    def convert_weights(self):
        """
        Populates new_weights by converting the keras weights to a flattened
        array of shape NHWC (Number of Filters, Height, Width, Channels) for
        convolutional layers and NC (# output channels, # input channels) 
        for dense layers
        """
        if not self._has_weights():
            return None

        # Layer parameters stored as (weights, bias)
        params = self.layer.get_weights() 

        weights = params[0]
        bias = params[1]

        if self._is_convolution_layer():
            # TODO Check if data format is some analogue of "channels first" 
            # before converting

            # Transpose layer weights from the HWCN format to NHWC
            self.new_weights = weights.transpose(3,0,1,2)
        
        elif self._is_dense_layer(): 
            # The layer's data format should be channels_last. If the trained
            # model is channels_first, we must reshape
            # TODO Check data format before blindly transposing
            self.new_weights = weights.T

        # Populate data format
        self.data_format = self.new_weights.shape

        # Flatten weights C-Style to export to a 1D array
        self.new_weights = weights.ravel()
        self.new_bias = bias
            
    def quantize_weights(self):
        """
        Converts the layer's weights from float32 to a fixed-point format
        (called q7 by ARM).
        
        @pre                Weights have been converted
        
        @param layer        A keras layer within a model
        @return             A list containing the model weights
        """
        if not self._has_weights():
            return None

        """ Choosing a good q format (# integer bits, # decimal bits) """

        # Get min number of integer bits needed for q conversion (ARM's method)
        min_wt = min(self.new_weights)
        max_wt = max(self.new_weights)
        int_bits = max(0, np.ceil(np.log2(max(abs(min_wt),abs(max_wt)))))
        dec_bits = self.weight_size - int_bits - 1  # (We leave a bit for sign)

        # Use ARM's method to perform the quantization
        self.new_weights = np.round((2**dec_bits)*self.new_weights)

        # Do the same for the bias
        min_bias = min(self.new_bias)
        max_bias = max(self.new_bias)
        int_bias_bits = max(0, np.ceil(np.log2(max(abs(min_wt),abs(max_wt)))))
        dec_bias_bits = self.weight_size - int_bias_bits - 1

        # Use ARM's method to perform the quantization
        self.new_bias = np.round((2**dec_bias_bits)*self.new_bias)

        # Calculating the shift is trivial if we assume the input vector
        # consists of 8-bit integers from (0-255), quantized to an unsigned 
        # UQ.8 format falling in [0,1)
        self.bias_shift = self.image_q_shift + dec_bits - dec_bias_bits

        # TODO This assumes the output precision should always be the same as
        # the input vector. For deeper models this should depend on the needed
        # precision of the next layer instead of being a fixed model.
        self.output_shift = dec_bits

        # TODO Better model accuracy can be achieved if the model were
        # repeatedly evaluated during the quantization process. This will not
        # affect performance during inference, only memory usage at higher
        # resolutions. 
        
        return None

    def _print_parameter(self, param_name, param_value):
        """
        Prints the given parameter as a preprocessor macro
        
        # Example
        _print_parameter("VAL", 1) with layer name "LAYER" generates:
        #define LAYER_VAL = 1

        # Arguments
            param_name: Parameter name (string)
            param_value: Value of the given parameter (int)
        """
        print(f"#define {self.layer_name}_{param_name.upper()} = {param_value}")

        return None

    def _print_convolution_parameters(self):
        """
        @pre                Current layer is a convolution layer
        """
        assert self.layer.rank==2,"Converter currently only supports Conv2D layers"

        # TODO Padding sizes, buffer space for input
        # TODO How does the CMSIS convolution library know the number of pixels
        # in each channel?

        self._print_parameter("INPUT_RANK", self.layer.rank)
        self._print_parameter("INPUT_CHANNELS", self.data_format[-1])
        self._print_parameter("OUTPUT_CHANNELS", self.data_format[0])
        self._print_parameter("KERNEL_X", self.layer.kernel_size[0])
        self._print_parameter("KERNEL_Y", self.layer.kernel_size[1])
        self._print_parameter("STRIDES", self.layer.strides[0])
        return None

    def print_converted_weights(self):
        """
        Writes the layer's weights as a C header file to stdout

        @pre                Weights have been quantized
        """
        if not self._has_weights():
            return None

        # TODO Added to make debugging easier; remove when done
        self.new_weights = self.new_weights[:30]

        # Comma-separated string storing the weights and bias
        weights_str = ','.join(str(int(weight)) for weight in self.new_weights)
        bias_str = ','.join(str(int(bias)) for bias in self.new_bias)

        weights_str = '{'+weights_str+'}'
        bias_str = '{'+bias_str+'}'

        # Printing the preprocessor macros
        print("")
        self._print_parameter("WEIGHTS", weights_str)
        self._print_parameter("BIAS", bias_str)
        self._print_parameter("BIAS_SHIFT", self.bias_shift)
        self._print_parameter("OUTPUT_SHIFT", self.output_shift)

        if self._is_convolution_layer():
            self._print_convolution_parameters()

        return None

if __name__ == "__main__":
    # Test code
    mnist_model = load_model('./MNIST/MNIST_model.h5')

    keras2arm(mnist_model)
