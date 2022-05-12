//
// Created by tim on 16. 04. 2021.
//

#include "ColorTask.h"

#include <sstream>

ColorTask::ColorTask(Color color, string name, string description, DateTime added) : color(color),
                                                                                     Task(name, description, added) {}

std::string ColorTask::toString() const {
    std::stringstream ss;
    ss << Task::toString() << ": ";
    ss << color.toString();
    return ss.str();
}

Color ColorTask::getColor() {
    return this->color;
}

DateTime ColorTask::getAddedDT() {
    return Task::getAddedDT();
}

Date ColorTask::getAdded() {
    return Task::getAdded();
}

string ColorTask::getName() {
    return Task::getName();
}

