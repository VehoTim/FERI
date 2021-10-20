#include "Athlete.h"
#include <iostream>
#include <sstream>

//getters
int Athlete::getNumber() {
    return number;
}

string Athlete::getFirstName() {
    return firstName;
}

string Athlete::getLastName() {
    return lastName;
}

string Athlete::getCountry() {
    return country;
}

double Athlete::getHeight() {
    return height;
}

double Athlete::getWeight() {
    return weight;
}

//setters
void Athlete::setNumber(int number) {
    this->number = number;
}

void Athlete::setFirstName(string firstName) {
    this->firstName = firstName;
}

void Athlete::setLastName(string lastName) {
    this->lastName = lastName;
}

void Athlete::setCountry(string country) {
    this->country = country;
}

void Athlete::setHeight(double height) {
    if (height < 50){
        cout << "data error\n";
        height = 50;
    }
    this->height = height;
}

void Athlete::setWeight(double weight) {
    this->weight = weight;
}

//methods
void Athlete::print() {
    cout << "Nm: " << number << ". name:" << firstName << " " << lastName << ", country: " << country;
    cout << ", height: " << height << "cm, weight: " << weight << "kg" << endl;
}

string Athlete::toString() {
    stringstream ss;
    ss << "Nm: " << number << ". name: " << firstName << " " << lastName << ", country: " << country << ", height: " << height << "cm, weight: " << weight << "kg";
    return ss.str();
}

bool Athlete::isSame(Athlete b) {
    return (this->firstName == b.firstName && this->lastName == b.lastName && this->country == b.country && this->height == b.height && this->weight == b.weight);
}