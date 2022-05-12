#ifndef NALOGA0202_COVIDDATA_H
#define NALOGA0202_COVIDDATA_H

#include <sstream>

using namespace std;

class CovidData {
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;
    unsigned int activeCases;

public:
    CovidData() {
        day = 1;
        month = 1;
        year = 2021;
        activeCases = 0;
    }

    CovidData(int day, int month, int year, int activeCases) {
        this->day = day;
        this->month = month;
        this->year = year;
        this->activeCases = activeCases;
    }

    int getDay();

    int getMonth();

    int getYear();

    int getActiveCases();


    void setActiveCases(int activeCases);


    string toString();
};


#endif //NALOGA0202_COVIDDATA_H
