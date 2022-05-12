//
// Created by timve on 21. 05. 2021.
//

#ifndef NALOGA0901_POINT_H
#define NALOGA0901_POINT_H

#include <string>
#include <cmath>
#include <sstream>

template <typename T>
class Point{
private:
    T x, y;
public:
    Point(T x, T y) : x(x), y(y){};
    Point move(T m1, T m2){
        return Point(x += m1, y+=m2);
    }
    bool equal(const Point &other) const{
        return (this->x == other.x && this->y == other.y);
    };
    std::string to_string() const{
        std::stringstream ss;
        ss << "x: " << x << ", y: " << y;
        return ss.str();
    };
};

template<>
inline bool Point<float>::equal(const Point<float> &other) const {
    return (abs(this->x - other.x) < 0.000001 && abs(this->y - other.y) < 0.0000001);
}

#endif //NALOGA0901_POINT_H
