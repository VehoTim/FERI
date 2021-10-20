#include <iostream>
#include <vector>
#include "Competition.h"
#include "DateTime.h"
#include <ctime>

int main() {
    /*//DEMONSTRATION OF getCompetitionsBetween
    vector<Competition *> competitions;

    //Competition is in 2021
    competitions.push_back(new Competition("Competition 1",
                                       DateTime(Date(17,2,2021), Time(9,30,0)),
                                       DateTime(Date(25,2,2021), Time(22,0,0))));

    //Competition is in 2021
    competitions.push_back(new Competition("Competition 2",
                                       DateTime(Date(17,2,2021), Time(19,35,0)),
                                       DateTime(Date(25,2,2021), Time(20,0,0))));

    //Competition starts before 2021
    competitions.push_back(new Competition("Competition 3",
                                       DateTime(Date(10,5,2017), Time(18,10,0)),
                                       DateTime(Date(25,2,2021), Time(12,5,0))));

    //Competition ends after 2021
    competitions.push_back(new Competition("Competition 4",
                                       DateTime(Date(10,5,2021), Time(14,33,0)),
                                       DateTime(Date(5,12,2023), Time(22,22,0))));

    vector<Competition *> competitionsIn2021 = Competition::getCompetitionsBetween(competitions,
                                                                                   DateTime(Date(1,1,2021),Time()),
                                                                                   DateTime(Date(31,12,2021), Time()));

    for(Competition* c : competitionsIn2021){
        cout << c->toString() << endl;
    }*/

    Athlete *peter = new Athlete("Peter", "Prevc", "Slovenia", 182, 64);
    Athlete *tim = new Athlete("Tim", "Vehovar", "Slovenia", 177, 61);
    Athlete *klemen = new Athlete("Klemen", "Bracun", "New Zeland", 180, 63);
    Athlete *rok = new Athlete("Rok", "Klun", "Slovenia", 182, 64);
    Athlete *toni = new Athlete("Anton", "Lajhar", "Slovenia", 177, 61);
    Athlete *tekm1 = new Athlete("tekm1", "Bracun", "New Zeland", 180, 63);
    Athlete *tekm2 = new Athlete("tekm2", "Prevc", "Slovenia", 182, 64);
    Athlete *tekm3 = new Athlete("tekm3", "Vehovar", "Slovenia", 177, 61);
    Athlete *tekm4 = new Athlete("tekm4", "Bracun", "New Zeland", 180, 63);
    Athlete *tekm5 = new Athlete("tekm5", "Prevc", "Slovenia", 182, 64);
    Athlete *tekm6 = new Athlete("tekm6", "Vehovar", "Slovenia", 177, 61);
    Athlete *tekm7 = new Athlete("tekm7", "Bracun", "New Zeland", 180, 63);
    Competition skoki("Skoki1", DateTime(Date(25,3,2021), Time()), DateTime(Date(8,4,2021), Time()));
    skoki.addCompetitor(peter);
    skoki.addCompetitor(tim);
    skoki.addCompetitor(klemen);
    skoki.addCompetitor(rok);
    skoki.addCompetitor(toni);
    skoki.addCompetitor(tekm1);
    skoki.addCompetitor(tekm2);
    skoki.addCompetitor(tekm3);
    skoki.addCompetitor(tekm4);
    skoki.addCompetitor(tekm5);
    skoki.addCompetitor(tekm6);
    skoki.addCompetitor(tekm7);

    srand(time(nullptr));

    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 3; ++j) {
            skoki.addResult(i + 1, rand() % 150 + 100);
        }
    }

    cout << skoki.toString();

    //vector<Competitor> qualified = skoki.getQualifiedCompetitors(200);

    //for(Competitor c : qualified) cout << c.toString();

    skoki.printPlayOff();

    cout << endl;

    skoki.printAvgResult();

    delete peter, tim, klemen,rok, toni, tekm1, tekm2, tekm3, tekm4, tekm5, tekm6, tekm7;
    peter = tim = klemen = rok = toni = tekm1 = tekm2 = tekm3 = tekm4 = tekm5 = tekm6 = tekm7 = nullptr;
    return 0;
}
