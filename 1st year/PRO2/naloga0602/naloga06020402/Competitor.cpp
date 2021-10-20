#include "Competitor.h"
#include <sstream>

Competitor::Competitor(unsigned int startNum, string firstName, string lastName, string country, double height,
                       double weight) : startNumber(startNum), Athlete(firstName, lastName, country, height, weight) {}

string Competitor::toString() const {
    stringstream ss;
    ss << "Start num: " << startNumber << ", athlete: " << Athlete::toString()  << endl;
    return ss.str();
}

Results Competitor::getResults() const {
    return this->results;
}

void Competitor::addResult(double result) {
    this->results.addResult(result);
}

void Competitor::print() {
        cout << "Start num: " << startNumber << ": name:" << firstName << " " << lastName << ", country: " << country;
        cout << ", height: " << height << "cm, weight: " << weight << "kg" << endl;
}

