#include "Circle.h"
#include "Math.h"
#include <iostream>
#include <sstream>

int Circle::counter = 0;

Circle::Circle(){
    radius = 1;
    counter++;
};

Circle::Circle(int r){
    setRadius(r);
    counter++;
}

Circle::Circle(Circle &a) {
    setRadius(a.radius);
    counter++;
}

Circle::~Circle() {
    counter--;
}

void Circle::setRadius(int r){
    this->radius = r;
}

string Circle::toString() const{
    stringstream ss;
    ss << "radius: " << radius;
    return ss.str();
}

void Circle::printCounter(){
    cout << "Count: " << counter;
}

double Circle::diameter(Circle a){
    return 2 * a.radius * Math::PI;
}

double Circle::area(Circle a){
    return Math::PI * Math::square(a.radius);
}

vector<struct Circle *> Circle::generateCircles(int noc) {
    vector<Circle*> circles;
    for (int i = 0; i < noc; ++i) {
        circles.push_back(new Circle(rand() % 49 + 1));
    }
    return circles;
}

void Circle::printCircles(vector<Circle*> &circles) {
    for (Circle* item : circles) {
        cout << item->toString() << endl;
    }
}
