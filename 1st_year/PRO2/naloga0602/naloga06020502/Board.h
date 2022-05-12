#ifndef NALOGA0501_BOARD_H
#define NALOGA0501_BOARD_H

/*
 zamenjajte instančno spremenljivko tasks z categories: std::vector<Category> (kompozicija),
dodajte metodo void addCategory(const Category &category),
spremenite definicijo metode addTask v bool addTask(const std::string &categoryName, Task* task)
(preveri, če kategorija s tem imenom obstaja, potem task doda v kategorijo in vrne true, v nasprotnem primeru vrne false).
 */

#include <string>
#include <vector>
#include "Category.h"

using namespace std;

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

    void bord();
};


#endif //NALOGA0501_BOARD_H
