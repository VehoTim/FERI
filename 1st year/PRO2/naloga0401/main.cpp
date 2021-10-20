#include <iostream>
#include "Competition.h"
#include <ctime>

int main() {
    Competition comp1("Name of competition", Date(26,3,2021));
    string firstName, lastName, country;
    double height, weight;
    /*for (int i = 1; i <= 6; ++i) {
        cout << "Competitor " << i << endl;
        cout << "First name: ";
        getline(cin, firstName);
        cout << "Last name: ";
        getline(cin, lastName);
        cout << "Country: ";
        getline(cin, country);
        cout << "Height: ";
        cin >> height;
        cout << "Weight: ";
        cin >> weight;
        comp1.addCompetitor(new Athlete(firstName, lastName, country, height, weight));
        cin.ignore();
    }*/

    comp1.addCompetitor(new Athlete("Tim","Vehovar","Slovenia",177.8, 62));
    comp1.addCompetitor(new Athlete("Mitja","Kaluza","Poland",195.3, 100));
    comp1.addCompetitor(new Athlete("Klemen","Bracun","Japan",179.1, 70.3));
    comp1.addCompetitor(new Athlete("Rok","Klun","USA",167.8, 82.1));
    comp1.addCompetitor(new Athlete("Nejc","Vehovar","Croatia",174.9, 58.8));
    comp1.addCompetitor(new Athlete("Han","Hostnik","New Zeland",178.5, 70.2));


    srand(time(nullptr));
    /*for (int i = 1; i <= 6; ++i) {
        comp1.addResult(i, rand() % 100);
    }*/

    for (int i = 1; i <= 6; ++i) {
        comp1.addResult(i, rand() % 2);
    }

    comp1.printCompetitors();

    comp1.removeResult0();

    comp1.printCompetitors();

    /*vector<Competitor> qvlf;
    qvlf = comp1.getQualifiedCompetitors(50);

    cout << "\nQualified competitors: " << endl;
    for(Competitor comp : qvlf) cout << comp.toString();*/



    return 0;
}
