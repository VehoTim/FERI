#include <iostream>
#include "Athlete.h"

using namespace std;

// stanje objekta Athlete height ne sme biti manjse od 50cm. V primeru poizkusa nastavitve napacne vrednosti izpisite "data error" in nastavite vrednost na 50
// napišite metodo isSame, ki prejme kazalec na Atleta in vrne true, ce so vsi podatki enaki

// Dodate Athlete lastnost number (int). Popravi izpise in konstruktorje.

int main() {
    Athlete *a = new Athlete();

    Athlete b(2, "Tim", "Vehovar", "Rogatec", 176.0, 62.0);

    Athlete c;

    c.setNumber(3);
    c.setFirstName("Tim");
    c.setLastName("Vehovar");
    c.setCountry("Rogatec");
    c.setHeight(176);
    c.setWeight(62);

    Athlete d;

    Athlete *e = new Athlete(5, "Name", "LastName", "Country", 30, 68);


    cout << a->toString() << endl;
    cout << b.getFirstName() << " " << b.getLastName() << endl;
    cout << c.toString() << endl;
    d.print();
    e->print();


    if (c.isSame(b)) cout << "Same athlete";
    else cout << "Not same athlete";

    delete a,e;

    return 0;
}
