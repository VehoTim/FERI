//
// Created by tim on 26. 04. 2021.
//

#ifndef NALOGA0801B_DATE_H
#define NALOGA0801B_DATE_H

#include <string>
using namespace std;

class Date {
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;

public:
    Date(unsigned int day, unsigned int month, unsigned int year);

    string toString() const;

    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;
};


#endif //NALOGA0801B_DATE_H
