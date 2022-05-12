import numpy as np
import matplotlib.pyplot as plt

def konv_cas_mono(signal, impulz):
    N = signal.shape[0]+impulz.shape[0]-1

    y = np.zeros(N)

    for n in range(N):
        for k in range(max(n-impulz.shape[0]+1,0), min(n+1, signal.shape[0])):
            y[n] = (y[n]+signal[k]*impulz[n-k])

    return (y / np.abs(np.max(y))).reshape(-1, 1)

def konv_cas_stereo(signal, impulz):
    N = signal.shape[0]+impulz.shape[0]-1

    y = np.zeros((N, 2))

    for n in range(N):
        for k in range(max(n-impulz.shape[0]+1,0), min(n+1, signal.shape[0])):
            y[n, 0] = (y[n, 0]+signal[k, 0]*impulz[n-k, 0])
            y[n, 1] = (y[n, 1]+signal[k, 1]*impulz[n-k, 1])

    return (y / np.abs(np.max(y))).reshape(-1, 2)

if __name__ == '__main__':
    x = np.random.rand(10,1)
    x2 = np.random.rand(10,2)

    print("Vzorec x:")
    print(x)
    print("-------------------------")
    print("Vzorec x2:")
    print(x2)
    print("-------------------------")
    
    h = np.random.rand(3,1)
    h2 = np.random.rand(3,2)
    
    print("Vzorec h:")
    print(h)
    print("-------------------------")
    print("Vzorec h2:")
    print(h2)
    print("-------------------------")

    r = konv_cas_mono(x,h)
    r2 = konv_cas_stereo(x2,h2)

    print("Vzorec r:")
    print(r)
    print("-------------------------")
    print("Vzorec r2:")
    print(r2)
    print("-------------------------")

    