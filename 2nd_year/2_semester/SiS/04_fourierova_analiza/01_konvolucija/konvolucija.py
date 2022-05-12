import numpy as np
from scipy import signal as s
import matplotlib.pyplot as plt


def konv_frekvenca_mono(signal, impulz):
    X = np.fft.fft(signal)
    H = np.fft.fft(impulz)

    Y = s.convolve(X, H)

    y = np.real(np.fft.ifft(Y))

    y = np.reshape(y, (-1, 1))

    return y / np.max(np.abs(y))

def konv_frekvenca_stereo(signal, impulz):
    z = signal.shape[0] + impulz.shape[0] - 1

    X = np.fft.fft(signal, n=z, axis=0)
    H = np.fft.fft(impulz, n=z, axis=0)

    y = np.zeros((z, 2))

    y = np.real(np.fft.ifft(X*H, axis=0))
    #y = np.delete(y,-1,1)

    return y / np.max(np.abs(y))

if __name__ == '__main__':
    x = np.random.rand(10,1)
    x2 = np.random.rand(10,2)
    x = x / np.abs(np.max(x))
    x2 = x2 / np.abs(np.max(x2))

    #plt.plot(x2)
    #plt.show()

    #print("Vzorec x:")
    #print(x)
    #print("-------------------------")
    #print("Vzorec x2:")
    #print(x2)
    #print("-------------------------")
    
    h = np.random.rand(3,1)
    h = h / np.abs(np.max(h))
    h2 = np.random.rand(3,2)
    h2 = h2 / np.abs(np.max(h2))
    
    #print("Vzorec h:")
    #print(h)
    #print("-------------------------")
    #print("Vzorec h2:")
    #print(h2)
    #print("-------------------------")

    r = konv_frekvenca_mono(x,h)
    r2 = konv_frekvenca_stereo(x2,h2)

    
    #plt.plot(r2)
    #plt.show()

    #print(r.shape)
    #print(r2.shape)

    print("Vzorec r:")
    print(r)
    print("-------------------------")
    print("Vzorec r2:")
    print(r2)
    print("-------------------------")