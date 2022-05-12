#include "Time.h"
#include <sstream>


Time::Time() : hour(0), minute(0), second(0) {}

Time::Time(int hour, int minute, int second) : hour(hour), minute(minute), second(second) {}

string Time::toString() const {
    stringstream ss;
    ss << hour << ":" << minute << ":" << second;
    return ss.str();
}

unsigned int Time::getHour() const { return this->hour; }
unsigned int Time::getMinute() const { return this->minute; }
unsigned int Time::getSecond() const { return this->second; }


