//
// Created by timve on 2. 06. 2021.
//

#ifndef NALOGA1101_POSITION_H
#define NALOGA1101_POSITION_H

#include <string>
#include <sstream>


class Position {
private:
    float x, y;
public:
    Position(float x, float y);
    float getX() const;
    float getY() const;
    std::string toString() const;
};


#endif //NALOGA1101_POSITION_H
