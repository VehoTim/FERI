#ifndef NALOGA0301_TRAPEZ_H
#define NALOGA0301_TRAPEZ_H

#include <string>
#include <vector>

using namespace std;

/*2. Po vzoru Circle naredite Trapez, vse metode tudi max v Math.
#include <cmath>
... sqrt(...)*/

class Trapez {
private:
    double a;
    double b;
    double c;
    double d;

    static int counter;

public:
    Trapez();
    Trapez(double a, double b, double c, double d);
    Trapez(Trapez &t);
    ~Trapez();

    void setA(double a);
    void setB(double b);
    void setC(double c);
    void setD(double d);

    string toString() const;

    static void printCounter();

    static double diameter(Trapez &t);
    static double area(Trapez &t);

    static vector<Trapez*> generateTrapezes(int no);

    static void printCircles(vector<Trapez*> &trapezes);
};


#endif //NALOGA0301_TRAPEZ_H
