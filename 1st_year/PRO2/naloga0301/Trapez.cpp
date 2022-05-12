#include "Trapez.h"
#include <cmath>
#include "Math.h"
#include <iostream>
#include <sstream>

int Trapez::counter = 0;

Trapez::Trapez() {
    setA(1);
    setB(1);
    setC(1);
    setD(1);
    counter++;
}

Trapez::Trapez(double a, double b, double c, double d) {
    setA(a);
    setB(b);
    setC(c);
    setD(d);
    counter++;
}

Trapez::Trapez(Trapez &t) {
    setA(t.a);
    setB(t.b);
    setC(t.c);
    setD(t.d);
    counter++;
}

Trapez::~Trapez() { counter--; }

void Trapez::setA(double a) {
    this->a = a;
}

void Trapez::setB(double b) {
    this->b = b;
}

void Trapez::setC(double c) {
    this->c = c;
}

void Trapez::setD(double d) {
    this->d = d;
}

string Trapez::toString() const {
    stringstream ss;
    ss << "a: " << a << ", b:" << b << ", c:" << c << ", d:" << d << endl;
    return ss.str();
}
void Trapez::printCounter(){
    cout << "Count: " << counter;
}

double Trapez::diameter(Trapez &t) {
    return t.a + t.b + t.c + t.d;
}

double Trapez::area(Trapez &t) {
    return ((t.a + t.c) / (4 * (t.a - t.c))) *
    (sqrt((t.a + t.b - t.c + t.d) * (t.a - t.b - t.c + t.d) * (t.a + t.b - t.c - t.d) * ( 0 - t.a + t.b + t.c + t.d)));
}

vector<Trapez *> Trapez::generateTrapezes(int no) {
    vector<Trapez*> trapezes;
    for (int i = 0; i < no; ++i) {
        trapezes.push_back(new Trapez(rand() % 49 + 1,rand() % 49 + 1,rand() % 49 + 1,rand() % 49 + 1));
    }
    return trapezes;
}

void Trapez::printCircles(vector<Trapez *> &trapezes) {
    for (Trapez* item : trapezes) {
        cout << item->toString() << endl;
    }
}
