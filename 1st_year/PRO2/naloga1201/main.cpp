#include <iostream>

#include "Date.h"
#include "Fuel.h"

bool ascendingPricesPerLiter(const Fuel &refuel1, const Fuel &refuel2) {
    return (refuel1.getPricePerLiter() < refuel2.getPricePerLiter());
}

bool descendingPricesPerLiter(const Fuel &refuel1, const Fuel &refuel2) {
    return (refuel1.getPricePerLiter() > refuel2.getPricePerLiter());
}

int main() {

    std::vector<Fuel> fuels = Fuel::LoadFromFile("refuelfake.csv");
    for (auto f : fuels) {
        std::cout << f.toString() << std::endl;
    }

    std::cout << "Sorted A:" << std::endl;
    Fuel::SortRefuels(fuels, ascendingPricesPerLiter);
    for (auto f : fuels) {
        std::cout << f.toString() << std::endl;
    }

    std::cout << "Sorted D:" << std::endl;
    Fuel::SortRefuels(fuels, descendingPricesPerLiter);
    for (auto f : fuels) {
        std::cout << f.toString() << std::endl;
    }

    Fuel::saveToFile(fuels,"refuel_sorted.csv");

    std::cout << "Output file" << std::endl;
    std::vector<Fuel> fuels_new = Fuel::LoadFromFile("refuel_sorted.csv");
    for (auto f : fuels_new) {
        std::cout << f.toString() << std::endl;
    }

    std::cout << "Avg price per liter: " << Fuel::avgPricePerLiter(3, 1.325, 1.032, 1.215) << std::endl;

    return 0;
}
