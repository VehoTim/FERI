#ifndef NALOGA0402_RESULTS_H
#define NALOGA0402_RESULTS_H

#include <vector>
#include "DateTime.h"

using namespace std;

class Results {
private:
    vector<double> results;
public:
    void addResult(double result);

    vector<double> getResults();

    double getAvgResult();
};


#endif //NALOGA0402_RESULTS_H
