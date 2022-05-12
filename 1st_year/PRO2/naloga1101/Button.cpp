//
// Created by timve on 2. 06. 2021.
//

#include "Button.h"

Button::Button(Position position, Size size, const std::string text) : TextView(position, size, text) {
    enabled = true;
}

bool Button::isEnabled() const {
    return enabled;
}

void Button::setEnabled(bool enabled) {
    Button::enabled = enabled;
}

void Button::onClick() {
    if(enabled) std::cout << getText();
}

void Button::draw() {
    for (int i = 0; i < size.getWidth() - position.getY(); ++i) {
        std::cout << "-";
    }
    std::cout << "\n| ";
    TextView::draw();
    for (int i = 0; i < size.getWidth() - position.getY() - text.length() - 3; ++i) {
        std::cout << " ";
    }
    std::cout << "|\n";
    for (int i = 0; i < size.getWidth() - position.getY(); ++i) {
        std::cout << "-";
    }
}
