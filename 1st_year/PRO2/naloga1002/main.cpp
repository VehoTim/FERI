#include <iostream>
#include "Date.h"
#include "SmartPointer.h"

int main() {
    /*SmartPointer<Date> date1(new Date(6, 5, 2020)); // s pomočjo pametnega kazalca, dinamično ustvarimo objekt Date
    {
        SmartPointer<Date> date2 = date1;   // na tem mestu naredimo kopijo kazalca date1 in sedaj oba kazalca (date1
        // in date2 kažeta na isti objekt
    }   // na tem mestu se bo klical destruktor pametnega kazalca date2 in pobrisal objekt Date
    std::cout << date1->toString() << std::endl;    // ker sta oba kazalca kazala na isti objekt v pomnilniku,
    // se bo tukaj zgodila napaka, saj bomo klicali metodo toString()
    // nad objektom, ki več ne obstaja*/


    SmartPointer<Date> date1(new Date(1, 1, 2020));
    SmartPointer<Date> date2(new Date(1, 1, 2019));
    date2 = date1 = date1 = date1 = date1 = date1;
    date2 = date2;
    date2 = date2;
    std::cout << "reference count: " << date1.useCount() << std::endl;

    cout << date1.getNoOfEqualExpresion() << endl;

    return 0;
}
