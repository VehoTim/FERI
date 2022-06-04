import numpy as np
import matplotlib.pyplot as pyplot
#import scipy.ndimage as ndimage
import scipy.signal as signal


def conv_2d(slika, jedro):

    #tmp = np.copy(slika)

    R = signal.convolve2d(slika[:,:,0], jedro, "same")
    G = signal.convolve2d(slika[:,:,1], jedro, "same")
    B = signal.convolve2d(slika[:,:,2], jedro, "same")  

    '''
    #sredinska tocka
    startX = jedro.shape[0] // 2
    startY = jedro.shape[1] // 2

    for i in range(tmp.shape[0]):
        for j in range(tmp.shape[1]):

            #skupajR = 0.0
            #skupajG = 0.0
            #skupajB = 0.0

            skupaj = np.float32([0,0,0])

            dodanih = 0

            for k in range(jedro.shape[0]):
                for l in range(jedro.shape[1]):
                    if(i - startX + k >= 0) and (j - startY + l >= 0) and (i - startX + k < tmp.shape[0]) and (j - startY + l < tmp.shape[1]):
                        skupaj = skupaj + slika[i - startX + k][j - startY + l] * jedro[k][l]
                        
                        #skupajR = skupajR + tmp[i - startX + k][j - startY + l][0] * jedro[k][l][0]
                        #skupajG = skupajG + tmp[i - startX + k][j - startY + l][1] * jedro[k][l][1]
                        #skupajB = skupajB + tmp[i - startX + k][j - startY + l][2] * jedro[k][l][2]
                        dodanih+=1
                    

                    #slika[i + k][j + l] *= jedro[k][l]
            #tmp[i][j][0] = skupajR / dodanih
            #tmp[i][j][1] = skupajG / dodanih
            #tmp[i][j][2] = skupajB / dodanih
            tmp[i][j] = skupaj / dodanih
    '''

    #tmp[:][:][0] = R
    #tmp[:][:][1] = G
    #tmp[:][:][2] = B

    return np.dstack([R, G, B])

def RGB_glajenje(slika, faktor):

    tmp = np.copy(slika)

    #sredinska tocka
    startX = faktor // 2
    startY = faktor // 2

    for i in range(tmp.shape[0]):
        for j in range(tmp.shape[1]):

            skupaj = np.float32([0,0,0])

            dodanih = 0

            for k in range(faktor):
                for l in range(faktor):
                    if(i - startX + k >= 0) and (j - startY + l >= 0) and (i - startX + k < tmp.shape[0]) and (j - startY + l < tmp.shape[1]):
                        skupaj = skupaj + tmp[i - startX + k][j - startY + l]
                        dodanih+=1

            tmp[i][j] = skupaj / dodanih

    return tmp


def RGB_ostrenje(slika, faktor_glajenja, faktor_ostrenja):

    tmp = np.float32(RGB_glajenje(slika, faktor_glajenja))/255


    jedro = np.float32([[0, 0, 0], 
                        [0, 1, 0], 
                        [0, 0, 0]]) + (np.float32([[0, 0, 0], 
                                                   [0, 1, 0], 
                                                   [0, 0, 0]]) - np.float32([[0, 1, 0], 
                                                                             [1, 1, 1], 
                                                                             [0, 1, 0]]) / faktor_ostrenja) * faktor_ostrenja

    '''
    #sredinska tocka
    startX = 3 // 2
    startY = 3 // 2


    for i in range(tmp.shape[0]):
        for j in range(tmp.shape[1]):

            skupaj = np.float32([0,0,0])

            dodanih = 0

            for k in range(3):
                for l in range(3):
                    if(i - startX + k >= 0) and (j - startY + l >= 0) and (i - startX + k < tmp.shape[0]) and (j - startY + l < tmp.shape[1]):
                        skupaj = skupaj + tmp[i - startX + k][j - startY + l] * jedro[k][l]
                        dodanih+=1
                    
            tmp[i][j] = skupaj / dodanih

    return tmp
    '''

    return conv_2d(tmp, jedro)

if __name__ == '__main__':
    print("Modul za demonstracijo lokalnih operacij!")

    '''
    #KONVOLUCIJA
    slika = np.float32(pyplot.imread('F:\FERI\FERI\\2nd_year\\2_semester\SiS\\07_obdelava_2D_signalov\\0701_pretvorbe_barvnih_prostorov\slike\sea-breeze-apartments-pool.jpg'))/255
    jedro2 = np.array([[[1,1,1], [1,1,1], [1,1,1]],
                      [[1,1,1], [1,1,1], [1,1,1]],
                      [[1,1,1], [1,1,1], [1,1,1]]])


    jedro = np.array([[-2, -1, 0],[-1, 1, 1],[0, 1, 2]])

    slika_conv = conv_2d(slika, jedro)

    pyplot.figure()
    pyplot.imshow(slika)
    pyplot.figure()
    pyplot.imshow(slika_conv)
    pyplot.show()

    '''
    '''
    slikaFilter = cv2.filter2D(slika, -1, jedro)
    pyplot.figure()
    pyplot.imshow(slikaFilter)

    pyplot.show()
    '''

    #slikaNova = ndimage.convolve(slika, jedro2)

    
    #pyplot.figure()
    #pyplot.imshow(slikaNova)

    #pyplot.show()


    #GLAJENJE
    '''
    slika = pyplot.imread('F:\FERI\FERI\\2nd_year\\2_semester\SiS\\07_obdelava_2D_signalov\\0701_pretvorbe_barvnih_prostorov\slike\sea-breeze-apartments-pool.jpg')
    
    glajenaSlika = RGB_glajenje(slika, 7)
    pyplot.figure()
    pyplot.imshow(glajenaSlika)
    pyplot.show()
    '''

    #OSTRENJE
    slika = pyplot.imread('F:\FERI\FERI\\2nd_year\\2_semester\SiS\\07_obdelava_2D_signalov\\0701_pretvorbe_barvnih_prostorov\slike\\phone_red.jpg')
    
    glajenaSlika = RGB_ostrenje(slika, 3, 5)
    pyplot.figure()
    pyplot.imshow(slika)
    pyplot.figure()
    pyplot.imshow(glajenaSlika)
    pyplot.show()