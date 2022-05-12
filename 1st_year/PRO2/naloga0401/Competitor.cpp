#include "Competitor.h"
#include <sstream>

Competitor::Competitor(unsigned int startNum, Athlete *athlete1, double result) : startNumber(startNum), athlete(athlete1), result(result){}

string Competitor::toString() const {
    stringstream ss;
    ss << "Start num: " << startNumber << ", athlete: " << athlete->toString() << ", result: " << result << endl;
    return ss.str();
}

void Competitor::setResult(double result) { this->result = result; }

double Competitor::getResult() const{
    return this->result;
}

