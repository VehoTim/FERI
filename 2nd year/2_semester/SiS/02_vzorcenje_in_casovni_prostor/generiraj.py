import random
import numpy as np
import matplotlib.pyplot as plt

def generiraj_ton_mono(cas, vzorcevalna_frekvenca, bitna_locljivost, frekvenca_tona):

    #minEl = -(pow(2,bitna_locljivost)/2)
    maxEl = (pow(2,bitna_locljivost)/2 - 1)

    #int8 je do 128
    if maxEl < 128:
        tip="int8"
    #int16 je do 32768
    elif maxEl < 32768:
        tip="int16"
    #int32 je do 2147483648
    elif maxEl < 2147483648:
        tip="int32"
    #ostalo je int64
    else:
        tip="int64"
    
    t = np.arange(0, cas * vzorcevalna_frekvenca, 1, dtype=tip) / vzorcevalna_frekvenca

    s = np.sin(2 * np.pi * frekvenca_tona * t)
    
    s = maxEl * s

    vektor = np.zeros((len(s), 1), dtype=tip)
    i = 0
    while i < len(s):
        vektor[i] = s[i]
        i = i + 1
    
    return vektor

if __name__ == '__main__':
    plt.plot(generiraj_ton_mono(1, 10, 8, 5))
    plt.show()