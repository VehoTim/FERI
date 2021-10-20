#include "ExpirationTask.h"
#include <sstream>

ExpirationTask::ExpirationTask(string name, string description, DateTime &added, string assignee, DateTime &deadline,
                               string state) : Task(name, description, added), assignee(assignee), deadline(deadline), state(state) {}

string ExpirationTask::toString() const{
    std::stringstream ss;
    ss << Task::toString() << endl;
    ss << "\tassignee: " << assignee << ", deadline: " << deadline.toString() << ", state: " << state;
    return ss.str();
}

string ExpirationTask::exportJSON() const {
    std::stringstream ss;
    ss << Task::exportJSON() << " assigne: \"" << assignee << "\" , deadline: " << deadline.exportJSON() << ", state: \"" << state << "\"}";
    return ss.str();
}
