#include "Task.h"
#include <sstream>

Task::Task(string name, string description, DateTime &added) : name(name), description(description), added(added) {}

string Task::toString() const {
    std::stringstream ss;
    ss << "Name: " << name << ", description: " << description << ", added: " << added.toString();
    return ss.str();
}

std::string Task::getName() const {
    return name;
}

DateTime Task::getAdded() const {
    return added;
}

void Task::setAdded(DateTime dt) {
    this->added = dt;
}

std::vector<std::string> Task::getTags() const{
    return tags;
}

void Task::addTag(string tag) {
    tags.push_back(tag);
}
