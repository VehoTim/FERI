//
// Created by timve on 2. 06. 2021.
//

#include "View.h"

View::View(Position position, Size size) : position(position), size(size) {}

const Position &View::getPosition() const {
    return position;
}

void View::setPosition(const Position &position) {
    View::position = position;
}

const Size &View::getSize() const {
    return size;
}

void View::setSize(const Size &size) {
    View::size = size;
}

bool View::isVisible() {
    return visible;
}

void View::setVisible(bool visible) {
    View::visible = visible;
}

void View::draw() {
    //std::cout << "Position: " << position.toString() << ", size:" << size.toString();
}


