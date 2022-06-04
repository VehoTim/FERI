import numpy as np
import matplotlib.pyplot as pyplot

def gauss(shape):
    m,n = [(ss-1.)/2. for ss in shape]
    y,x = np.ogrid[-m:m+1,-n:n+1]
    h = np.exp( -(x*x + y*y) / (2.) )
    h[ h < np.finfo(h.dtype).eps*h.max() ] = 0
    sumh = h.sum()
    if sumh != 0:
        h /= sumh
    return h

def decimiraj_sliko(slika, faktor, filter, gauss_sigma=None):
    novH = int(slika.shape[0] / faktor)
    novW = int(slika.shape[1] / faktor)

    decimiranaSlika = np.array(np.zeros((novH, novW, 3)), dtype=int)

    g = gauss((faktor, faktor))

    for x in range(novH):
        for y in range(novW):
            if filter == "mean":
                skupaj = np.array([0,0,0], dtype=int)
                for i in range(faktor):
                    for j in range(faktor):
                        skupaj = skupaj + slika[faktor * x + i][faktor * y + j]
                decimiranaSlika[x][y] = (skupaj / (faktor * faktor))

            elif filter == "gauss":
                skupaj = np.array([0,0,0], dtype=int)
                for i in range(faktor):
                    for j in range(faktor):
                        skupaj = skupaj + slika[faktor * x + i][faktor * y + j] * g[i][j]
                decimiranaSlika[x][y] = skupaj #/ (faktor * faktor)


    return decimiranaSlika

if __name__ == '__main__':
    print("Modul za skaliranje slike!")

    slika = pyplot.imread('./0701_pretvorbe_barvnih_prostorov/slike/lenna.jpg')
    #slika = pyplot.imread('sea-breeze-apartments-pool.jpg')
    novaSlika = decimiraj_sliko(slika, 6, "gauss")

    print(novaSlika.shape)

    pyplot.figure()
    pyplot.imshow(slika)
    pyplot.figure()
    pyplot.imshow(novaSlika)
    pyplot.show()