from keras.models import Model

def keras2arm(model, filepath):
    """
    Acts as an interpreter between a keras model and the CMSIS neural network
    library. 

    @Param model        Reads from this model
    @Param filepath     Writes the generated code to this filepath
    """
    for layer in model.layers:
        

    return None;

