//
// Created by tim on 16. 04. 2021.
//

#ifndef NALOGA0603_DATE_H
#define NALOGA0603_DATE_H

#include <iostream>

class Date {
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;

public:
    Date(unsigned int day, unsigned int month, unsigned int year);

    std::string toString() const;

    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;

};


#endif //NALOGA0603_DATE_H
