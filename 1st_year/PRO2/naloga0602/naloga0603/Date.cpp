//
// Created by tim on 16. 04. 2021.
//

#include "Date.h"
#include <sstream>

Date::Date(unsigned int day, unsigned int month, unsigned int year) : day(day), month(month), year(year) {}

std::string Date::toString() const {
    std::stringstream ss;
    ss << ((day < 10) ? "0" : "") << day << "."
       << ((month < 10) ? "0" : "") << month << "."
       << year;
    return ss.str();
}

unsigned int Date::getDay() const { return this->day; }
unsigned int Date::getMonth() const { return this->month; }
unsigned int Date::getYear() const { return this->year; }
