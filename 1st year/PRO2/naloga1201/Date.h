//
// Created by tim on 13. 06. 2021.
//

#ifndef NALOGA1201_DATE_H
#define NALOGA1201_DATE_H

#include <string>


class Date {
private:
    unsigned int day, month, year;
public:
    Date(unsigned int day, unsigned int month, unsigned int year);

    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;

    std::string toString() const;

    static Date GetDateFromString(std::string datum);
};


#endif //NALOGA1201_DATE_H
