//
// Created by tim on 26. 04. 2021.
//

#ifndef NALOGA0801B_TIME_H
#define NALOGA0801B_TIME_H

#include <string>

using namespace std;

class Time {
private:
    unsigned int hour, minute, second;
public:
    Time();
    Time(int hour, int minute, int second);

    string toString() const;

    unsigned int getHour() const;
    unsigned int getMinute() const;
    unsigned int getSecond() const;
};



#endif //NALOGA0801B_TIME_H
