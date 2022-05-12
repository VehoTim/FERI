#include "Board.h"
#include <sstream>

Board::Board(string name) : name(name) {}

Board::~Board() {
    for (int i = tasks.size() - 1; i >= 0; i--) {
        delete tasks[i];
    }
    tasks.clear();
    this->name = nullptr;
}

void Board::addTask(Task *task) { tasks.push_back(task); }

string Board::toString() const {
    std::stringstream ss;
    ss << "Name: " << name << endl;
    for(Task* t : tasks){ ss << " - " << t->toString() << endl; }
    return ss.str();
}

string Board::exportJSON() const {
    std::stringstream ss;
    for(Task* t : tasks){
        ss << "{ name: \"" << name << "\" {" << t->exportJSON() << "}" << endl;
    }
    return ss.str();
}
