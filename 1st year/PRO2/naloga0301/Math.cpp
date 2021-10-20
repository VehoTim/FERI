#include "Math.h"

const double Math::PI = 3.14159265358979323846;

double Math::square(int num) {
    return num * num;
}

Circle Math::maxCircle(Circle &a, Circle &b) {
    if (Circle::diameter(a) >= Circle::diameter(b)) return a;
    else return b;
}

Trapez Math::maxTrapez(Trapez &a, Trapez &b) {
    if (Trapez::diameter(a) >= Trapez::diameter(b)) return a;
    else return b;
}
