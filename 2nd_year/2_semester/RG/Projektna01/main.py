import math
import numpy as np
import random

def izracun3tocke(P1, P2, P3, r1, r2, r3):
    P1_ = np.array([0, 0, 0])
    P2_ = np.array([(P2[0]) - (P1[0]), (P2[1]) - (P1[1]), (P2[2]) - (P1[2])])
    P3_ = np.array([(P3[0]) - (P1[0]), (P3[1]) - (P1[1]), (P3[2]) - (P1[2])])

    V1 = np.subtract(P2_, P1_)
    V2 = np.subtract(P3_, P1_)
    
    Xn = V1/np.linalg.norm(V1)
    Zn = np.cross(V1, V2)
    Zn = Zn / np.linalg.norm(Zn)
    Yn = np.cross(Xn, Zn)

    d = np.dot(Xn, V1)
    i = np.dot(Xn, V2)
    j = np.dot(Yn, V2)

    P2_ = [d, 0, 0]
    P3_ = [i, j, 0]

    #X = (r1na2 - r22 + d2) / 2d
    #Y = (r12 - r32 + i2 + j2) / 2j - (i / j) * X
    #z = √(|r12 - X2 - Y2|)
    X = ((r1 * r1) - (r2 * r2) + (d * d)) / (2 * d)
    Y = ((r1 * r1) - (r3 * r3) + (i * i) + (j * j)) / (2 * j) - (i / j) * X
    z = math.sqrt(abs((r1 * r1) - (X * X) - (Y * Y)))

    K1 = P1 + X * Xn + Y * Yn + z * Zn
    K2 = P1 + X * Xn + Y * Yn - z * Zn

    print(K1)
    print(K2)

def izracun4tocke(P1, P2, P3, P4, r1, r2, r3 ,r4):
    P1_ = np.array([0, 0, 0])
    P2_ = np.array([(P2[0]) - (P1[0]), (P2[1]) - (P1[1]), (P2[2]) - (P1[2])])
    P3_ = np.array([(P3[0]) - (P1[0]), (P3[1]) - (P1[1]), (P3[2]) - (P1[2])])

    V1 = np.subtract(P2_, P1_)
    V2 = np.subtract(P3_, P1_)
    
    Xn = V1/np.linalg.norm(V1)
    Zn = np.cross(V1, V2)
    Zn = Zn / np.linalg.norm(Zn)
    Yn = np.cross(Xn, Zn)


    d = np.dot(Xn, V1)
    i = np.dot(Xn, V2)
    j = np.dot(Yn, V2)

    P2_ = [d, 0, 0]
    P3_ = [i, j, 0]

    a = np.dot((np.subtract(P4, P1)), Xn)
    b = np.dot((np.subtract(P4, P1)), Yn)
    c = np.dot((np.subtract(P4, P1)), Zn)


    
    X = ((r1 * r1) - (r2 * r2) + (d * d)) / (2 * d)
    Y = ((r1 * r1) - (r3 * r3) + (i * i) + (j * j)) / (2 * j) - (i / j) * X
    Z = ((r1 * r1) - (r4 * r4) + (a * a) + (b * b) +
        (c * c)) / (2 * c) - (a / c) * X - (b / c) * Y

    K1 = P1 + X * Xn + Y * Yn + Z * Zn
    return(K1)

    
def izracun4plustocke(tocka1, tocka2, tocka3, tocka4):
    
    P1_ = np.array([0, 0, 0])
    P2_ = np.array([(tocka2[0]) - (tocka1[0]), (tocka2[1]) - (tocka1[1]), (tocka2[2]) - (tocka1[2])])
    P3_ = np.array([(tocka3[0]) - (tocka1[0]), (tocka3[1]) - (tocka1[1]), (tocka3[2]) - (tocka1[2])])

    V1 = np.subtract(P2_, P1_)
    V2 = np.subtract(P3_, P1_)
    
    Xn = V1/np.linalg.norm(V1)
    Zn = np.cross(V1, V2)
    Zn = Zn / np.linalg.norm(Zn)
    Yn = np.cross(Xn, Zn)


    d = np.dot(Xn, V1)
    i = np.dot(Xn, V2)
    j = np.dot(Yn, V2)

    P2_ = [d, 0, 0]
    P3_ = [i, j, 0]

    P1 = np.array(([tocka1[0], tocka1[1], tocka1[2]]))
    P4 = np.array(([tocka4[0], tocka4[1], tocka4[2]]))

    a = np.dot((np.subtract(P4, P1)), Xn)
    b = np.dot((np.subtract(P4, P1)), Yn)
    c = np.dot((np.subtract(P4, P1)), Zn)


    
    X = ((tocka1[3] * tocka1[3]) - (tocka2[3] * tocka2[3]) + (d * d)) / (2 * d)
    Y = ((tocka1[3] * tocka1[3]) - (tocka3[3] * tocka3[3]) + (i * i) + (j * j)) / (2 * j) - (i / j) * X
    Z = ((tocka1[3] * tocka1[3]) - (tocka4[3] * tocka4[3]) + (a * a) + (b * b) + (c * c)) / (2 * c) - (a / c) * X - (b / c) * Y

    K1 = P1 + X * Xn + Y * Yn + Z * Zn
    return(K1)

if __name__ == '__main__':

    st = int(input("Vpisi stevilo tock: "))

    if st == 3:

        P1 = [0, 0, 0]
        P2 = [0, 0, 0]
        P3 = [0, 0, 0]

        r1 = 0
        r2 = 0
        r3 = 0

        #vnos treh pozicij
        P1[0] = int(input("Vpisi x1 za P1: "))
        P1[1] = int(input("Vpisi y1 za P1: "))
        P1[2] = int(input("Vpisi z1 za P1: "))

        P1np = np.array(P1)

        P2[0] = int(input("Vpisi x2 za P2: "))
        P2[1] = int(input("Vpisi y2 za P2: "))
        P2[2] = int(input("Vpisi z2 za P2: "))

        P2np = np.array(P2)

        P3[0] = int(input("Vpisi x3 za P3: "))
        P3[1] = int(input("Vpisi y3 za P3: "))
        P3[2] = int(input("Vpisi z3 za P3: "))
        
        P3np = np.array(P3)

        #izpis teh pozicij
        #print("P1(" + P1[0] + ", " + P1[1] + ", " + P1[2] + ")")
        #print("P2(" + P2[0] + ", " + P2[1] + ", " + P2[2] + ")")
        #print("P3(" + P3[0] + ", " + P3[1] + ", " + P3[2] + ")")
        #print("")
        
        #vnos razdalj
        r1 = float(input("Vpisi razdaljo r1: "))
        r2 = float(input("Vpisi razdaljo r2: "))
        r3 = float(input("Vpisi razdaljo r3: "))

        #izpis razdalj
        #print("r1 = " + r1)
        #print("r2 = " + r2)
        #print("r3 = " + r3)

        izracun3tocke(P1, P2, P3, r1, r2, r3)


    elif st == 4:

        P1 = [0, 0, 0]
        P2 = [0, 0, 0]
        P3 = [0, 0, 0]
        P4 = [0, 0, 0]

        r1 = 0
        r2 = 0
        r3 = 0
        r4 = 0

        #vnos stirih pozicij
        P1[0] = int(input("Vpisi x1 za P1: "))
        P1[1] = int(input("Vpisi y1 za P1: "))
        P1[2] = int(input("Vpisi z1 za P1: "))

        P1np = np.array(P1)

        P2[0] = int(input("Vpisi x2 za P2: "))
        P2[1] = int(input("Vpisi y2 za P2: "))
        P2[2] = int(input("Vpisi z2 za P2: "))

        P2np = np.array(P2)

        P3[0] = int(input("Vpisi x3 za P3: "))
        P3[1] = int(input("Vpisi y3 za P3: "))
        P3[2] = int(input("Vpisi z3 za P3: "))
        
        P3np = np.array(P3)

        P4[0] = int(input("Vpisi x1 za P4: "))
        P4[1] = int(input("Vpisi y1 za P4: "))
        P4[2] = int(input("Vpisi z1 za P4: "))

        P4np = np.array(P4)
        
        #vnos razdalj
        r1 = float(input("Vpisi razdaljo r1: "))
        r2 = float(input("Vpisi razdaljo r2: "))
        r3 = float(input("Vpisi razdaljo r3: "))
        r4 = float(input("Vpisi razdaljo r4: "))

        print(izracun4tocke(P1, P2, P3, P4, r1, r2, r3, r4))
        

    elif st > 4:
        tocke = []
        P = [0, 0, 0]
        for i in range(st):
            #vnos pozicije
            P[0] = int(input("Vpisi x za P" + str(i + 1) + ": "))
            P[1] = int(input("Vpisi y za P" + str(i + 1) + ": "))
            P[2] = int(input("Vpisi z za P" + str(i + 1) + ": "))
            
            #vnos razdalje
            r = float(input("Vpisi razdaljo r" + str(i + 1) + ": "))

            tocke.append((P[0], P[1], P[2], r))

        rezultati = []

        skupaj = np.zeros(3)

        for i in range(st):
            a = random.sample(range(0, st-1), 4)

            rezultati.append(izracun4plustocke(tocke[a[0]], tocke[a[1]], tocke[a[2]], tocke[a[3]]))
            skupaj += rezultati[i]

        resitev = skupaj / st

        print(resitev)

        racRMSE = np.zeros(3)

        for i in range(st):
            racRMSE = racRMSE + (abs(rezultati[i] - resitev) * abs(rezultati[i] - resitev))

        racRMSE = racRMSE / st

        rmse = math.sqrt(racRMSE.mean())
        print("RMSE: ", str(rmse))

        #koncaj to
                   
