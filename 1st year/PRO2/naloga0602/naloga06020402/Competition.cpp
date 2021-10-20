#include "Competition.h"
#include <sstream>
#include <algorithm>

Competition::Competition(string name, DateTime startDate, DateTime endDate) : name(name), startDate(startDate), endDate(endDate) {
}

void Competition::addCompetitor(string firstName, string lastName, string country, double height, double weight) {
    Competitor a(competitors.size() + 1, firstName, lastName, country, height, weight);
    competitors.push_back(a);
}

void Competition::addResult(unsigned int startNumber, double result) {
    competitors[startNumber - 1].addResult(result);
}

void Competition::printCompetitors() {
    for(Competitor c : competitors) cout << c.toString();
}

vector<Competitor> Competition::getQualifiedCompetitors(double limit) const {
    vector<Competitor> tmpComp;
    for(Competitor c : competitors){
        Results tmpRes = c.getResults();
        double max = tmpRes.getResults()[0];
        for(double r : tmpRes.getResults()){
            if(r > max) max = r;
        }
        if (max >= limit) tmpComp.push_back(c);
    }
    return tmpComp;
}

string Competition::toString() const {
    stringstream ss;
    ss << "Name: " << name << ", start date: " << startDate.toString() << ", number of competitors: " << competitors.size() << endl;
    return ss.str();
}

vector<Competition *> Competition::getCompetitionsBetween(const vector<Competition *> competitions, const DateTime &from, const DateTime &to) {
    vector<Competition *> tmp;
    for(Competition* comp : competitions){
        if (comp->startDate.isAfter(from) && comp->endDate.isBefore(to))
            tmp.push_back(comp);
    }
    return tmp;
}
