import numpy as np
import random

def generiraj_vektor_nakljucno(stevilo_vzorcev):
    return np.random.uniform(0, 1, (stevilo_vzorcev, 1))

def beri_zvok_mono(pot_do_datoteke):
    from scipy.io import wavfile
    Fs, y = wavfile.read(pot_do_datoteke)

    if(y.ndim == 1):
        vektor = y.reshape((-1, 1))
        return vektor / np.max(np.abs(vektor))
    else:
        #zdruzi
        vektor = np.mean(y, axis=1)
        vektor = vektor.reshape((-1, 1))
        return vektor / np.max(np.abs(vektor))

def beri_zvok_stereo(pot_do_datoteke):
    from scipy.io import wavfile
    Fs, y = wavfile.read(pot_do_datoteke)

    if(y.ndim == 1):
        vektor = np.zeros((y.size,2))
        for n in range(y.size):
            vektor[n][0] = y[n]
            vektor[n][1] = y[n]

        return vektor / np.max(np.abs(vektor))
    else: 
        vektor = y
        vektor = np.reshape(vektor,(-1,2))
        return vektor / np.max(np.abs(vektor))

def normaliziraj(vektor):
    vektor = vektor.astype(float)
    oblika = vektor.shape
    tmp = np.reshape(vektor, (-1))
    tmp = tmp.astype(float)
    maxNorm = 0
    for x in tmp:
        if abs(x) > maxNorm:
            maxNorm = abs(x)

    i = 0
    while i < tmp.size:
        tmp[i] = tmp[i] / maxNorm
        i += 1

    vektor = np.reshape(tmp, oblika)
    vektor = vektor.astype(float)
            
    return vektor

def normaliziraj_vektorsko(vektor):
    return vektor / np.max(np.abs(vektor))

import timeit

def testiraj_cas_izvajanja(vektor):
    start = timeit.default_timer()
    normaliziraj(vektor)
    cas = timeit.default_timer() - start

    start2 = timeit.default_timer()
    normaliziraj_vektorsko(vektor)
    cas2 = timeit.default_timer() - start2
    return np.array([[cas, cas2]])

if __name__ == '__main__':
    print(testiraj_cas_izvajanja(generiraj_vektor_nakljucno(1000000)))