//
// Created by timve on 3. 06. 2021.
//

#include "ImageButton.h"

ImageButton::ImageButton(Position position, Size size, const std::string &text, const std::string &path) :
                                                            View(position, size),
                                                            TextView(position, size, text),
                                                            Button(position, size, text),
                                                            ImageView(position,size,path) {}

void ImageButton::draw() {
    Button::draw();
    std::cout << ", path: " << imgPath;
}
