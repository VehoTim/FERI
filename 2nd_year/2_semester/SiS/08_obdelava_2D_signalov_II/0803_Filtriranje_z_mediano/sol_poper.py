import numpy as np
import matplotlib.pyplot as pyplot

def sol_poper(slika):

    r = []
    g = []
    b = []
    r_ = np.array(r)
    g_ = np.array(g)
    b_ = np.array(b)

    tmp = np.copy(slika)
    for i in range(slika.shape[0]):
        for j in range(slika.shape[1]):
            dodano = 0
            for x in range(3):
                for y in range(3):
                    if(i - 1 + x >= 0) and (j - 1 + y >= 0) and (i - 1 + x < slika.shape[0]) and (j - 1 + y < slika.shape[1]):
                        r.append(slika[i + x - 1][j + y - 1][0])
                        g.append(slika[i + x - 1][j + y - 1][1])
                        b.append(slika[i + x - 1][j + y - 1][2])

                        dodano += 1

            r_ = np.array(sorted(r))
            g_ = np.array(sorted(g))
            b_ = np.array(sorted(b))

            r.clear()
            b.clear()
            g.clear()

            if dodano % 2 == True:
                tmp[i][j][0] = r_[(dodano // 2)]
                tmp[i][j][1] = g_[(dodano // 2)]
                tmp[i][j][2] = b_[(dodano // 2)]
            else:
                tmp[i][j][0] = ((int)(r_[(dodano // 2)]) + (int)(r_[(dodano // 2 ) + 1])) // 2
                tmp[i][j][0] = ((int)(g_[(dodano // 2)]) + (int)(g_[(dodano // 2 ) + 1])) // 2
                tmp[i][j][0] = ((int)(b_[(dodano // 2)]) + (int)(b_[(dodano // 2 ) + 1])) // 2

    return tmp

if __name__ == '__main__':
    print("Demo sol in poper")

    slika = pyplot.imread('F:\FERI\FERI\\2nd_year\\2_semester\SiS\\07_obdelava_2D_signalov\\0701_pretvorbe_barvnih_prostorov\slike\\download.jpg')
    
    pyplot.figure()
    pyplot.imshow(slika)

    vrnjeno = sol_poper(slika)

    
    pyplot.figure()
    pyplot.imshow(vrnjeno)
    pyplot.show()