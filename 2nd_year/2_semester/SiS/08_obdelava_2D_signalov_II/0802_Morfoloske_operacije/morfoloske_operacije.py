import numpy as np
import matplotlib.pyplot as pyplot

import scipy.ndimage as ndimage

def open(slika, jedro):
    tmp = ndimage.binary_erosion(slika, jedro)

    return ndimage.binary_dilation(tmp, jedro)

def close(slika, jedro):
    tmp = ndimage.binary_dilation(slika, jedro)

    return ndimage.binary_erosion(tmp, jedro)


def hit_miss(slika, jedro_hit, jedro_miss):

    AxHit = ndimage.binary_erosion(slika, jedro_hit)

    slika_ = np.copy(slika)

    for i in range(slika.shape[0]):
        for j in range(slika.shape[1]):
            if slika[i][j] == 0:
                slika_[i][j] = 1
            else:
                slika_[i][j] = 0

    AcxMiss = ndimage.binary_erosion(slika_, jedro_miss)

    return np.logical_and(AxHit, AcxMiss)

if __name__ == '__main__':
    print("Modul za demonstracijo morfoloških operacij!")

    '''
    slika = pyplot.imread('F:\FERI\FERI\\2nd_year\\2_semester\SiS\\07_obdelava_2D_signalov\\0701_pretvorbe_barvnih_prostorov\slike\Bikesgray.jpg')
    jedro = np.ones((3,3), np.bool)
    tmp = open(slika, jedro)

    
    pyplot.figure()
    pyplot.imshow(tmp)
    pyplot.show()
    '''

