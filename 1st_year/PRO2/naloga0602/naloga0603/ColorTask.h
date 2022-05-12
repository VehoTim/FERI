//
// Created by tim on 16. 04. 2021.
//

#ifndef NALOGA0603_COLORTASK_H
#define NALOGA0603_COLORTASK_H

#include "Task.h"

class ColorTask : public Task{
private:
    Color color;
public:
    ColorTask(Color color, string name, string description, DateTime added);
    std::string toString() const override;

    Date getAdded() override;
    DateTime getAddedDT() override;
    string getName() override;

    Color getColor() override;

};


#endif //NALOGA0603_COLORTASK_H
