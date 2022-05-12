//
// Created by timve on 4. 06. 2021.
//

#ifndef NALOGA1101_TEXTINPUT_H
#define NALOGA1101_TEXTINPUT_H

#include "TextView.h"

class TextInput : public TextView{
private:
    int length;
    std::string input;
public:
    TextInput(Position position, Size size, const std::string &text, int length, const std::string &input);
    void draw() override;
    void setInputText(const std::string &text);
};


#endif //NALOGA1101_TEXTINPUT_H
