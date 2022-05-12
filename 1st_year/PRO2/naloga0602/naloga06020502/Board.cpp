#include "Board.h"
#include <sstream>

Board::Board(string name) : name(name) {}

Board::~Board() {
    for (int i = categories.size() - 1; i >= 0; i--) {
        for (int j = categories[i].getTasks().size() - 1; j >= 0 ; --j) {
            delete categories[i].getTasks()[j];
        }
        categories[i].getTasks().clear();
    }
    categories.clear();
    this->name = nullptr;
}

string Board::toString() const {
    std::stringstream ss;
    ss << "Name: " << name << endl;
    for(Category c : categories){
        ss << " - " << c.toString() << endl;
    }
    return ss.str();
}

void Board::addCategory(const Category &category) { categories.push_back(category); }

bool Board::addTask(const string &categoryName, Task *task) {
    for(Category &c : categories){
        if(c.getName() == categoryName) {
            c.addTask(task);
            return true;
        }
    }
    return false;
}

void Board::agenda(const Date &date) const {
    for (Category c : categories){
        for (Task* t : c.getTasks()){
            if (t->getAdded().toString() == date.toString())
                cout << t->toString() << endl;
        }
    }
}

bool Board::changeName(const string &categoryName, const string &newName) {
    for(Category &c : categories){
        if(c.getName() == categoryName) {
            c.setName(newName);
            return true;
        }
    }
    return false;
}



Board::Board(const Board &old) {
    this->name = old.name + "Copy";
    for(Category c : old.categories){
        this->categories.push_back(c);
    }
}

/*Board Board::removeAllWithTaskName(const string ime) {
    Board tmpBoard(name + "Copy");
    for (int i = 0; i < this->categories.size(); ++i) {
        tmpBoard.categories.push_back((this->categories[i]));
    }
    for (Category &c : tmpBoard.categories){
        for (int i = 0; i < c.getTasks().size(); ++i) {
            if (c.getTasks()[i]->getName() == ime){
                //c.getTasks().erase(c.getTasks().begin() + i);
            }
        }
    }
    return tmpBoard;
}*/

Board Board::removeAllWithTaskName(const string ime) {
    Board tmpBoard(name + "Copy");
    for (int i = 0; i < this->categories.size(); ++i) {
        tmpBoard.addCategory(Category(this->categories[i].getName()));
        for (int j = 0; j < this->categories[i].getTasks().size(); ++j) {
            if (this->categories[i].getTasks()[j]->getName() != ime){
                Task* nov = this->categories[i].getTasks()[j];
                tmpBoard.addTask(this->categories[i].getName(), nov);
            }
        }
    }
    return tmpBoard;
}

void Board::bord() {
    for(int i = 0; i < categories.size(); i++){
        categories[i].bord();
    }
}
