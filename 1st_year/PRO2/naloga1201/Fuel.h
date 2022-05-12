//
// Created by tim on 13. 06. 2021.
//

#ifndef NALOGA1201_FUEL_H
#define NALOGA1201_FUEL_H

#include "Date.h"
#include <vector>

class Fuel {
private:
    Date date;
    unsigned int mileage;
    float fuelAmount;
    std::string fuelType;
    float pricePerLiter;
public:
    Fuel(Date date, unsigned int mileage, float fuealAmount, std::string fuelType, float pricePerLiter);

    const Date &getDate() const;

    unsigned int getMileage() const;

    float getFuelAmount() const;

    const std::string &getFuelType() const;

    float getPricePerLiter() const;

    std::string toString() const;
    static std::vector<Fuel> LoadFromFile(const std::string &filename);
    static void SortRefuels(std::vector<Fuel> &refuels, bool (*c)(const Fuel&, const Fuel&));
    static void saveToFile(const std::vector<Fuel> &athletes, const std::string &fileName);

    static double avgPricePerLiter(int n,...);
};


#endif //NALOGA1201_FUEL_H
