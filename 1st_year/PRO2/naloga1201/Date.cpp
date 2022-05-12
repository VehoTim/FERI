//
// Created by tim on 13. 06. 2021.
//

#include <iostream>
#include "Date.h"
#include <sstream>
#include "UnparseableDateException.h"

Date::Date(unsigned int day, unsigned int month, unsigned int year) : day(day), month(month), year(year) {}

unsigned int Date::getDay() const{
    return day;
}

unsigned int Date::getMonth() const {
    return month;
}

unsigned int Date::getYear() const {
    return year;
}

std::string Date::toString() const {
    std::stringstream ss;
    if(getDay() < 10) ss << 0;
    ss << getDay() << ".";
    if(getMonth() < 10) ss << 0;
    ss << getMonth() << "." << getYear();
    return ss.str();
}

Date Date::GetDateFromString(std::string datum) {
    for (int i = 0; i < datum.length(); ++i) {
        if(i == 2 || i == 5){
            if(datum[i] != '.') throw UnparseableDateException(datum);
            else continue;
        }
        if(isdigit(datum[i])) continue;
        else throw UnparseableDateException(datum);
    }

    unsigned int day = std::stoi(datum.substr(0, 2));
    unsigned int month =  std::stoi(datum.substr(3, 2));
    unsigned int year = std::stoi(datum.substr(6, 4));
    return Date(day, month, year);
}
