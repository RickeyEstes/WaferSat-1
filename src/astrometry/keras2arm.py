from keras.models import Model
from keras.models import load_model
import enum
import numpy as np

"""
Note: If using as a shell script, writes output to stdout. This can then be piped 
into a header file.
"""

def keras2arm(model, filepath):
    """
    Acts as an interpreter between a keras model and the CMSIS neural network
    library. 

    @param model        Reads from this model
    @param filepath     Writes the generated code to this filepath
    """
    
    return None

class _LayerWrapper:
    """
    Stores the relevant info from a given keras layer and its ARM counterpart
    """
    def __init__(self, layer):
        """
        @param layer        A layer within a keras model
        """
        # Number of bits per weight (either 8 or 16)
        self.weight_size = 8

        # Keeps a copy of the original layer
        self.layer = layer

        # Unique name assigned to layer
        self.name = layer.name 

        # Converted and quantized weights, for ARM
        self.new_weights = []
        self.new_bias = []

    def _has_weights(self):
        """
        Many keras layers do not have any weights (like Flatten, Activation,
        etc.), so it is worthwhile to check if the given layer does
        """
        return len(self.layer.get_weights()) > 0

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

        if "dense" in self.layer.name:
            # TODO Check if data format is some analogue of "channels first" before converting
            # Transpose layer weights to the (output, input) shape
            self.new_weights = weights.T
        
        elif "conv" in self.layer.name:
            # The layer's data format should be channels_last. If the trained
            # model is channels_first, we must reshape
            # TODO Reshape instead of throwing an error 
            assert("last" in self.layer.data_format, 
                """ Currently the converter only accepts convolution layers 
                    with the \"channels last\" data format """)

        # Flatten weights C-Style to export to a 1D array
        self.new_weights = weights.flatten('C')
        self.new_bias = bias
            
    def quantize_weights(self):
        """
        Converts the layer's weights from float32 to either an int or q
        format
        
        @pre                new_weights have been converted
        
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

        # TODO Better model accuracy can be achieved if the model were
        # repeatedly evaluated during the quantization process. This will not
        # affect performance during inference, only memory usage at higher
        # resolutions. 

        return None

    def print_converted_weights(self):
        """
        Writes the layer's weights as a C header file to stdout

        @pre                new_weights have been quantized
        """
        if not self._has_weights():
            return None

        # TODO Added to make debugging easier; remove when done
        self.new_weights = self.new_weights[:70]

        # Generated macro name
        weights_name = self.name.upper()

        # Comma-separated string storing the weights
        weights_str = ','.join(str(int(weight)) for weight in self.new_weights)
        print("#define %s = {%s}" % (weights_name, weights_str))

        # TODO Handle bias

        return None

if __name__ == "__main__":
    # Test code
    mnist_model = load_model('./MNIST/MNIST_model.h5')

    for layer in mnist_model.layers:
        wrapper = _LayerWrapper(layer)
        wrapper.convert_weights()
        wrapper.quantize_weights()
        wrapper.print_converted_weights()
