#ifndef NALOGA0502_CATEGORY_H
#define NALOGA0502_CATEGORY_H

/*
name: std::string,
tasks: std::vector<Task*> (kompozicija),
konstruktor (z enim parametrom, ime kategorije),
void addTask(Task* task),
std::string toString() const.
 */

#include <string>
#include <vector>
#include "Task.h"
#include "ExpirationTask.h"

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

};


#endif //NALOGA0502_CATEGORY_H
