from keras.models import Sequential
from keras.layers import Conv2D, Activation
from keras.datasets import mnist
from keras import backend as K

"""
Data gathering and preprocessing
"""
batch_size = 128
num_classes = 10
epochs = 12

# Keras already comes with the mnist dataset, so we load it into memory
(x_train, y_train), (x_test, y_test) = mnist.load_data()

"""
Model architecture
"""
model = Sequential()

# First convolution layer takes a 28x28 bitmap and applies 16 filters with a kernel size of 4 pixels
model.add(Conv2D(16, (4, 4), input_shape=(1, 28, 28))) 

# Then applies the relu function to add nonlinearity to the model
model.add(Activation('relu'))

# Adds two more convolution layers for the sole sake of adding computational complexity
model.add(Conv2D(16, (4, 4)))
model.add(Activation('relu'))
model.add(Conv2D(16, (4, 4)))
model.add(Activation('relu'))

# Adds a final softmax layer
model.add(Dense(10, activation='softmax'))

# Choice of optimizer taken from keras examples
model.compile(loss=keras.losses.mean_squared_error, metrics=['accuracy'], optimizer=keras.optimizers.Adadelta())

model.fit(x_train, y_train, batch_size=batch_size, epochs=epochs, verbose=1, validation_data=(x_test, y_test))

score = model.evaluate(x_test, y_test, verbose=0)
print('Test loss:', score[0])
print('Test accuracy:', score[1])
