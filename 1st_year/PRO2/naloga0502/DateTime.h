#ifndef TASK0501_DATETIME_H
#define TASK0501_DATETIME_H

#include "Date.h"
#include "Time.h"

class DateTime {
private:
    Date date;
    Time time;

public:
    DateTime(Date date, Time time);

    std::string toString() const;

    Date getDate();

    bool isAfter(const DateTime &second);

    bool isBefore(const DateTime &second);

};


#endif //TASK0501_DATETIME_H
