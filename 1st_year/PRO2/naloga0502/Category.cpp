#include "Category.h"
#include <sstream>

Category::Category(string name) : name(name){}

void Category::addTask(Task *task) { this->tasks.push_back(task); }

string Category::toString() const {
    std::stringstream ss;
    ss << "Name: " << name << endl;
    for(Task* t : tasks){
        ss << "\t-> " << t->toString() << endl;
    }
    return ss.str();
}

string Category::getName() { return this->name; }

vector<Task *> Category::getTasks() { return this->tasks; }

void Category::setName(string name) { this->name = name; }
