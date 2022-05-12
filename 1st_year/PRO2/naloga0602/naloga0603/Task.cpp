//
// Created by tim on 16. 04. 2021.
//

#include <sstream>
#include "DateTime.h"
#include "Task.h"
#include <string>

using namespace std;

Task::Task(string name, string description, DateTime &added) : name(name), description(description), added(added) {}

string Task::toString() const {
    std::stringstream ss;
    ss << "Name: " << name << ", description: " << description << ", added: " << added.toString();
    return ss.str();
}

Date Task::getAdded() { return this->added.getDate(); }

DateTime Task::getAddedDT() { return this->added; }

string Task::getName() { return name; }