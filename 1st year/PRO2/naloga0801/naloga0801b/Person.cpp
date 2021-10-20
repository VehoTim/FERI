//
// Created by tim on 26. 04. 2021.
//

#include "Person.h"
#include <sstream>

Person::Person(std::string fn, std::string ln, double height, double weight) : firstName(fn), lastName(ln),
                                                                                 height(height), weight(weight) {}

double Person::getHeight() const {
    return height;
}

double Person::getWeight() const {
    return weight;
}

std::string Person::toString() const {
    std::stringstream ss;
    ss << firstName << " " << lastName << " (" << height << "cm, " << weight << "kg)";
    return ss.str();
}
