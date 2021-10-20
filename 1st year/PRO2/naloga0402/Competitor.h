#ifndef NALOGA0402_COMPETITOR_H
#define NALOGA0402_COMPETITOR_H

#include "Athlete.h"
#include "Results.h"

class Competitor {
private:
    unsigned int startNumber;
    Athlete* athlete;
    Results results;
public:
    Competitor(unsigned int startNum, Athlete* athlete1/*, double result*/);
    string toString() const;

    string name() const;

    //void setResult(double result);

    void addResult(double result);

    Results getResults() const;
};


#endif //NALOGA0402_COMPETITOR_H
