#include "Task.h"
#include <sstream>

Task::Task(string name, string description, DateTime &added) : name(name), description(description), added(added) {}

string Task::toString() const {
    std::stringstream ss;
    ss << "Name: " << name << ", description: " << description << ", added: " << added.toString();
    return ss.str();
}

string Task::exportJSON() const {
    std::stringstream ss;
    ss << " name: \"" << name << "\", description: \"" << description << "\" , added: " << added.exportJSON() << "}";
    return ss.str();
}