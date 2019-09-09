from keras.models import Sequential
from keras.layers import Conv2D, Activation, Dense, Flatten
from keras.datasets import mnist
from keras import backend as K
from keras.losses import categorical_crossentropy
from keras.optimizers import Adadelta
from keras.utils import to_categorical

"""
Data gathering and preprocessing
"""
batch_size = 128
num_classes = 10
epochs = 2

# Keras already comes with the mnist dataset, so we load it into memory
(x_train, y_train), (x_test, y_test) = mnist.load_data()

# Reshape training data for our network
x_train = x_train.reshape(x_train.shape[0], 28, 28, 1)
x_test = x_test.reshape(x_test.shape[0], 28, 28, 1)

x_train = x_train.astype('float32')
x_test = x_test.astype('float32')
x_train /= 255
x_test /= 255

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

# Adds two more convolution layers for the sole sake of adding computational
# complexity to our hardware tests
model.add(Conv2D(16, (4, 4)))
model.add(Activation('relu'))
model.add(Conv2D(16, (4, 4)))
model.add(Activation('relu'))

# Convolutions were being done in a 2D space, but the output vector has only 1
# dimension
model.add(Flatten())

# Adds a final softmax layer
model.add(Dense(10, activation='softmax'))

# Choice of optimizer taken from keras examples
model.compile(loss=categorical_crossentropy, metrics=['accuracy'], optimizer=Adadelta())

model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs, verbose=1, validation_data=(x_test, y_test))

"""
Analyze and export model
"""
score = model.evaluate(x_test, y_test, verbose=0)

model.save("./mnist_model")
print('Test loss:', score[0])
print('Test accuracy:', score[1])
