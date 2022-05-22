import numpy as np
import matplotlib.pyplot as pyplot

def RGB_hist(slika):
    histogram = np.array(np.zeros((256,3)))

    for x in range(slika.shape[0]):
        for y in range(slika.shape[1]):
            histogram[slika[x][y][0]][0] += 1
            histogram[slika[x][y][1]][1] += 1
            histogram[slika[x][y][2]][2] += 1

    return histogram

def GRAY_hist(slika):
    histogram = np.array(np.zeros((256,1)))

    for x in range(slika.shape[0]):
        for y in range(slika.shape[1]):
            histogram[slika[x][y]][0] += 1

    return histogram



if __name__ == '__main__':
    print("Modul za izdelavo histograma slike!")

    slika = pyplot.imread('./0701_pretvorbe_barvnih_prostorov/slike/sea-breeze-apartments-pool.jpg')

    print(RGB_hist(slika))