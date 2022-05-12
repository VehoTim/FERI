//
// Created by timve on 2. 06. 2021.
//

#include "ImageView.h"

#include <utility>

ImageView::ImageView(Position position, Size size, const std::string &imgPath) : View(position, size), imgPath(imgPath) {}

const std::string &ImageView::getImgPath() const {
    return imgPath;
}

void ImageView::setImgPath(const std::string &imgPath) {
    ImageView::imgPath = imgPath;
}

void ImageView::draw() {
    View::draw();
    std::cout << ", img. path: " << imgPath;
}
