//
// Created by timve on 2. 06. 2021.
//

#include "Position.h"

Position::Position(float x, float y) : x(x), y(y) {}

float Position::getX() const{
    return x;
}

float Position::getY() const{
    return y;
}

std::string Position::toString() const {
    std::stringstream ss;
    ss << "x: " << x << ", y: " << y;
    return ss.str();
}
