from keras.models import load_model
import numpy as np

# Brings in trained model, with the architecture and optimizers included
model = load_model('mnist_model.h5')

# Saves only the weights - preexisting knowledge of architecture is needed to
# load properly, but saves disk space 
# TODO Commented out due to redundancy; delete if saving weights is not
# sufficient to reconstruct model in CMSIS
# model.save_weights('mnist_weights.h5')    

# Note that ARM uses a Q-based format instead of traditional float32's to store
# floating point numbers

def weights_to_header(filepath, model):
    """
    Generates a header file compatible with CMSIS at the given filepath, using
    the given model's weights
    """
    layer = model.layers[0]
    print(layer.get_weights().shape)

weights_to_header("./test_weights.h", model)

