#ifndef NALOGA06020502_COLORTASK_H
#define NALOGA06020502_COLORTASK_H

#include <string>
#include "Task.h"
#include "Color.h"

using namespace std;

class ColorTask : public Task {
protected:
    Color color;
public:
    ColorTask(Color color, string name, string description, DateTime added);
    std::string toString() const override;

    Date getAdded()override;
    DateTime getAddedDT() override;
    string getName() override;

   Color getColor() const override;
};


#endif //NALOGA06020502_COLORTASK_H
