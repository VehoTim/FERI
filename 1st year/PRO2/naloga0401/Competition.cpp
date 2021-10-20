#include "Competition.h"
#include <sstream>

Competition::Competition(string name, Date startDate) : name(name), startDate(startDate) {
}

void Competition::addCompetitor(Athlete *athlete) {
    Competitor a(competitors.size() + 1, athlete, 0);
    competitors.push_back(a);
}

void Competition::addResult(unsigned int startNumber, double result) {
    competitors[startNumber - 1].setResult(result);
}

void Competition::printCompetitors() {
    for(Competitor c : competitors) cout << c.toString();
}

vector<Competitor> Competition::getQualifiedCompetitors(double limit) const {
    vector<Competitor> tmp;
    for(Competitor c : competitors){
        if (c.getResult() >= limit) tmp.push_back(c);
    }
    return tmp;
}

string Competition::toString() const {
    stringstream ss;
    ss << "Name: " << ", start date: " << startDate.toString() << ", number of competitors: " << competitors.size() << endl;
    return ss.str();
}

void Competition::removeResult0() {
    for (int i = 0; i < competitors.size(); ++i) {
        if(competitors[i].getResult() == 0){
            competitors.erase(competitors.begin() + i);
            i--;
        }
    }
}
