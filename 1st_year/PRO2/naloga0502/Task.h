#ifndef NALOGA0501_TASK_H
#define NALOGA0501_TASK_H


#include <string>
#include "DateTime.h"

using namespace std;

class Task {
protected:
    string name, description;
    DateTime added;
public:
    Task(string name, string description, DateTime &added);
    virtual string toString() const;

    virtual Date getAdded();
    virtual DateTime getAddedDT();
    virtual string getName();
};


#endif //NALOGA0501_TASK_H
