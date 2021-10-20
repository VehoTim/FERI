#include "Competitor.h"
#include <sstream>

Competitor::Competitor(unsigned int startNum, Athlete *athlete1/*, double result*/) : startNumber(startNum), athlete(athlete1)/*, result(result)*/{}

string Competitor::toString() const {
    stringstream ss;
    ss << "Start num: " << startNumber << ", athlete: " << athlete->toString() /*<< ", result: " << result*/ << endl;
    return ss.str();
}

//void Competitor::setResult(double result) { this->result = result; }

Results Competitor::getResults() const{
    return this->results;
}

void Competitor::addResult(double result) {
    this->results.addResult(result);
}

string Competitor::name() const {
    stringstream ss;
    ss << this->athlete->name();
    return ss.str();
}

