//
// Created by timve on 2. 06. 2021.
//

#ifndef NALOGA1101_BUTTON_H
#define NALOGA1101_BUTTON_H

#include "TextView.h"

class Button : virtual public TextView{
protected:
    bool enabled;
public:
    Button(Position position, Size size, const std::string text);

    bool isEnabled() const;

    void setEnabled(bool enabled);

    void onClick();

    void draw() override;
};


#endif //NALOGA1101_BUTTON_H
