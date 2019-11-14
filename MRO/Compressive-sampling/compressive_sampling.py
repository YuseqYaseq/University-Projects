import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import scipy.optimize as spopt
import scipy.fftpack as spfft
import scipy.ndimage as spimg
import cvxpy as cvx
import cv2
from pylbfgs import owlqn


def dct2(x):
    return spfft.dct(spfft.dct(x.T, norm='ortho', axis=0).T, norm='ortho', axis=0)


def idct2(x):
    return spfft.idct(spfft.idct(x.T, norm='ortho', axis=0).T, norm='ortho', axis=0)


def create_masks(nx, ny):
    masks = []
    first_10_10_1 = np.zeros((nx, ny))
    first_10_10_1[:10, :10] = 1

    first_50_50_1 = np.zeros((nx, ny))
    first_50_50_1[:50, :50] = 1

    first_100_100_1 = np.zeros((nx, ny))
    first_100_100_1[:100, :100] = 1

    first_10_10_0 = np.ones((nx, ny))
    first_10_10_0[:10, :10] = 0

    first_50_50_0 = np.ones((nx, ny))
    first_50_50_0[:50, :50] = 0

    first_100_100_0 = np.ones((nx, ny))
    first_100_100_0[:100, :100] = 0

    proportionally_to_position = np.zeros((nx, ny))
    for i in range(nx):
        for j in range(ny):
            proportionally_to_position[i, j] = max(1 - 20 * (i+j) / (nx + ny), 0)

    removed_shape = np.ones((nx, ny))
    removed_shape[5:15, 5:15] = 0

    removed_shape_2 = np.ones((nx, ny))
    removed_shape_2[5:30, 5:30] = 0

    masks.append(("Pierwsze 10x10 częstotliwości = 1",first_10_10_1))
    masks.append(("Pierwsze 50x50 częstotliwości = 1", first_50_50_1))
    masks.append(("Pierwsze 100x100 częstotliwości = 1", first_100_100_1))
    masks.append(("Pierwsze 10x10 częstotliwości = 0", first_10_10_0))
    masks.append(("Pierwsze 50x50 częstotliwości = 0", first_50_50_0))
    masks.append(("Pierwsze 100x100 częstotliwości = 0", first_100_100_0))
    masks.append(("Proporcjonalnie do pozycji na obrazie", proportionally_to_position))
    masks.append(("Usunięty kwadrat 5x15, 5x15", removed_shape))
    masks.append(("Usunięty kwadrat 5x30, 5x30", removed_shape_2))

    return masks


def remove_n_pixels(image: np.ndarray, no_of_zeros: int):
    selected_pixels = np.array([0] * no_of_zeros + [1] * (image.size - no_of_zeros))
    np.random.shuffle(selected_pixels)
    selected_pixels = selected_pixels.reshape(image.shape)
    image = np.multiply(image, selected_pixels)
    return image


def calc(x, mask):
    freq = dct2(x)
    freq = np.multiply(freq, mask)
    result = idct2(freq)
    return result


def evaluate(x, g, step, nx=1000, ny=1000, ):
    """An in-memory evaluation callback."""

    # we want to return two things: 
    # (1) the norm squared of the residuals, sum((Ax-b).^2), and
    # (2) the gradient 2*A'(Ax-b)

    # expand x columns-first
    print(x.shape)
    x2 = x.reshape((nx, ny)).T

    # Ax is just the inverse 2D dct of x2
    Ax2 = idct2(x2)

    # stack columns and extract samples
    Ax = Ax2.T.flat[ri].reshape(b.shape)

    # calculate the residual Ax-b and its 2-norm squared
    Axb = Ax - b
    fx = np.sum(np.power(Axb, 2))

    # project residual vector (k x 1) onto blank image (ny x nx)
    Axb2 = np.zeros(x2.shape)
    Axb2.T.flat[ri] = Axb # fill columns-first

    # A'(Ax-b) is just the 2D dct of Axb2
    AtAxb2 = 2 * dct2(Axb2)
    AtAxb = AtAxb2.T.reshape(x.shape) # stack columns

    # copy over the gradient vector
    np.copyto(g, AtAxb)

    return fx


nx = 1000
ny = 1000
imgs = ['a.jpg', 'b.jpg', 'c.jpg']
masks = create_masks(nx, ny)


for i, img in enumerate(imgs):
    x = cv2.imread(img)  # read img
    x = cv2.resize(x, (nx, ny))  # scale down
    x = cv2.cvtColor(x, cv2.COLOR_BGR2GRAY)  # to grayscale
    plt.imshow(x)
    plt.title("Oryginalny obraz")
    plt.savefig("imgs//orig" + str(i))

    # HW part 1
    '''for title, mask in masks:
        result = calc(x, mask)
        plt.imshow(result)
        plt.title(title)
        plt.savefig("imgs//" + title + str(i))'''

    # HW part 2
    
    # fractions of the scaled image to randomly sample at
    sample_sizes = (0.1, 0.01)
    
    # for each sample size
    Z = [np.zeros(x.shape, dtype='uint8') for s in sample_sizes]
    masks = [np.zeros(x.shape, dtype='uint8') for s in sample_sizes]
    for j,s in enumerate(sample_sizes):

        # create random sampling index vector
        k = round(nx * ny * s)
        ri = np.random.choice(nx * ny, k, replace=False) # random sample of indices

        # create images of mask (for visualization)
        Xm = 255 * np.ones(x.shape)
        Xm.T.flat[ri] = x.T.flat[ri]
        masks[j][:,:] = Xm

        # take random samples of image, store them in a vector b
        b = x.T.flat[ri].astype(float)

        # perform the L1 minimization in memory
        Xat2 = owlqn(nx*ny, evaluate, None, 5)

        # transform the output back into the spatial domain
        Xat = Xat2.reshape(nx, ny).T # stack columns
        Xa = idct2(Xat)
        Z[j][:,:] = Xa.astype('uint8')
        plt.imshow(Z[j])
        plt.title("Odtwarzanie obrazu z próbki " + str(s * 100) + "% obrazu")
        plt.savefig("imgs//Z" + str(j) + str(i))
        plt.imshow(Xm)
        plt.title("Maska pozostawiająca " + str(s * 100) + "% obrazu")
        plt.savefig("imgs//Mask" + str(j) + str(i))
