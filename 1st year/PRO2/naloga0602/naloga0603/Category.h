//
// Created by tim on 16. 04. 2021.
//

#ifndef NALOGA0603_CATEGORY_H
#define NALOGA0603_CATEGORY_H

#include <string>
#include <vector>
#include "Task.h"

using namespace std;

class Category {
private:
    string name;
    vector<Task*> tasks;
public:
    Category(string name);

    void addTask(Task* task);
    string toString() const;

    string getName();
    void setName(string name);
    vector<Task*> getTasks();

    void bord();
};


#endif //NALOGA0603_CATEGORY_H
