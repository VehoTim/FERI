//
// Created by timve on 2. 06. 2021.
//

#ifndef NALOGA1101_VIEW_H
#define NALOGA1101_VIEW_H

#include "Position.h"
#include "Size.h"
#include <iostream>

class View {
protected:
    Position position;
    Size size;
    bool visible;
public:
    View(Position position, Size size);

    const Position &getPosition() const;

    void setPosition(const Position &position);

    const Size &getSize() const;

    void setSize(const Size &size);

    bool isVisible();

    void setVisible(bool visible);

    virtual void draw();
};


#endif //NALOGA1101_VIEW_H
