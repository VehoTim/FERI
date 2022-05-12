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

void Category::bord() {
    for (int i = 0; i < tasks.size() - 1; i++){
        for (int j = 0; j < tasks.size() - i - 1; ++j) {
            if (tasks[i] > tasks[i+1]) {
                swap(tasks[i], tasks[i + 1]);
            }
        }
    }
}
