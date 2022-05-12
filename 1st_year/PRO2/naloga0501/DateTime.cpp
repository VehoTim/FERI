#include "DateTime.h"
#include <sstream>

DateTime::DateTime(Date date, Time time) : date(date), time(time) {}

std::string DateTime::toString() const {
    std::stringstream ss;
    ss << date.toString() << " " << time.toString();
    return ss.str();
}

std::string DateTime::exportJSON() const {
    std::stringstream ss;
    ss << "{ date: " << this->date.exportJSON() << ", time: " << this->time.exportJSON() << "}";
    return ss.str();
}
