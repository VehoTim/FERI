#include "Board.h"
#include <sstream>

Board::Board(string name) : name(name) {}

bool Board::addTask(Task *task) {
    for(auto &t : tasks){
        if(task->getName() == t.first) return false;
    }
    tasks.emplace(task->getName(), task);
    for(string &s : task->getTags()){
        byTag[s].push_back(task);
    }
    return true;
}

string Board::toString() const {
    std::stringstream ss;
    ss << "Name: " << name << endl;
    for(auto t : tasks){ ss << " - " << t.second->toString() << endl; }
    return ss.str();
}

Task *Board::findTask(const string &key) const {
    for(auto &t : tasks){
        if(key == t.first) return t.second;
    }
    return nullptr;
}

void Board::deleteTask(const string &key) {
    for(auto &t : tasks){
        if(key == t.first) {
            delete t.second;
            t.second = nullptr;
            tasks.erase(key);
            break;
        };
    }
}

unsigned int Board::numberOfTasks() const {
    return tasks.size();
}

std::vector<Task *> Board::toVector(Board board) {
    vector<Task *> tmp;
    for(auto &t : board.tasks){
        tmp.push_back(t.second);
    }
    return tmp;
}

void Board::clearTasks() {
    for(auto t : tasks){
        delete t.second;
        t.second = nullptr;
    }
    tasks.clear();
}

void Board::swapTasks(const string &key1, const string &key2) {
    for(auto &t : tasks){
        if(key1 == t.first) {
            for(auto &t2 : tasks){
                if(key2 == t2.first) swap(t.second, t2.second);
            }
        }
    }
}

void Board::changeDate(const string &key, DateTime newDT) {
    for(auto &t : tasks){
        if(t.first == key) t.second->setAdded(newDT);
    }
}

std::vector<Task *> Board::findTaskByTag(const string &tag) {
    return byTag[tag];
}
