//
// Created by timve on 2. 06. 2021.
//

#ifndef NALOGA1101_IMAGEVIEW_H
#define NALOGA1101_IMAGEVIEW_H

#include "View.h"
#include <string>

class ImageView : virtual public View{
protected:
    std::string imgPath;
public:
    ImageView(Position position, Size size, const std::string &imgPath);

    const std::string &getImgPath() const;

    void setImgPath(const std::string &imgPath);

    void draw() override;
};


#endif //NALOGA1101_IMAGEVIEW_H
