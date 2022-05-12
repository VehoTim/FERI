#ifndef NALOGA0501_EXPIRATIONTASK_H
#define NALOGA0501_EXPIRATIONTASK_H

/*
assignee: std::string (komu je naloga dodeljena, omejimo se na eno osebo),
deadline: DateTime (kompozicija),
state: std::string (trenutno stanje naloge (npr. TODO, DOING, DONE)),
konstruktor (s šestimi parametri),
toString().
 */

#include <string>
#include "Task.h"
#include "DateTime.h"

using namespace std;

class ExpirationTask : public Task {
private:
    string assignee;
    DateTime deadline;
    string state;
public:
    ExpirationTask(string name, string description, DateTime &added, string assignee, DateTime &deadline, string state);
    string toString() const override;

    string exportJSON() const override;
};


#endif //NALOGA0501_EXPIRATIONTASK_H
