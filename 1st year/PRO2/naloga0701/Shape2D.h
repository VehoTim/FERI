//
// Created by tim on 11. 04. 2021.
//

#ifndef NALOGA0701_SHAPE2D_H
#define NALOGA0701_SHAPE2D_H

#include "Color.h"
#include "Visibility.h"

class Shape2D {
protected:
    Color color;
    Visibility visibility;
public:
    Shape2D(const Color& color);
    ~Shape2D() = default;
    void setVisibility(Visibility visibility);
    virtual bool inBounds(float canvasWidth, float canvasHeight) = 0;
    virtual void draw() = 0;
};


#endif //NALOGA0701_SHAPE2D_H
