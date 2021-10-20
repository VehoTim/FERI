//
// Created by tim on 11. 04. 2021.
//

#ifndef NALOGA0701_CANVAS_H
#define NALOGA0701_CANVAS_H

#include "Shape2D.h"
#include <vector>

class Canvas {
private:
    float width;
    float height;
    std::vector<Shape2D*> shapes;
public:
    Canvas(float width, float height);
    ~Canvas();
    bool addShape(Shape2D* shape);
    void resize(float width, float height);
    void draw();
    void undo();
};


#endif //NALOGA0701_CANVAS_H
