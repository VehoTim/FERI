#ifndef NALOGA0501_EXPIRATIONTASK_H
#define NALOGA0501_EXPIRATIONTASK_H

#include <string>
#include "ColorTask.h"
#include "DateTime.h"

using namespace std;

class ExpirationTask : public ColorTask {
private:
    string assignee;
    DateTime deadline;
    string state;
public:
    ExpirationTask(string name, string description, DateTime &added, string assignee, DateTime &deadline, string state, Color color);
    string toString() const override;

    Date getAdded() override;
    DateTime getAddedDT() override;
    string getName() override;

    //bool isExpired(DateTime now) override;

    Color getColor() const override;
};


#endif //NALOGA0501_EXPIRATIONTASK_H
