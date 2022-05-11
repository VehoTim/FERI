import numpy as np
import math
import itertools as it

nadaljuj = True
while(nadaljuj):


    st_tock = int(input("Število točk: "))
    if st_tock == 4:
        # implementacija za 4 točke
        print("Podatki prvega vektorja: ")
        p1x = int(input("X1: "))
        p1y = int(input("Y1: "))
        p1z = int(input("Z1: "))

        l1 = [p1x, p1y, p1z]
        vec1 = np.array(l1)

        print("Podatki drugega vektorja: ")
        p2x = int(input("X2: "))
        p2y = int(input("Y2: "))
        p2z = int(input("Z2: "))

        l2 = [p2x, p2y, p2z]
        v2 = np.array(l2)

        print("Podatki tretjega vektorja: ")
        p3x = int(input("X3: "))
        p3y = int(input("Y3: "))
        p3z = int(input("Z3: "))

        l3 = [p3x, p3y, p3z]
        v3 = np.array(l3)

        print("Podatki cetrtega vektorja: ")
        p4x = int(input("X4: "))
        p4y = int(input("Y4: "))
        p4z = int(input("Z4: "))

        l4 = [p4x, p4y, p4z]
        v4 = np.array(l4)

        print("Razdalje: ")
        r1 = float(input("r1: "))
        r2 = float(input("r2: "))
        r3 = float(input("r3: "))
        r4 = float(input("r4: "))

        P1 = np.subtract(vec1, vec1)
        P2 = np.subtract(v2, vec1)
        P3 = np.subtract(v3, vec1)

        V1 = np.subtract(P2, P1)

        Xn = V1/np.linalg.norm(V1)

        V2 = np.subtract(P3, P1)

        Zn = np.cross(V1, V2)
        Zn = Zn / np.linalg.norm(Zn)
        # Zn je vredu
        # v1 x v2 = (y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2)        3D vektorski produkt

        # np.cross(V1,V2) = V1 x V2  #funkcija za vektorski produkt
        # Yn = Xn x Zn
        Yn = np.cross(Xn, Zn)
        # Yn je okej
        # np.dot = skalarni produkt

        d = np.dot(Xn, V1)
        i = np.dot(Xn, V2)
        j = np.dot(Yn, V2)

        a = np.dot((np.subtract(v4, vec1)), Xn)
        b = np.dot((np.subtract(v4, vec1)), Yn)
        c = np.dot((np.subtract(v4, vec1)), Zn)

        X = (pow(r1, 2) - pow(r2, 2) + pow(d, 2)) / (2 * d)
        Y = (pow(r1, 2) - pow(r3, 2) + pow(i, 2) +
            pow(j, 2)) / (2 * j) - (i / j) * X
        Z = (pow(r1, 2) - pow(r4, 2) + pow(a, 2) + pow(b, 2) +
            pow(c, 2)) / (2 * c) - (a / c) * X - (b / c) * Y

        K1 = vec1 + X*Xn + Y*Yn + Z*Zn
        print(K1)

    elif st_tock == 3:
        # implementacija za 3 točke
        print("Podatki prvega vektorja: ")
        p1x = int(input("X1: "))
        p1y = int(input("Y1: "))
        p1z = int(input("Z1: "))

        l1 = [p1x, p1y, p1z]
        vec1 = np.array(l1)

        print("Podatki drugega vektorja: ")
        p2x = int(input("X2: "))
        p2y = int(input("Y2: "))
        p2z = int(input("Z2: "))

        l2 = [p2x, p2y, p2z]
        v2 = np.array(l2)

        print("Podatki tretjega vektorja: ")
        p3x = int(input("X3: "))
        p3y = int(input("Y3: "))
        p3z = int(input("Z3: "))

        l3 = [p3x, p3y, p3z]
        v3 = np.array(l3)

        print("Razdalje: ")
        r1 = float(input("r1: "))
        r2 = float(input("r2: "))
        r3 = float(input("r3: "))

        P1 = np.subtract(vec1, vec1)
        P2 = np.subtract(v2, vec1)
        P3 = np.subtract(v3, vec1)

        V1 = np.subtract(P2, P1)

        Xn = V1/np.linalg.norm(V1)

        V2 = np.subtract(P3, P1)

        Zn = np.cross(V1, V2)
        Zn = Zn / np.linalg.norm(Zn)
        # Zn je vredu
        # v1 x v2 = (y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2)        3D vektorski produkt

        # np.cross(V1,V2) = V1 x V2  #funkcija za vektorski produkt
        # Yn = Xn x Zn
        Yn = np.cross(Xn, Zn)
        # Yn je okej
        # np.dot = skalarni produkt

        d = np.dot(Xn, V1)
        i = np.dot(Xn, V2)
        j = np.dot(Yn, V2)

        X = (pow(r1, 2) - pow(r2, 2) + pow(d, 2)) / (2 * d)
        Y = (pow(r1, 2) - pow(r3, 2) + pow(i, 2) +
            pow(j, 2)) / (2 * j) - (i / j) * X
        Z = math.sqrt(abs(pow(r1, 2) - pow(X, 2) - pow(Y, 2)))

        K1 = vec1 + X*Xn + Y*Yn + Z*Zn
        K2 = vec1 + X*Xn + Y*Yn - Z*Zn
        print(K1)
        print(K2)

    elif st_tock > 4:
        # implementacija za več kot 4 točke
        #print("Se ne dela")

        arr = []
        for i in range(st_tock):
            x = int(input("X koordinata " + str(i + 1) + ". točke: "))
            y = int(input("Y koordinata " + str(i + 1) + ". točke: "))
            z = int(input("Z koordinata " + str(i + 1) + ". točke: "))
            r = float(input("Razdalja " + str(i + 1) + ". točke: "))

            arr.append((x, y, z, r))

        s = list(it.combinations(arr, 4))
        s.remove(((2,1,0,0.9661), (4,3,0,2.2039), (2,3,4,4.0825), (5,5,2,4.7003)))
        """tukaj za izpis katere kombinacije je izračunalo"""
        # print(s[:4])
        vsota = []
        err = 0
        #print(str(s))
        for i in range(st_tock):
            K1 = 0
            l1 = [s[i][0][0], s[i][0][1], s[i][0][2]]
            r1 = s[i][0][3]
            v1 = np.array(l1)

            l2 = [s[i][1][0], s[i][1][1], s[i][1][2]]
            r2 = s[i][1][3]
            v2 = np.array(l2)

            l3 = [s[i][2][0], s[i][2][1], s[i][2][2]]
            r3 = s[i][2][3]
            v3 = np.array(l3)

            l4 = [s[i][3][0], s[i][3][1], s[i][3][2]]
            r4 = s[i][3][3]
            v4 = np.array(l4)
            #vec1 = np.array(l1)

            P1 = np.subtract(v1, v1)
            P2 = np.subtract(v2, v1)
            P3 = np.subtract(v3, v1)

            V1 = np.subtract(P2, P1)

            Xn = V1/np.linalg.norm(V1)

            V2 = np.subtract(P3, P1)

            Zn = np.cross(V1, V2)
            Zn = Zn / np.linalg.norm(Zn)
            # Zn je vredu
            # v1 x v2 = (y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2)        3D vektorski produkt

            # np.cross(V1,V2) = V1 x V2  #funkcija za vektorski produkt
            # Yn = Xn x Zn
            Yn = np.cross(Xn, Zn)
            # Yn je okej
            # np.dot = skalarni produkt

            d = np.dot(Xn, V1)
            i = np.dot(Xn, V2)
            j = np.dot(Yn, V2)

            a = np.dot((np.subtract(v4, v1)), Xn)
            b = np.dot((np.subtract(v4, v1)), Yn)
            c = np.dot((np.subtract(v4, v1)), Zn)

            X = (pow(r1, 2) - pow(r2, 2) + pow(d, 2)) / (2 * d)
            Y = (pow(r1, 2) - pow(r3, 2) + pow(i, 2) +
                pow(j, 2)) / (2 * j) - (i / j) * X
            Z = (pow(r1, 2) - pow(r4, 2) + pow(a, 2) + pow(b, 2) +
                pow(c, 2)) / (2 * c) - (a / c) * X - (b / c) * Y

            K1 = v1 + X*Xn + Y*Yn + Z*Zn            
            vsota.append((K1))

        #print(str(vsota))
        konec = (sum(vsota) / len(vsota))
        print(str(konec))
        konec = np.array(konec)
        vsota = np.array(vsota)
        mse = np.square(np.subtract(vsota,konec)).mean()
        rmse = math.sqrt(mse)
        print("RMSE: ", str(rmse))
    rez = input("Zelite nadaljevati (y/n)? ")
    
    if(rez == str.lower("y")):
        nadaljuj = True
    else:
        nadaljuj = False