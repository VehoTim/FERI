#ifndef NALOGA0401_COMPETITION_H
#define NALOGA0401_COMPETITION_H

#include "Date.h"
#include <vector>
#include "Competitor.h"

class Competition {
private:
    string name;
    Date startDate;
    vector<Competitor> competitors;
public:
    Competition(string name, Date startDate);

    void addCompetitor(Athlete* athlete);

    void addResult(unsigned int startNumber, double result);

    void printCompetitors();

    vector<Competitor> getQualifiedCompetitors(double limit) const;

    string toString() const;

    void removeResult0();
};


#endif //NALOGA0401_COMPETITION_H
