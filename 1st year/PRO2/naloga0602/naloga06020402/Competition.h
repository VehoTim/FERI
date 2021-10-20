#ifndef NALOGA0402_COMPETITION_H
#define NALOGA0402_COMPETITION_H

#include "DateTime.h"
#include <vector>
#include "Competitor.h"

class Competition {
private:
    string name;
    DateTime startDate;
    DateTime endDate;
    vector<Competitor> competitors;
public:
    Competition(string name, DateTime startDate, DateTime endDate);

    void addCompetitor(string firstName, string lastName, string country, double height, double weight);

    void addResult(unsigned int startNumber, double result);

    void printCompetitors();

    vector<Competitor> getQualifiedCompetitors(double limit) const;

    string toString() const;

    static vector<Competition*> getCompetitionsBetween(const vector<Competition*> competitions, const DateTime &from, const DateTime &to);
};


#endif //NALOGA0402_COMPETITION_H
