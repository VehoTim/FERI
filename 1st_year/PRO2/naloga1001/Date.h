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
    int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
public:
    Date(unsigned int day, unsigned int month, unsigned int year);

    friend std::ostream& operator<<(std::ostream &out, const Date &date);
    string toString() const;

    unsigned int getDay() const;
    unsigned int getMonth() const;
    unsigned int getYear() const;

    bool operator==(const Date& other);
    Date& operator++();
    Date operator++(int dummy);
};


#endif //NALOGA0801B_DATE_H
