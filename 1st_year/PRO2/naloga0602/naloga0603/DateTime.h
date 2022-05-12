//
// Created by tim on 16. 04. 2021.
//

#ifndef NALOGA0603_DATETIME_H
#define NALOGA0603_DATETIME_H

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


#endif //NALOGA0603_DATETIME_H
