//
// Created by timve on 2. 06. 2021.
//

#include "Size.h"

Size::Size(float width, float height, Unit unit) : width(width), height(height), unit(unit) {}

float Size::getWidth() const {
    return width;
}

void Size::setWidth(float width) {
    Size::width = width;
}

float Size::getHeight() const {
    return height;
}

void Size::setHeight(float height) {
    Size::height = height;
}

Unit Size::getUnit() const {
    return unit;
}

void Size::setUnit(Unit unit) {
    Size::unit = unit;
}

std::string Size::toString() const {
    std::stringstream ss;
    ss << "width: " << width << getUnitInString() << " , height: " << height << getUnitInString();
    return ss.str();
}

std::string Size::getUnitInString() const{
    if(unit == Unit::px) return "px";
    else if(unit == Unit::pt) return "pt";
    else if(unit == Unit::dp) return "dp";
    else if(unit == Unit::in) return "in";
    else return "mm";
}
