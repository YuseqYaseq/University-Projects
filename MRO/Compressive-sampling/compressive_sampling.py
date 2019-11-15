# -*- coding: utf-8 -*-
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
import scipy.optimize as spopt
import scipy.fftpack as spfft
import scipy.ndimage as spimg
import cvxpy as cvx
import cv2
from pylbfgs import owlqn
from textwrap import wrap


def dct2(x):
    return spfft.dct(spfft.dct(x.T, norm='ortho', axis=0).T, norm='ortho', axis=0)


def idct2(x):
    return spfft.idct(spfft.idct(x.T, norm='ortho', axis=0).T, norm='ortho', axis=0)


def generate_img(path, save_as, nx, ny):
    x = cv2.imread(path)  # read img
    x = cv2.resize(x, (nx, ny))  # scale down
    x = cv2.cvtColor(x, cv2.COLOR_BGR2GRAY)  # to grayscale
    plt.imshow(x)
    plt.title("Oryginalny obraz")
    plt.savefig("imgs//" + save_as)
    plt.close()
    return x


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


def calc(x, mask):
    freq = dct2(x)
    freq = np.multiply(freq, mask)
    result = idct2(freq)
    return result


def task1(masks, x, img_no):
    for title, mask in masks:
        result = calc(x, mask)
        plt.imshow(result)
        plt.title(title)
        plt.savefig("imgs//" + title + str(img_no))


class Evaluator:

    def __init__(self, nx, ny, ri, b):
        self.nx = nx
        self.ny = ny
        self.ri = ri
        self.b = b

    def evaluate(self, x, g, step):
        """An in-memory evaluation callback."""

        # we want to return two things: 
        # (1) the norm squared of the residuals, sum((Ax-b).^2), and
        # (2) the gradient 2*A'(Ax-b)

        # expand x columns-first
        print(x.shape)
        x2 = x.reshape((self.nx, self.ny)).T

        # Ax is just the inverse 2D dct of x2
        Ax2 = idct2(x2)

        # stack columns and extract samples
        Ax = Ax2.T.flat[self.ri].reshape(self.b.shape)

        # calculate the residual Ax-b and its 2-norm squared
        Axb = Ax - self.b
        fx = np.sum(np.power(Axb, 2))

        # project residual vector (k x 1) onto blank image (ny x nx)
        Axb2 = np.zeros(x2.shape)
        Axb2.T.flat[self.ri] = Axb # fill columns-first

        # A'(Ax-b) is just the 2D dct of Axb2
        AtAxb2 = 2 * dct2(Axb2)
        AtAxb = AtAxb2.T.reshape(x.shape) # stack columns

        # copy over the gradient vector
        np.copyto(g, AtAxb)

        return fx


def mask_and_recreate_image(s, img, special_mask:np.s_=None):
    nx, ny = img.shape
    # create random sampling index vector
    k = round(nx * ny * s)
    if special_mask is None:
        ri = np.random.choice(nx * ny, k, replace=False)  # random sample of indices
    else:
        ri = np.arange(nx * ny).reshape((nx, ny))
        ri[special_mask] = -1
        ri.flatten()
        ri = ri[ri != -1]
    # create images of mask (for visualization)
    Xm = 255 * np.ones(img.shape)
    Xm.T.flat[ri] = img.T.flat[ri]
    mask = Xm

    # take random samples of image, store them in a vector b
    b = img.T.flat[ri].astype(float)

    # perform the L1 minimization in memory
    evaluator = Evaluator(nx, ny, ri, b)
    evaluator = Evaluator(nx, ny, ri, b)
    Xat2 = owlqn(nx*ny, evaluator.evaluate, None, 5)

    # transform the output back into the spatial domain
    Xat = Xat2.reshape(nx, ny).T # stack columns
    Xa = idct2(Xat)
    recovered_image = Xa.astype('uint8')
    diff = np.square(np.subtract(recovered_image, img)).mean()
    return recovered_image,  mask, diff


def task2_2(x, sample_sizes, img_no):
    '''
    Wybierzmy losowo k% pikseli z oryginalnej fotografii.
    Odtwórzmy całą fotografię z użyciem CS.
    Obliczmy różnicę między pierwotnym obrazem, a tym uzyskanym po rekonstrukcji.
    Przygotujmy wykres tej różnicy w zależności od k (czyli % dostępnych na starcie pikseli).
    '''
    (nx, ny) = x.shape
    diffs = []
    Z = [np.zeros(x.shape, dtype='uint8') for s in sample_sizes]
    masks = [np.zeros(x.shape, dtype='uint8') for s in sample_sizes]
    for j,s in enumerate(sample_sizes):
        Z[j], masks[j], diff = mask_and_recreate_image(s, x)
        diffs.append(diff)
        plt.imshow(Z[j])
        plt.title("Odtwarzanie obrazu z próbki " + str(s * 100) + "% obrazu")
        plt.savefig("imgs//Z" + str(j) + str(img_no))
        plt.close()
        plt.imshow(masks[j])
        plt.title("Maska pozostawiająca " + str(s * 100) + "% obrazu")
        plt.savefig("imgs//Mask" + str(j) + str(img_no))
        plt.close()
    plt.plot(sample_sizes, diffs, label="Procent samplowanego obrazu")
    plt.legend(loc='best')
    plt.title("Różnica między odtworzonym obrazem a oryginałem")
    plt.savefig("imgs//diff" + str(img_no))
    plt.close()


def task2_3(x, sample_size, no_tries, img_no):
    '''
    Dla wartości k, gdzie błąd jest jeszcze tolerowalnie niewielki powtórz eksperyment wielokrotnie.
    Dla każdego piksela pokaż jaki był średni błąd jego rekonstrukcji (inaczej mówiąc - narysuj heatmapę pokazującą średni błąd w tym miejscu obrazu).
    Z rekonstrukcją których pikseli jest zwykle największy problem?
    '''
    (nx, ny) = x.shape
    diff = np.zeros(x.shape)
    for i in range(no_tries):
        recreated_img, _, _ = mask_and_recreate_image(sample_size, x)
        diff += np.square(np.subtract(recreated_img, x))
    plt.imshow(diff)
    plt.title("Mapa cieplna różnic między oryginałem\na obrazem odzyskanym z próbki " + str(sample_size * 100) + "% obrazu")
    plt.tight_layout()
    plt.savefig("imgs//heatmap" + str(img_no))


def task2_4():
    ''' Zmniejsz startową rozdzielczość fotografii, wykonaj taki sam wykres zależności błędu od k jak dwa punkty wcześniej. Czy coś się zmieniło?'''
    pass


def task2_5():
    '''
    Zmień sposób próbkowania z jednolitego na całej powierzchni na taki, który bardziej koncentruje się na środku (np. w oparciu o rozkład normalny). 
    Jak to wpływa na uzyskiwane rekonstrukcje?
    '''
    pass


def task2_6(x, slice, img_no):
    '''
    Usuń niezbyt duży prostokąt z centrum zdjęcia, użyj wszystkich pozostałych pikseli jako próbek do procedury CS.
    Jak został zrekonstruowany ten usunięty obszar?
    '''
    
    # Copy image not to modify the original
    x = x.copy()
    x[slice] = 0
    plt.imshow(x)
    plt.title("Obraz z usuniętym fragmentem")
    plt.savefig("imgs//hole" + str(img_no))
    plt.close()
    
    recreated_img, _, _ = mask_and_recreate_image(1, x, slice)
    plt.imshow(recreated_img)
    plt.title("Odtworzony obraz")
    plt.savefig("imgs//hole_removed" + str(img_no))
    plt.close()
    
    

def main():
    nx = 1000
    ny = 1000
    imgs = ['a.jpg', 'b.jpg', 'c.jpg']
    masks = create_masks(nx, ny)

    for i, path in enumerate(imgs):
        
        x = generate_img(path, "orig" + str(i), nx, ny)
        #task1(masks, x, i)

        sample_sizes = [0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9]
        #task2_2(x, sample_sizes, i)
        
        sample_size = 0.5
        no_tries = 10
        #task2_3(x, sample_size, no_tries, i)
        
        task2_6(x, np.s_[450:550, 450:550], i)


main()
