//
// Created by tim on 16. 04. 2021.
//

#include "DateTime.h"
#include <sstream>

DateTime::DateTime(Date date, Time time) : date(date), time(time) {}

std::string DateTime::toString() const {
    std::stringstream ss;
    ss << date.toString() << " " << time.toString();
    return ss.str();
}

Date DateTime::getDate() { return this->date; }

bool DateTime::isAfter(const DateTime &second) {
    if (this->date.getYear() == second.date.getYear()){
        if (this->date.getMonth() == second.date.getMonth()){
            if (this->date.getDay() == second.date.getDay()){
                if (this->time.getHour() == second.time.getHour()){
                    if (this->time.getMinute() == second.time.getSecond()){
                        if (this->time.getSecond() == second.time.getSecond()){
                            return false;
                        }
                        else return this->time.getSecond() > second.time.getSecond();
                    }
                    else return this->time.getMinute() > second.time.getMinute();
                }
                else return this->time.getHour() > second.time.getHour();
            }
            else return this->date.getDay() > second.date.getDay();
        }
        else return this->date.getMonth() > second.date.getMonth();
    }
    else return this->date.getYear() > second.date.getYear();
}

bool DateTime::isBefore(const DateTime &second) {
    return !(this->isAfter(second));
}
