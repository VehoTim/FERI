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

    std::string exportJSON() const;
};


#endif //TASK0501_TIME_H
