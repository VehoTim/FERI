//
// Created by tim on 16. 04. 2021.
//

#ifndef NALOGA06020502_COLOR_H
#define NALOGA06020502_COLOR_H

#include <iostream>

class Color {
private:
    unsigned char r, g, b;
public:
    static Color red;
    static Color green;
    static Color blue;
    Color(unsigned char r, unsigned char g, unsigned char b);
    Color(unsigned char cyan, unsigned char magenta, unsigned char yellow, unsigned char black);
    std::string toString() const;
    static Color generateRandomColor();

    bool isBigger(Color c2) const;
};


#endif //NALOGA06020502_COLOR_H
