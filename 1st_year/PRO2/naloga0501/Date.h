#ifndef TASK0501_DATE_H
#define TASK0501_DATE_H

#include <iostream>

class Date {
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;

public:
    Date(unsigned int day, unsigned int month, unsigned int year);

    std::string toString() const;

    std::string exportJSON() const;
};


#endif //TASK0501_DATE_H
