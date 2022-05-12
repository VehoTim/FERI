//
// Created by tim on 13. 06. 2021.
//

#include <iostream>
#include <sstream>
#include "Fuel.h"
#include <fstream>
#include <algorithm>
#include "UnparseableDateException.h"
#include <stdarg.h>

Fuel::Fuel(Date date, unsigned int mileage, float fuealAmount, std::string fuelType, float pricePerLiter)
: date(date), mileage(mileage), fuelAmount(fuealAmount), fuelType(fuelType), pricePerLiter(pricePerLiter) {}

const Date &Fuel::getDate() const {
    return date;
}

unsigned int Fuel::getMileage() const {
    return mileage;
}

float Fuel::getFuelAmount() const {
    return fuelAmount;
}

const std::string &Fuel::getFuelType() const {
    return fuelType;
}

float Fuel::getPricePerLiter() const {
    return pricePerLiter;
}

std::string Fuel::toString() const {
    std::stringstream ss;
    ss << date.toString() << ", mileage: " << mileage << ", fuel type: " << fuelType;
    return ss.str();
}

std::vector<Fuel> Fuel::LoadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    std::vector<Fuel> fuelArr;
    while (!file.eof()) {
        std::string dateString, mileage, fuelAmount, fuelType, pricePerLiter;
        std::getline(file, dateString, ',');
        std::getline(file, mileage, ',');
        std::getline(file, fuelAmount, ',');
        std::getline(file, fuelType, ',');
        std::getline(file, pricePerLiter, '\n');
        try {
            Date date(Date::GetDateFromString(dateString));
            fuelArr.push_back(Fuel(date, std::stoi(mileage), std::stof(fuelAmount), fuelType,
                                   std::stof(pricePerLiter)));
        } catch (UnparseableDateException ude) {
            std::cout << ude.what() << std::endl;
        }
        file.peek();
    }
    file.close();
    return fuelArr;
}

void Fuel::SortRefuels(std::vector<Fuel> &refuels, bool (*c)(const Fuel &, const Fuel &)) {
    std::sort(refuels.begin(), refuels.end(), c);
}

bool ascendingFuelAmount(const Fuel &refuel1, const Fuel &refuel2) {
    return (refuel1.getFuelAmount() < refuel2.getFuelAmount());
}

void Fuel::saveToFile(const std::vector<Fuel> &athletes, const std::string &fileName) {
    std::vector<Fuel> tmp = athletes;
    Fuel::SortRefuels(tmp, ascendingFuelAmount);
    std::ofstream file(fileName);
    for (Fuel f : tmp){
        file << f.date.toString() << ',' << f.mileage << ',' << f.fuelAmount << ',' << f.fuelType << ',' << f.pricePerLiter << '\n';
    }
    file.close();
}

double Fuel::avgPricePerLiter(int n, ...) {
    va_list args;
    double sum = 0;
    va_start(args, n);

    for (int i = 0; i < n; ++i) {
        sum += va_arg(args, double);
    }
    va_end(args);
    return sum/n;
}
