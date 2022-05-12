#ifndef NALOGA0402_DATETIME_H
#define NALOGA0402_DATETIME_H

#include "Date.h"
#include "Time.h"

class DateTime {
private:
    Date date;
    Time time;
public:
    DateTime(Date date1, Time time1);

    string toString() const;

    bool isEqual(const DateTime &second);

    bool isAfter(const DateTime &second);
    bool isBefore(const DateTime &second);
};


#endif //NALOGA0402_DATETIME_H
