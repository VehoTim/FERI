//
// Created by timve on 28. 05. 2021.
//

#ifndef NALOGA1001_ANIMAL_H
#define NALOGA1001_ANIMAL_H

#include <string>

using namespace std;

class Animal {
private:
    double size;
public:
    Animal(double size);

    string toString() const;

    friend std::ostream& operator<<(std::ostream &out, const Animal &animal);
    Animal& operator++();
    Animal operator++(int fake);
};


#endif //NALOGA1001_ANIMAL_H
