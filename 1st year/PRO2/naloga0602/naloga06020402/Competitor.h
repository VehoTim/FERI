#ifndef NALOGA0402_COMPETITOR_H
#define NALOGA0402_COMPETITOR_H

#include "Athlete.h"
#include "Results.h"

class Competitor : public Athlete{
private:
    unsigned int startNumber;
    Results results;
public:
    Competitor(unsigned int startNum, string firstName, string lastName, string country, double height, double weight);

    string toString() const override;
    void print() override;

    void addResult(double result);

    Results getResults() const;
};


#endif //NALOGA0402_COMPETITOR_H
