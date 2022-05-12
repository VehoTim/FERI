#ifndef NALOGA0201_ATHLETE_H
#define NALOGA0201_ATHLETE_H

#include <string>
#include <iostream>

using namespace std;

class Athlete {
private:
    int number;
    string firstName, lastName, country;
    double height, weight;

public:
    //constructors
    Athlete(){
        number = 0;
        firstName = "";
        lastName = "";
        country = "";
        height = 0;
        weight = 0;
    }

    Athlete(int number, string firstName, string lastName, string country, double height, double weight){
        this->setNumber(number);
        this->setFirstName(firstName);
        this->setLastName(lastName);
        this->setCountry(country);
        this->setHeight(height);
        this->setWeight(weight);
    }

    int getNumber();
    string getFirstName();
    string getLastName();
    string getCountry();
    double getHeight();
    double getWeight();

    void setNumber(int number);
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setCountry(string country);
    void setHeight(double height);
    void setWeight(double weight);

    void print();
    string toString();

    bool isSame(Athlete b);
};


#endif //NALOGA0201_ATHLETE_H
