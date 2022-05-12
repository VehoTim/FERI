#include "Results.h"

void Results::addResult(double result) { this->results.push_back(result); }

vector<double> Results::getResults() {
    return results;
}

double Results::getAvgResult() {
    double sum = 0;
    for(double r : results){  sum+=r; }
    return (sum / results.size());
}