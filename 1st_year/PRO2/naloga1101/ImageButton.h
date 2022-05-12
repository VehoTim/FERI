//
// Created by timve on 3. 06. 2021.
//

#ifndef NALOGA1101_IMAGEBUTTON_H
#define NALOGA1101_IMAGEBUTTON_H

#include "Button.h"
#include "ImageView.h"

class ImageButton : public Button, public ImageView{
public:
    ImageButton(Position position, Size size, const std::string &text, const std::string &path);
    void draw() override;
};


#endif //NALOGA1101_IMAGEBUTTON_H
