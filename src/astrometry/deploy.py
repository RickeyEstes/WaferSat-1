import keras2caffe
from keras.models import load_model

# Converts keras model to caffe, then uses ARM's script to generate C code
# This script is meant for quick performance testing; use keras2arm when it is complete

mnist_model = load_model('./MNIST/MNIST_model.h5')

keras2caffe.convert(mnist_model, "./MNIST/MNIST_caffe_net",
    "./MNIST/MNIST_caffe_params")

# When the model is loaded, run the CMSIS quantizer and converter to deploy.

# Note: This kind of coupling is bad practice and should be automated in
#       production

# UPDATE - It seems the CMSIS quantizer is still under development; keras2arm
# will be just as effective
