import numpy as np

def analiziraj_vzorcevalno_mono(signal, dominantna_frekvenca):
    X = np.fft.fft(signal, axis=0)
    n = np.argmax(X)
    Fvz = dominantna_frekvenca / (n / X.shape[0])
    return Fvz

if __name__ == '__main__':
    t = np.arange(0, 1 * 250, 1) / 250
    sig = 1 * np.sin(2 * np.pi * 7 * t + 0 * np.pi)
    sig.shape = (-1, 1)
    print(analiziraj_vzorcevalno_mono(sig, 7))