//
// Created by timve on 2. 06. 2021.
//

#include "TextView.h"

TextView::TextView(Position position, Size size, const std::string &text) : View(position, size), text(text) {}

const std::string &TextView::getText() const {
    return text;
}

void TextView::setText(const std::string &text) {
    TextView::text = text;
}

void TextView::draw() {
    View::draw();
    std::cout /*<< ", "*/ << text;
}
