import numpy as np
from scipy import signal as sig
import math
from scipy.io import wavfile
    
DTMF = np.array([["1", "2", "3"], 
                ["4", "5", "6"], 
                ["7", "8", "9"], 
                ["*", "0", "#"]])

def najdi_vrednost(vec, vrednost):
    index = np.searchsorted(vec, vrednost, side="left")
    if index > 0 and (index == len(vec) or math.fabs(vrednost - vec[index-1]) < math.fabs(vrednost - vec[index])):
        return index-1
    else:
        return index

def analiziraj_dtmf(signal, vzorcevalna_frekvenca, min_cas_ton, min_cas_pavza):

    vec = []
    vektor = []
    dolzina_tona = 0
    dolzina_pavze = 0
    st_tonov = []
    st_pavz = []

    velikost_okna = ((int)(2**(int((vzorcevalna_frekvenca*(min_cas_ton/4))*0.001)-1))).bit_length()


    f, t, TFD = sig.spectrogram(signal, vzorcevalna_frekvenca, window=sig.windows.hamming(velikost_okna), nperseg=abs(velikost_okna), noverlap=int(velikost_okna*0.8))

    najdene = np.array([najdi_vrednost(f, 697),
                        najdi_vrednost(f, 770),
                        najdi_vrednost(f, 852),
                        najdi_vrednost(f, 941),
                        najdi_vrednost(f, 1209),
                        najdi_vrednost(f, 1336),
                        najdi_vrednost(f, 1477)])
                            
    pomembne = TFD[najdene,0:]
    spodnja = pomembne[0:4,0:]
    zgornja = pomembne[4:,0:]

    prestop = t[1] - t[0]

    povprecje = np.average(pomembne) * 0.75
    pomembne[pomembne < povprecje] = np.nan

    povprecje = np.nanmean(pomembne) * 0.4
    pomembne[np.isnan(pomembne)] = 0
    pomembne[pomembne < povprecje] = 0

    for i in range(t.size):
        i_spodnje = spodnja[0:,i].argmax()
        i_zgornje = zgornja[0:,i].argmax()

        if(np.amax(spodnja[0:,i]) != 0 or np.amax(zgornja[0:,i]) != 0):

            vektor.append(DTMF[i_spodnje,i_zgornje])
            dolzina_tona += prestop

            if(i == t.size-1):
                break

            if(np.amax(spodnja[0:,i+1]) == 0 and np.amax(zgornja[0:,i+1]) == 0):
                c = max(set(vektor), key=vektor.count)
                vec.append(c)
                vektor.clear()
                st_tonov.append(dolzina_tona)
                dolzina_tona = prestop
        else:
            dolzina_pavze += prestop

            if(i == t.size-1):
                break

            if(np.amax(spodnja[0:,i+1]) != 0 or np.amax(zgornja[0:,i+1]) != 0):
                st_pavz.append(dolzina_pavze)
                dolzina_pavze = prestop

    min_cas_pavza = min_cas_pavza*0.0009
    min_cas_ton = min_cas_ton*0.0009

    i = 0
    n = len(vec)-1
    for c in vec[:]:
        if(i == n and st_tonov[i] >= min_cas_ton):
            continue
        if(st_tonov[i] < min_cas_ton or st_pavz[i] < min_cas_pavza):
            vec.remove(c)
        i += 1

    return (np.array(vec, dtype="<U1")).reshape([-1,1])

if __name__ == '__main__':
    print("Modul za DTMF analizo!")
    Fvz, signal = wavfile.read("dtmf_123456789_0__min_pulse_0.1_min_pause_0.1.wav")
    vec = analiziraj_dtmf(signal, Fvz, 100, 100) # v ms podano

    print(vec)