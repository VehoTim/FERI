//
// Created by tim on 11. 04. 2021.
//

#ifndef NALOGA0701_COLOR_H
#define NALOGA0701_COLOR_H

#include <string>

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
};


#endif //NALOGA0701_COLOR_H
