//
// Created by tim on 26. 04. 2021.
//

#ifndef NALOGA0801B_PERSON_H
#define NALOGA0801B_PERSON_H

#include <iostream>

class Person {
private:
    std::string firstName;
    std::string lastName;
    double height;
    double weight;
public:
    Person(std::string fn, std::string ln, double height, double weight);

    double getHeight() const;
    double getWeight() const;

    std::string toString() const;
};


#endif //NALOGA0801B_PERSON_H
