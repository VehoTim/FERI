//
// Created by tim on 11. 04. 2021.
//

#ifndef NALOGA0701_RECTANGLE_H
#define NALOGA0701_RECTANGLE_H

#include "Shape2D.h"

class Rectangle : public Shape2D{
private:
    float x, y, width, height;
public:
    Rectangle(Color color, float x, float y, float width, float height);
    bool inBounds(float canvasWidth, float canvasHeight) override;
    void draw() override;
};


#endif //NALOGA0701_RECTANGLE_H
