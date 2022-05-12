#include <iostream>
#include <vector>
#include "Competition.h"
#include "DateTime.h"
#include <ctime>

int main() {
    //DEMONSTRATION OF getCompetitionsBetween
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
    }


    Competition skoki("Ime tekmovanja", DateTime(Date(25,3,2021), Time()), DateTime(Date(8,4,2021), Time()));
    skoki.addCompetitor("Peter", "Prevc", "Slovenia", 182, 64);
    skoki.addCompetitor("Tim", "Vehovar", "Slovenia", 177, 61);
    skoki.addCompetitor("Klemen", "Bracun", "New Zeland", 180, 63);
    skoki.addCompetitor("Rok", "Klun", "Slovenia", 182, 64);
    skoki.addCompetitor("Anton", "Lajhar", "Slovenia", 177, 61);
    skoki.addCompetitor("tekm1", "Bracun", "New Zeland", 180, 63);
    skoki.addCompetitor("tekm2", "Prevc", "Slovenia", 182, 64);
    skoki.addCompetitor("tekm3", "Vehovar", "Slovenia", 177, 61);
    skoki.addCompetitor("tekm4", "Bracun", "New Zeland", 180, 63);
    skoki.addCompetitor("tekm5", "Prevc", "Slovenia", 182, 64);
    skoki.addCompetitor("tekm6", "Vehovar", "Slovenia", 177, 61);
    skoki.addCompetitor("tekm7", "Bracun", "New Zeland", 180, 63);

    srand(time(nullptr));

    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 3; ++j) {
            skoki.addResult(i + 1, rand() % 150 + 100);
        }
    }

    cout << skoki.toString();

    cout << endl;

    skoki.printCompetitors();
    return 0;
}
