//
// Created by tim on 11. 04. 2021.
//

#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(Color color, float x, float y, float width, float height) : Shape2D(color), x(x), y(y),
                                                                                 width(width), height(height) {}

bool Rectangle::inBounds(float canvasWidth, float canvasHeight) {
    return (canvasWidth > (x + width) && canvasHeight > (y + height));
}

void Rectangle::draw() {
    if (visibility == Visibility::VISIBLE){
        std::cout << color.toString() << ", x:" << x << ", y:" << y << ", width:" << width << ", height:" << height;
    }
}

