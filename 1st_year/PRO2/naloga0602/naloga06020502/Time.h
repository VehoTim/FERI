#ifndef TASK0501_TIME_H
#define TASK0501_TIME_H

#include <iostream>

class Time {
private:
    unsigned int hour;
    unsigned int minute;
    unsigned int second;

public:
    Time(unsigned int hour, unsigned int minute, unsigned int second);

    std::string toString() const;

    unsigned int getHour() const;
    unsigned int getMinute() const;
    unsigned int getSecond() const;
};


#endif //TASK0501_TIME_H
