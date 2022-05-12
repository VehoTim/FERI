#ifndef NALOGA0401_COMPETITOR_H
#define NALOGA0401_COMPETITOR_H

#include "Athlete.h"

class Competitor{
private:
    unsigned int startNumber;
    Athlete* athlete;
    double result;
public:
    Competitor(unsigned int startNum, Athlete* athlete1, double result);
    string toString() const;

    void setResult(double result);

    double getResult() const;
};


#endif //NALOGA0401_COMPETITOR_H
