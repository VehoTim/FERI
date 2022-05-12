#ifndef NALOGA0402_ATHLETE_H
#define NALOGA0402_ATHLETE_H

#include <string>
#include <iostream>

using namespace std;

class Athlete {
protected:
    string firstName, lastName, country;
    double height, weight;

public:
    //constructors
    Athlete(){
        firstName = "";
        lastName = "";
        country = "";
        height = 0;
        weight = 0;
    }

    ~Athlete() = default;

    Athlete(string firstName, string lastName, string country, double height, double weight){
        this->setFirstName(firstName);
        this->setLastName(lastName);
        this->setCountry(country);
        this->setHeight(height);
        this->setWeight(weight);
    }
    string getFirstName();
    string getLastName();
    string getCountry();
    double getHeight();
    double getWeight();
    void setFirstName(string firstName);
    void setLastName(string lastName);
    void setCountry(string country);
    void setHeight(double height);
    void setWeight(double weight);

    virtual void print() = 0;
    virtual string toString() const;

};


#endif //NALOGA0402_ATHLETE_H
