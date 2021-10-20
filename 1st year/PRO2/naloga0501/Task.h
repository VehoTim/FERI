#ifndef NALOGA0501_TASK_H
#define NALOGA0501_TASK_H

/*
name: std::string,
description: std::string,
added: DateTime (kompozicija),
konstruktor (trije parametri, za vsako instančno spremenljivko),
toString().
 */

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

    virtual string exportJSON() const;
};


#endif //NALOGA0501_TASK_H
