#include <iostream>
#include "CovidData.h"

int CovidData::getDay() {
    return day;
}

int CovidData::getMonth() {
    return month;
}

int CovidData::getYear() {
    return year;
}

int CovidData::getActiveCases() {
    return activeCases;
}

void CovidData::setActiveCases(int activeCases) {
    this->activeCases = activeCases;
}

string CovidData::toString() {
    stringstream ss;
    ss << day << "." << month << ".: " << year << ", active cases: " << activeCases;
    return ss.str();
}