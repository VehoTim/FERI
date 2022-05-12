#include "ExpirationTask.h"
#include <sstream>

ExpirationTask::ExpirationTask(string name, string description, DateTime &added, string assignee, DateTime &deadline,
                               string state, Color color) : ColorTask(color, name, description, added), assignee(assignee), deadline(deadline), state(state) {}

string ExpirationTask::toString() const{
    std::stringstream ss;
    ss << ColorTask::toString() << endl;
    ss << "\tassignee: " << assignee << ", deadline: " << deadline.toString() << ", state: " << state;
    return ss.str();
}

Date ExpirationTask::getAdded() { return ColorTask::getAdded(); }

DateTime ExpirationTask::getAddedDT() { return ColorTask::getAddedDT(); }

/*bool ExpirationTask::isExpired(DateTime now) {
    return now.isAfter(this->deadline);
}*/

string ExpirationTask::getName() {
    return ColorTask::getName();
}

Color ExpirationTask::getColor() const {
    return Color(0, 0, 0);
}
