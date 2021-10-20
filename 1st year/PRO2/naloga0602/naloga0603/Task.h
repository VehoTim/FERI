//
// Created by tim on 16. 04. 2021.
//

#ifndef NALOGA0603_TASK_H
#define NALOGA0603_TASK_H

#include "DateTime.h"
#include <vector>
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

    virtual Color getColor() = 0;

};


#endif //NALOGA0603_TASK_H
