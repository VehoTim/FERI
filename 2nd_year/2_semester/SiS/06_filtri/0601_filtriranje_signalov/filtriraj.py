import numpy as np

def filtriraj_mono(signal, b, a):
    if len(a) == 0:
        prvi = a
    else:
        prvi = a[0]
    if(prvi == 0):
        prvi = 1
    y = np.zeros(len(signal))
    for i in range (signal.size):
        sestevek_b = 0

        for j in range (b.size):
            if(i - j >= 0):
                sestevek_b += b[j] * signal[i - j]

        sestevek_a = 0

        if len(a) > 0:  
            for j in range (1, a.size):
                if(i - j >= 0):
                    sestevek_a += a[j] * y[i - j]

        y[i] = (sestevek_b - sestevek_a) / prvi

    return y.reshape(-1,1)


def filtriraj_stereo(signal, b, a):
    if len(a) == 0:
        prvi = a
    else:
        prvi = a[0]
    if(prvi == 0):
        prvi = 1
    y = np.zeros(signal.shape)
    for i in range (signal.shape[0]):
        sestevek_b0 = 0

        for j in range (b.size):
            if(i - j >= 0):
                sestevek_b0 += b[j] * signal[:,0][i - j]

        sestevek_b1 = 0

        for j in range (b.size):
            if(i - j >= 0):
                sestevek_b1 += b[j] * signal[:,1][i - j]

        sestevek_a0 = 0

        if len(a) > 0:  
            for j in range (1, a.size):
                if(i - j >= 0):
                    sestevek_a0 += a[j] * y[:,0][i - j]

                    
        sestevek_a1 = 0

        if len(a) > 0:  
            for j in range (1, a.size):
                if(i - j >= 0):
                    sestevek_a1 += a[j] * y[:,1][i - j]
        

        y[i, 0] = (sestevek_b0 - sestevek_a0) / prvi
        y[i, 1] = (sestevek_b1 - sestevek_a1) / prvi

    return y.reshape(-1,2)

if __name__ == '__main__':
    print("Modul za filtriranje signala!")