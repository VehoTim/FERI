#ifndef NALOGA0301_MATH_H
#define NALOGA0301_MATH_H

#include "Circle.h"
#include "Trapez.h"

/*
 Ustvarite razred Math, ki naj ima:
privatni privzeti konstruktor,
javno razredno spremenljivko, ki je konstanta in predstavlja matematično vrednost "PI" (3.14159265358979323846),
javno razredno metodo square, ki kot argument prejme število in vrne kvadrat tega števila,
javno razredno metodo max, ki kot argumenta prejme dva objekta tipa Circle in vrne tistega, ki ima večji obseg.
 */

class Math {
private:
    Math();

public:
    static const double PI;

    static double square(int num);

    static Circle maxCircle(Circle &a, Circle &b);

    static Trapez maxTrapez(Trapez &a, Trapez &b);
};


#endif //NALOGA0301_MATH_H
