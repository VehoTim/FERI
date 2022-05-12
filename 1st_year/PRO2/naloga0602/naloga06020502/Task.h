#ifndef NALOGA0501_TASK_H
#define NALOGA0501_TASK_H

#include "DateTime.h"
#include "Color.h"

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

    //virtual bool isExpired(DateTime now) = 0;

    virtual Color getColor() const = 0;
};


#endif //NALOGA0501_TASK_H
