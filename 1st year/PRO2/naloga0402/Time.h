#ifndef NALOGA0402_TIME_H
#define NALOGA0402_TIME_H

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


#endif //NALOGA0402_TIME_H
