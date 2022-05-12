#ifndef NALOGA0301_CIRCLE_H
#define NALOGA0301_CIRCLE_H

#include <string>
#include <vector>

using namespace std;

/*
 Ustvarite razred Circle, ki naj ima:

privatno instančno spremenljivko radius, ki predstavlja polmer kroga,
privatno razredno spremenljivko counter, ki predstavlja števec ustvarjenih objektov tipa Circle,
javni privzeti konstruktor,
javni konstruktor, ki kot argument prejme polmer,
javni kopirni konstrutkor,
destruktor,
javno metodo toString, ki kot string vrne podatke o krogu,
javno razredno metodo printCounter, ki samo izpiše število ustvarjenih krogov,
javno razredno metodo diameter, ki kot argument prejme objekt tipa Circle in vrne izračunan obseg kroga,
javno razredno metodo area, ki kot argument prejme objekt tipa Circle in vrne izračunano ploščino kroga.
Pri izračunu obsega in ploščine kroga obvezno uporabite razred Math ("PI", kvadriranje).
Datoteko Math.h obvezno vključite (include) v datoteko Circle.cpp in ne v Circle.h!
Števec krogov ustrezno ažurirajte.
 */

/*Naloga 0301
1. Naredi generateCircles,printCircles naredite razredne metode razreda Circle in jih
    primerno preimnuj.
*/

class Circle {
private:
    int radius;
    static int counter;
public:
    Circle();
    Circle(int r);
    Circle(Circle &a);
    ~Circle();

    void setRadius(int r);

    string toString() const;

    static void printCounter();

    static double diameter(Circle a);

    static double area(Circle a);

    static vector<Circle*> generateCircles(int noc);

    static void printCircles(vector<Circle*> &circles);
};


#endif //NALOGA0301_CIRCLE_H
