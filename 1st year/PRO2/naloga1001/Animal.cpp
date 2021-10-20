//
// Created by timve on 28. 05. 2021.
//

#include "Animal.h"

Animal::Animal(double size) : size(size) {}

std::ostream &operator<<(ostream &out, const Animal &animal) {
    return out << animal.toString();
}

string Animal::toString() const {
    return "Size: " + to_string(size);
}

Animal &Animal::operator++() {
    size = size*(1.01);
    return *this;
}

Animal Animal::operator++(int fake) {
    Animal tmp(this->size);
    size = size*(1.01);
    return tmp;
}