#include <iostream>
#include <vector>
#include <ctime>
#include "Circle.h"
#include "Trapez.h"
#include "Math.h"

/*
 * Zahteve glavnega programa:
    Zapišite funkcijo generateCircles, ki kot argument prejme število krogov, ki jih želimo ustvariti
in vrne vector kazalcev na objekte tipa Circle. Velikost polmera naj bo generirana naključno.
    Zapišite funkcijo printCircles, ki kot argument prejme vector kazalcev na objekte tipa Circle
in podatke o objektih izpiše s pomočjo metode toString.
    Na začetku programa z uporabo razredne metode printCounter izpišite koliko krogov imamo v programu.
    Ustvarite vector kazalcev na objekte tipa Circle in ga z uporabo funkcije generateCircle napolnite
z 10 krogi.
    Z uporabo funkcije printCircles vse kroge v vektorju izpišite.
    Demonstrirajte uporabo razredne metode max iz razreda Math.
    Na koncu (pred vrstico return 0;) še izpišite koliko krogov imamo v programu (uporabite metodo
printCounter)./
 */

int main(){
    srand(time(nullptr));

    Circle::printCounter();

    cout << endl;

    vector<Circle*> circles = Circle::generateCircles(10);

    Circle::printCircles(circles);

    cout << "Max " << Math::maxCircle(*circles[0], *circles[1]).toString() << endl;

    Circle::printCounter();


    for (Circle* item : circles) {
        delete item;
    }

    circles.clear();

    cout << endl;

    Circle::printCounter();

    cout << endl << endl;

    //krogi gor
    //trapezi dol

    Trapez::printCounter();

    cout << endl;

    vector<Trapez*> trapezes = Trapez::generateTrapezes(10);

    Trapez::printCircles(trapezes);

    cout << "Max " << Math::maxTrapez(*trapezes[0], *trapezes[1]).toString() << endl;

    Trapez::printCounter();

    trapezes[10] = new Trapez(25,13,20,10);

    cout << "\nArea: " << Trapez::area(*trapezes[10]) << ", diameter: " << Trapez::diameter(*trapezes[10]);


    for (Trapez* item : trapezes) {
        delete item;
    }

    delete trapezes[10];

    trapezes.clear();

    cout << endl;

    Trapez::printCounter();



    return 0;
}
