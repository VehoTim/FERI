#include "Color.h"

#include <sstream>
#include <ctime>

Color Color::red(255,0,0);
Color Color::green(0,255,0);
Color Color::blue(0,0,255);

Color::Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

Color::Color(unsigned char cyan, unsigned char magenta, unsigned char yellow, unsigned char black) {
    r = 255 * (1 - cyan / 100) * (1 - black / 100);
    g = 255 * (1 - magenta / 100) * (1 - black / 100);
    b = 255 * (1 - yellow / 100) * (1 - black / 100);
}

std::string Color::toString() const {
    std::stringstream ss;
    ss << "(" << (int)r << "," << (int)g << "," << (int)b << ")";
    return ss.str();
}

Color Color::generateRandomColor() {
    srand(time(nullptr));
    return Color(rand() % 256, rand() % 256, rand() % 256);
}

bool Color::isBigger(Color c2) const {
    return ((int)this->r + (int)this->b + (int)this->g) > ((int)c2.r + (int)c2.b + (int)c2.g);
}
