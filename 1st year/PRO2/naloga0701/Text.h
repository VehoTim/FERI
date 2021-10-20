//
// Created by tim on 11. 04. 2021.
//

#ifndef NALOGA0701_TEXT_H
#define NALOGA0701_TEXT_H

#include "Shape2D.h"

class Text : public Shape2D{
private:
    float x, y;
    unsigned int fontSize;
    std::string text;
public:
    Text(Color color, float x, float y, unsigned int fontSize, std::string text);
    bool inBounds(float canvasWidth, float canvasHeight) override;
    void draw() override;
};


#endif //NALOGA0701_TEXT_H
