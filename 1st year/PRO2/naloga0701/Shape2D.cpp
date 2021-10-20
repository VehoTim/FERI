//
// Created by tim on 11. 04. 2021.
//

#include "Shape2D.h"

Shape2D::Shape2D(const Color &color) : color(color) { visibility = Visibility::VISIBLE; }

void Shape2D::setVisibility(Visibility visibility) { this->visibility = visibility; }
