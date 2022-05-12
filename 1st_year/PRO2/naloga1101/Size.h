//
// Created by timve on 2. 06. 2021.
//

#ifndef NALOGA1101_SIZE_H
#define NALOGA1101_SIZE_H

#include "Unit.h"
#include <string>
#include <sstream>

class Size {
private:
    float width;
    float height;
    Unit unit;
public:
    Size(float width, float height, Unit unit);

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);

    Unit getUnit() const;

    void setUnit(Unit unit);

    std::string toString() const;

    std::string getUnitInString() const;
};


#endif //NALOGA1101_SIZE_H
