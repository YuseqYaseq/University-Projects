from neur_homework1 import Model
from sklearn.datasets import load_digits
import keras.datasets.mnist as k_mnist
import numpy as np
import matplotlib.pyplot as plt

#60000 x 28 x 28 test images
#10000 x 28 x 28 test_images

path = 'weights'
train = False


def main():

    data = k_mnist.load_data()
    (train_images, train_labels), (test_images, test_labels) = data

    train_images = np.array(train_images).reshape((60000, 1, 28, 28))
    test_images = np.array(test_images).reshape((10000, 1, 28, 28))

    test_images = test_images[:5, :, :, :]
    test_labels = test_labels[:5]

    model = Model()
    model.load_from_file(path)
    if train:
        # train model
        for i in range(5):
            model.forward(train_images, train_labels)
            model.backward()
            print(model.get_result())

        #model.save_to_file(path)

    #predict
    model.forward(test_images, test_labels)
    print(model.get_result())

    for i in range(5):
        # plt.imshow(test_images[i][0])
        # plt.show()
        model.print_heat_map(test_images[i][0], test_labels[i])


if __name__ == "__main__":
    main()
