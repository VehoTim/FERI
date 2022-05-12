//
// Created by timve on 2. 06. 2021.
//

#ifndef NALOGA1101_TEXTVIEW_H
#define NALOGA1101_TEXTVIEW_H

#include "View.h"
#include <string>

class TextView : public View{
protected:
    std::string text;
public:
    TextView(Position position, Size size, const std::string &text);

    const std::string &getText() const;

    void setText(const std::string &text);

    void draw() override;
};


#endif //NALOGA1101_TEXTVIEW_H
