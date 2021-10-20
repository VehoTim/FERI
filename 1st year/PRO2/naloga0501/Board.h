#ifndef NALOGA0501_BOARD_H
#define NALOGA0501_BOARD_H

/*
name: std::string,
tasks: std::vector<Task*> (seznam vseh nalog; kompozicija),
konstruktor (z enim parametrom, ime table),
void addTask(Task* task),
std::string toString() const.
 */

#include <string>
#include <vector>
#include "Task.h"

using namespace std;

class Board {
private:
    string name;
    vector<Task*> tasks;
public:
    Board(string name);
    ~Board();
    void addTask(Task* task);
    string toString() const;

    string exportJSON() const;
};


#endif //NALOGA0501_BOARD_H
