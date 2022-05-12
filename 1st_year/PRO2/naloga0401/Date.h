#ifndef NALOGA0401_DATE_H
#define NALOGA0401_DATE_H

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
};


#endif //NALOGA0401_DATE_H
