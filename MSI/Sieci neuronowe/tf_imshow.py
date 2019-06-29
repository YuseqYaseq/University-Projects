import matplotlib.pyplot as plt
import numpy as np
from keras import backend as k


def show_layer(x, model, layer_to_preview):
    fig, ax = plt.subplots(figsize=(20, 10))
    visualize_layer(x, model, layer_to_preview, ax)
    plt.show()
    plt.close()


def show_layers(x, model, layers_to_preview):
    fig, ax = plt.subplots(nrows=len(layers_to_preview), figsize=(20, 100))
    for i, layer_to_preview in enumerate(layers_to_preview):
        visualize_layer(x, model, layer_to_preview, ax[i])
    plt.savefig("data_plot.png")
    plt.close()


def visualize_layer(x, model, layer_to_preview, ax):
    print("Processing layer {0}".format(layer_to_preview))

    '''size_x = model.layers[layer_to_preview].output_shape[1]
    size_y = model.layers[layer_to_preview].output_shape[2]
    channels = model.layers[layer_to_preview].output_shape[3]
    layer_name = model.layers[layer_to_preview].name'''
    size_x = model.layers[layer_to_preview].output.shape[1]
    size_y = model.layers[layer_to_preview].output.shape[2]
    channels = model.layers[layer_to_preview].output.shape[3]
    layer_name = model.layers[layer_to_preview].name

    width = 16
    rows = (channels - 1) // width + 1
    final_res = np.zeros([size_x * rows, size_y * width])

    for channel in range(channels):
        print("  Processing channel {0}".format(channel))
        i_0 = channel // width * size_x
        j_0 = channel % width * size_y
        activation = get_channel_img_array(x, model, layer_to_preview, channel)
        final_res[i_0:i_0 + size_x, j_0:j_0 + size_y] = activation

    np.savetxt("data_csv/{0}.csv".format(layer_name), final_res, delimiter=",")
    ax.imshow(final_res, cmap="viridis")
    ax.title.set_text(layer_name)


def get_channel_img_array(x, model, layer_number, channel_to_preview):
    get_activations = k.function([model.layers[0].input], [model.layers[layer_number].output])
    activations = get_activations([x])
    return activations[0][0, :, :, channel_to_preview]
