from keras.models import Sequential
from keras.layers import Conv2D, Activation, Dense, Flatten
from keras.datasets import mnist
from keras.losses import categorical_crossentropy
from keras.optimizers import Adadelta
from keras.utils import to_categorical

"""
Generates a simple keras model trained to do image classification using the
MNIST dataset. That model can then be used for hardware testing computational
performance on the STM32
"""

"""
Data gathering and preprocessing
"""
batch_size = 128
num_classes = 10
epochs = 2

# Keras already comes with the mnist dataset, so we load it into memory
(x_train, y_train), (x_test, y_test) = mnist.load_data()

# Reshape and normalize data to match model architecture
x_train = x_train.reshape(x_train.shape[0], 28, 28, 1)
x_test = x_test.reshape(x_test.shape[0], 28, 28, 1)

# TODO Look into quantization-aware training
x_train = x_train.astype('float32')             
x_test = x_test.astype('float32')
x_train /= 255
x_test /= 255

# Reshape validation data to match optimizer
y_train = to_categorical(y_train, 10)
y_test = to_categorical(y_test, 10)

"""
Model architecture
"""
model = Sequential()

# First convolution layer takes a 28x28 bitmap and applies 16 filters with a kernel size of 4 pixels
model.add(Conv2D(16, (4, 4), input_shape=(28, 28, 1))) 

# Then applies the relu function to add nonlinearity to the model
model.add(Activation('relu'))

# Adds two more convolution layers for the sole sake of adding computational complexity
model.add(Conv2D(16, (4, 4)))
model.add(Activation('relu'))
model.add(Conv2D(16, (4, 4)))
model.add(Activation('relu'))

# Flattens Conv2D layers to integrate with output layer
model.add(Flatten())

# Adds a final softmax layer
model.add(Dense(10, activation='softmax'))

# Choice of optimizer taken from keras examples
model.compile(loss=categorical_crossentropy, metrics=['accuracy'], optimizer=Adadelta())

model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs, verbose=1, validation_data=(x_test, y_test))

score = model.evaluate(x_test, y_test, verbose=0)
print('Test loss:', score[0])
print('Test accuracy:', score[1])

model.save('./MNIST_model.h5')
