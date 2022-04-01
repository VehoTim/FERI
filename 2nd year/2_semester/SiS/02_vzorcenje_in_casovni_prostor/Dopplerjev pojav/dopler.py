import numpy as np
import matplotlib.pyplot as plt

def interpolation(vektor, times, vektor_fvz):

    k = np.arange(0, len(vektor), 1) - times * vektor_fvz

    kf = np.floor(k).astype(int) 

    return ( (1.0-k+kf) * vektor[kf] + (k-kf) * vektor[kf+1] ) * (kf >= 0)

def dopler_efekt_mono(vektor, vektor_fvz, zacetna_oddaljenost, hitrost):

    s = int(vektor_fvz * ((zacetna_oddaljenost * 2) / hitrost))
    t = np.arange(s) / vektor_fvz

    vektor = np.sin(2.0 * np.pi * 2000 * t)

    x = t * hitrost
    x -= x.max() / 2
    y = np.zeros(s)
    z = 100.0 * np.ones(s)

    posSource = np.vstack((x,y,z)).T
    posReceiver = np.zeros(3)

    dolzina = np.linalg.norm((posSource - posReceiver), axis=-1)
    
    tmp = interpolation(vektor, (dolzina / 343.0), vektor_fvz)

    tmp = np.reshape(tmp, (-1,1))


    return tmp / np.max(np.abs(tmp))

    #while(len(vektor) < dolzina_novega_vektorja): 
        #vektor = np.array((*vektor, *vektor))

    #tmp = vektor[:dolzina_novega_vektorja]

    #tmp[:dolzina_novega_vektorja // 2] = tmp[:dolzina_novega_vektorja // 2] * (343.0 / (343.0 - hitrost))
    
    #tmp[dolzina_novega_vektorja + 1 // 2:] = tmp[dolzina_novega_vektorja + 1 // 2:] * (343.0 / (343.0 + hitrost))


    #tmp = tmp / np.abs(np.max(tmp))

    #return np.reshape(tmp, (-1, 1))


if __name__ == '__main__':
    import sounddevice as sd

    times = np.arange(int(44100.0*2.0)) / 44100.0

    signal = np.sin(2.0*np.pi*2000.0*times)

    #sd.play(signal, 44100.0)
    
    #sd.wait()
    
    plt.plot(signal)
    plt.show()

    novSignal = dopler_efekt_mono(signal, 44100.0, 70, 50)
    
    #sd.play(novSignal, 44100.0)

    #sd.wait()
    
    plt.plot(novSignal)
    plt.show()

