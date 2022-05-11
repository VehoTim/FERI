import numpy as np
from scipy.io import wavfile

#DTMF tabela za razpoznavanje znakov
DTMF = {(697, 1209): "1", 
        (697, 1336): "2", 
        (697, 1477): "3", 
        (770, 1209): "4", 
        (770, 1336): "5", 
        (770, 1477): "6", 
        (852, 1209): "7", 
        (852, 1336): "8", 
        (852, 1477): "9", 
        (941, 1209): "*", 
        (941, 1336): "0", 
        (941, 1477): "#"}

def analiziraj_dtmf(signal, vzorcevalna_frekvenca, min_cas_ton, min_cas_pavza):

    vec = ""

    #vzorcevalna frekvenca na sekundo * koliko sekund rabimo minimalno = min tonov
    min_tonov = (int)((vzorcevalna_frekvenca * min_cas_ton) / 1000)
    #vzorcevalna frekvenca na sekundo * koliko sekund pavze minimalno = min pavza
    min_pavze = (int)((vzorcevalna_frekvenca * min_cas_pavza) / 1000)

    trenZnak = ""
    #prejsnja = ""
    
    #loopamo skozi signal
    for i in range(0, len(signal), min_tonov):

        #na i do i + min_tonov izvedemo fft ter pridobimo frekvenco
        sigFFT = np.fft.fft(signal[i:i+min_tonov])
        frekv = np.fft.fftfreq(signal[i:i+min_tonov].size, 1 / vzorcevalna_frekvenca)

        #poiscemo nizke frekvence
        spodnjaMin = np.where(frekv > 600)[0][0]
        spodnjaMax = np.where(frekv > 1000)[0][0]

        freq = frekv[spodnjaMin:spodnjaMax]
        amp = abs(sigFFT.real[spodnjaMin:spodnjaMax])

        #najdena spodnja frekvenca
        spodnja = freq[np.where(amp == max(amp))[0][0]]

        #maksimalni odmik tona
        odmik = 10
        trenNaj = 0

        #loopamo skozi vse nizke frekv. in jih primerjamo z naso
        for f in [697, 770, 852, 941] :
            #ce ima boljsi odmik jo shranimo
            if abs(spodnja-f) < odmik :
                odmik = abs(spodnja-f)
                trenNaj = f
        #najdena spodnja
        spodnja = trenNaj
        
        #poiscemo visoke frekvence
        zgornjaMin = np.where(frekv > 1100)[0][0]
        zgornjaMax = np.where(frekv > 1500)[0][0]

        freq = frekv[zgornjaMin:zgornjaMax]
        amp = abs(sigFFT.real[zgornjaMin:zgornjaMax])

        #najdena zgornja frekvenca
        zgornja = freq[np.where(amp == max(amp))[0][0]]

        #maksimalni odmik tona
        odmik = 10
        trenNaj = 0

        #loopamo skozi vse visoke frekv. in jih primerjamo z naso
        for f in [1209, 1336, 1477] :
            #ce je boljsa jo shranimo
            if abs(zgornja-f) < odmik :
                odmik = abs(zgornja-f) 
                trenNaj = f
        #najdena zgornja
        zgornja = trenNaj
        
        #ce sta prazni samo ponastavimo trenZnak
        if spodnja == 0 or zgornja == 0:
            #prejsnja = trenZnak
            trenZnak = ""
        #ce pa se ni bila na trenZnaku jo dodamo
        elif DTMF[(spodnja,zgornja)] != trenZnak:
            #if trenZnak != prejsnja: continue
            #prejsnja = trenZnak
            trenZnak = DTMF[(spodnja,zgornja)]
            vec += trenZnak

    #nas vec spremenimo v vektor da ga bomo vrnili
    vektor = np.chararray((len(vec), 1))

    #vstavljamo v vektor
    pos = 0
    for c in vec:
        vektor[pos] = c
        pos += 1

    return vektor.decode("utf-8")


if __name__ == '__main__':
    print("Modul za DTMF analizo!")
    
    Fvz, sig = wavfile.read('dtmf_123456789_0__min_pulse_0.1_min_pause_0.1.wav')
    #Fvz, sig = wavfile.read('dtmf_124679_min_pulse_0.1_min_pause_0.1.wav')
    #Fvz, sig = wavfile.read('dtmf_123_min_pulse_0.2_min_pause_0.1_noise_low.wav')
    #Fvz, sig = wavfile.read('dtmf_123_min_pulse_0.2_min_pause_0.1_noise_med.wav')
    #Fvz, sig = wavfile.read('dtmf_123_min_pulse_0.2_min_pause_0.1_noise_high.wav')
    vec = analiziraj_dtmf(sig,Fvz, 100, 100)

    print(vec)