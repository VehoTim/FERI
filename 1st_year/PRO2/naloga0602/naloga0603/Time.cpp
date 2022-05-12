//
// Created by tim on 16. 04. 2021.
//

#include "Time.h"
#include <sstream>

Time::Time(unsigned int hour, unsigned int minute, unsigned int second) : hour(hour), minute(minute), second(second) {}

std::string Time::toString() const {
    std::stringstream ss;
    ss << ((hour < 10) ? "0" : "") << hour << ":"
       << ((minute < 10) ? "0" : "") << minute << ":"
       << ((second < 10) ? "0" : "") << second;
    return ss.str();
}

unsigned int Time::getHour() const { return this->hour; }
unsigned int Time::getMinute() const { return this->minute; }
unsigned int Time::getSecond() const { return this->second; }
