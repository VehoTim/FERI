import numpy as np
import matplotlib.pyplot as pyplot

#dela

#import cv2

##ta dela isto kot funkcija v cv2
def RGB_v_HSV(slika):

    tmp = np.copy(slika)

    for x in range(tmp.shape[0]):
        for y in range(tmp.shape[1]):
            R = tmp[x][y][0] / 255.0
            G = tmp[x][y][1] / 255.0
            B = tmp[x][y][2] / 255.0

            Cmax = max(R, G, B)
            Cmin = min(R, G, B)
            
            delta = Cmax - Cmin
            
            #mora biti med 0 in 255
            v = Cmax * 255 

            #mora biti med 0 in 255
            if(Cmax == 0):
                s = 0
            else:
                s = (delta / Cmax) * 255

            if(delta == 0):
                h = 0
            elif(Cmax == R):
                h = (60 * ((G - B) / delta)) % 360
                #h = (60 * ((G - B) / delta)) % 180
            elif(Cmax == G):
                h = (60 * ((B - R) / delta) + 120) % 360
                #h = (60 * ((B - R) / delta) + 120) % 180
            elif(Cmax == B):
                h = (60 * ((R - G) / delta) + 240) % 360
                #h = (60 * ((R - G) / delta) + 240) % 180

            #delimo z 2 da dobimo 180 (stopine / 2), ker mora biti med 0 in 180
            tmp[x][y][0] = h / 2
            tmp[x][y][1] = s
            tmp[x][y][2] = v

    return tmp

def HSV_v_RGB(slika):

    tmp = np.copy(slika)

    for x in range(tmp.shape[0]):
        for y in range(tmp.shape[1]):

            h = tmp[x][y][0] * 2
            s = tmp[x][y][1] / 255
            v = tmp[x][y][2] / 255


            C = s * v
            H_ = h / 60
            X = C * (1 - abs(H_ % 2 - 1))

            m = v - C

            if(H_ >= 0 and H_ < 1):
                R1 = C
                G1 = X
                B1 = 0
            elif(H_ >= 1 and H_ < 2):
                R1 = X
                G1 = C
                B1 = 0
            elif(H_ >= 2 and H_ < 3):
                R1 = 0
                G1 = C
                B1 = X
            elif(H_ >= 3 and H_ < 4):
                R1 = 0
                G1 = X
                B1 = C
            elif(H_ >= 4 and H_ < 5):
                R1 = X
                G1 = 0
                B1 = C
            elif(H_ >= 5 and H_ < 6):
                R1 = C
                G1 = 0
                B1 = X
                

            tmp[x][y][0] = (R1 + m) * 255
            tmp[x][y][1] = (G1 + m) * 255
            tmp[x][y][2] = (B1 + m) * 255

    return tmp

def RGB_v_YCbCr(slika):
    
    tmp = np.copy(slika)

    
    for x in range(tmp.shape[0]):
        for y in range(tmp.shape[1]):
            Y_ = (0.299 * tmp[x][y][0]) + (0.587 * tmp[x][y][1]) + (0.114 * tmp[x][y][2])
            Cb = 128 - (0.168736 * tmp[x][y][0]) - (0.331264 * tmp[x][y][1]) + (0.5 * tmp[x][y][2])
            Cr = 128 + (0.5 * tmp[x][y][0]) - (0.418688 * tmp[x][y][1]) - (0.081312 * tmp[x][y][2])

            tmp[x][y][0] = Y_
            tmp[x][y][1] = Cb
            tmp[x][y][2] = Cr
    
    return tmp

def YCbCr_v_RGB(slika):

    tmp = np.copy(slika)
    #tmp = slika.astype(np.float64)
    #tmp[:,:,[1,2]] -= 128
    
    for x in range(tmp.shape[0]):
        for y in range(tmp.shape[1]):
            #R_ = tmp[x][y][0] + 1.402 * (tmp[x][y][2] - 128)
            #G_ = tmp[x][y][0] - 0.344136 * (tmp[x][y][1] - 128) - 0.714136 * (tmp[x][y][2] - 128)
            #B_ = tmp[x][y][0] + 1.772  * (tmp[x][y][1] - 128)

            R_ = min(max(0, round(tmp[x][y][0] + 1.402 * (tmp[x][y][2] - 128))), 255)
            G_ = min(max(0, round(tmp[x][y][0] - 0.3441 * (tmp[x][y][1] - 128) - 0.7141 * (tmp[x][y][2] - 128))), 255)
            B_ = min(max(0, round(tmp[x][y][0] + 1.772  * (tmp[x][y][1] - 128))), 255)

            tmp[x][y][0] = R_
            tmp[x][y][1] = G_
            tmp[x][y][2] = B_
    
    return tmp
    '''
    
    xform = np.array([[1, 0, 1.402], [1, -0.34414, -.71414], [1, 1.772, 0]])
    rgb = slika.astype(np.float64)
    rgb[:,:,[1,2]] -= 128
    rgb = rgb.dot(xform.T)
    np.putmask(rgb, rgb > 255, 255)
    np.putmask(rgb, rgb < 0, 0)
    return np.uint8(rgb)
    '''

if __name__ == '__main__':
    print("Modul za pretvorbo barvnih prostorov!")

    slika = pyplot.imread('slike/sea-breeze-apartments-pool.jpg')

    print(slika.dtype)




    #img = cv2.cvtColor(slika, cv2.COLOR_RGB2HSV)
    
    #pyplot.figure()
    #pyplot.imshow(img)

    slikaHSV = RGB_v_HSV(slika)

    pyplot.figure()
    pyplot.imshow(slikaHSV)

    slikaRGB = HSV_v_RGB(slikaHSV)

    pyplot.figure()
    pyplot.imshow(slikaRGB)

    pyplot.show()

    '''

    slikaYCbCr = RGB_v_YCbCr(slika)

    pyplot.figure()
    pyplot.imshow(slikaYCbCr)

    slikaRGB = YCbCr_v_RGB(slikaYCbCr)

    pyplot.figure()
    pyplot.imshow(slikaRGB)

    pyplot.show()



    img = cv2.cvtColor(slika, cv2.COLOR_RGB2YCR_CB)
    
    pyplot.imshow(img)
    pyplot.show()


    slikaYCbCr = RGB_v_YCbCr(slika)

    
    pyplot.imshow(slikaYCbCr)
    pyplot.show()

    slikaRGB = YCbCr_v_RGB(slikaYCbCr)


    pyplot.imshow(slikaRGB)
    pyplot.show()


    '''