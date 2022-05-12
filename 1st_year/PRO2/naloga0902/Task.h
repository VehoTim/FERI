#ifndef NALOGA0501_TASK_H
#define NALOGA0501_TASK_H

/*Razredu Task dodajte instančno spremenljivko std::vector<std::string> tags.*/

#include <string>
#include "DateTime.h"
#include <vector>

using namespace std;

class Task {
protected:
    string name, description;
    DateTime added;
    std::vector<std::string> tags;
public:
    Task(string name, string description, DateTime &added);
    virtual string toString() const;

    std::string getName() const;
    DateTime getAdded() const;

    void setAdded(DateTime dt);

    std::vector<std::string> getTags() const;

    void addTag(string tag);
};


#endif //NALOGA0501_TASK_H
