#ifndef NALOGA0501_EXPIRATIONTASK_H
#define NALOGA0501_EXPIRATIONTASK_H

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

    Date getAdded() override;

    DateTime getAddedDT() override;

    bool isExpired(DateTime now);

    string getName() override;
};


#endif //NALOGA0501_EXPIRATIONTASK_H
