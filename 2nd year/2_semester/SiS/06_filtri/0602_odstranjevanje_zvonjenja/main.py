from scipy.io import wavfile
from scipy import signal
import numpy as np

Fvz, sig = wavfile.read('himna.wav')
Fvz2, sig2 = wavfile.read('filter.wav')

sig2 = np.mean(sig2, axis=1)
sig2 = sig2.reshape((-1, 1))

filter_order = 5
Wn = np.array([100, 200])/(Fvz/2)

b, a = signal.butter(filter_order, Wn, 'bandpass')

filt_sig = signal.lfilter(sig2, a, sig)

filt_sig = filt_sig / np.max(np.abs(filt_sig))

wavfile.write("zvonjenje.wav", Fvz, filt_sig)