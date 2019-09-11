from keras.models import Model
from keras.models import load_model
import enum

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
            
    def quantize_weights(self):
        """
        Converts the layer's weights from float32 to either an int or q
        format
        
        @pre                new_weights have been converted
        
        @param layer        A keras layer within a model
        @return             A list containing the model weights
        """

        return None

    def print_converted_weights(self):
        """
        Writes the layer's weights as a C header file to stdout
        """
        if not self.has_weights:
            return None

        return None

if __name__ == "__main__":
    # Debugging code
    mnist_model = load_model('./MNIST/MNIST_model.h5')

    for layer in mnist_model.layers:
        wrapper = _LayerWrapper(layer)
        wrapper.print_converted_weights()
