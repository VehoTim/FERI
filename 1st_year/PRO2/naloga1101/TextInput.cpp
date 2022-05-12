//
// Created by timve on 4. 06. 2021.
//

#include "TextInput.h"

TextInput::TextInput(Position position, Size size, const std::string &text, int length, const std::string &input) : TextView(position, size, text), length(length), input(input) {}

void TextInput::draw() {
    TextView::draw();
    std::cout << ": \"";
    for (int i = 0; i < input.length() && i < length; ++i) {
        std::cout << input[i];
    }
    for (int i = 0; i < length - input.length(); ++i) {
        std::cout << " ";
    }
    std::cout << "\"";
}

void TextInput::setInputText(const std::string &text) {
    this->input = text;
}
