The python files in this directory are used to train neural networks on an external system on the ground with high
compute power. The models' weights are then exported to weights.h for efficient deployment on the spacecraft. 

MNIST - Trains a simple classifier on the MNIST dataset (a set of 10000 32x32 handwritten images). 
    - Note: We are interested in measuring computational performance, not model accuracy. Therefore, the model may be
      trained quickly on a CPU to get desired results. To test, we can use randomly generated bitmaps in memory as our
      "images"
