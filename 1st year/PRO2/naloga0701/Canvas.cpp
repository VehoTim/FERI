//
// Created by tim on 11. 04. 2021.
//

#include "Canvas.h"
#include <iostream>

Canvas::Canvas(float width, float height) : width(width), height(height) {}

Canvas::~Canvas() {
    int size = shapes.size();
    for (int i = size - 1; i >= 0; ++i) {
        delete shapes[i];
    }
    shapes.clear();
}

bool Canvas::addShape(Shape2D *shape) {
    if(shape->inBounds(width,height)){
        shapes.push_back(shape);
        return true;
    }
    else return false;
}

void Canvas::resize(float width, float height) {
    this->width = width;
    this->height = height;
    for (int i = shapes.size() - 1; i >= 0 ; --i) {
        if(!(shapes[i]->inBounds(height,width))){
            delete shapes[i];
            shapes.erase(shapes.begin() + i);
        }
    }
}

void Canvas::draw() {
    for(Shape2D* shape : shapes){
        shape->draw();
        std::cout << std::endl;
    }
}

void Canvas::undo() {
    delete shapes[shapes.size() - 1];
    shapes.pop_back();
}
