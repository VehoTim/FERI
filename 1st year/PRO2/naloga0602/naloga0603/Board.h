//
// Created by tim on 16. 04. 2021.
//

#ifndef NALOGA0603_BOARD_H
#define NALOGA0603_BOARD_H


#include <string>
#include <vector>
#include "Category.h"

class Board {
private:
    string name;
    vector<Category> categories;
public:
    Board(string name);
    Board(const Board &old);
    ~Board();

    void addCategory(const Category &category);
    bool addTask(const string &categoryName, Task* task);
    string toString() const;

    void agenda(const Date &date) const;
    bool changeName(const string &categoryName, const string &newName);

    Board removeAllWithTaskName(const string ime);

};


#endif //NALOGA0603_BOARD_H
