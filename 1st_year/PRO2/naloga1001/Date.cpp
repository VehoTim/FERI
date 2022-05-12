#include "Date.h"
#include <sstream>

Date::Date(unsigned int day, unsigned int month, unsigned int year) : day(day), month(month), year(year) {
}

string Date::toString() const {
    std::stringstream ss;
    ss << ((day < 10) ? "0" : "") << day << "."
       << ((month < 10) ? "0" : "") << month << "."
       << year;
    return ss.str();
}

unsigned int Date::getDay() const { return this->day; }
unsigned int Date::getMonth() const { return this->month; }
unsigned int Date::getYear() const { return this->year; }



bool Date::operator==(const Date &other) {
    return (this->getYear() == other.getYear() &&
            this->getMonth() == other.getMonth() &&
            this->getDay() == other.getDay() );
}

Date &Date::operator++() {
    if (months[month - 1] > day) day++;
    else month++, day = 1;
    if(month > 12) {
        month = 1;
        year += 1;
    }
    return *this;
}

Date Date::operator++(int dummy) {
    Date tmp(this->day, this->month, this->year);
    if (months[month - 1] > day) day += 1;
    else month += 1, day = 1;
    if(month > 12) {
        month = 1;
        year += 1;
    }
    return tmp;
}

std::ostream &operator<<(ostream &out, const Date &date)  {
    return out << date.toString();
}
