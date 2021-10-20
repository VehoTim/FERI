//
// Created by tim on 11. 04. 2021.
//

#include "Text.h"
#include <iostream>

Text::Text(Color color, float x, float y, unsigned int fontSize, std::string text) : Shape2D(color), x(x), y(y), fontSize(fontSize), text(text) {}

bool Text::inBounds(float canvasWidth, float canvasHeight) {
    return (canvasWidth > (x + text.length() * fontSize) && canvasHeight > (y + fontSize));
}

void Text::draw() {
    if(visibility == Visibility::VISIBLE){
        std::cout << text;
    }
}
