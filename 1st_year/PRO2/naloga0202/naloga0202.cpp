#include <iostream>
#include <vector>
#include <ctime>
#include "CovidData.h"

/*
- Dodaj v menu dodatno opcijo addData, ki na koncu vektorja doda nov naključen podatek. Po potrebi popravi kodo.
- Napišite metodo filterData, ki prejme vektor kazalcev, in limit (int) okužb, vrne pa nov vektor, ki vsebuje vse dneve,
    ko število okužb je večje od limit. Demonstriraj podatke.*/

using namespace std;

void menu() {
    cout << "============================" << endl;
    cout << "=========== MENU ===========" << endl;
    cout << "============================" << endl;
    cout << "1 ... GENERATE ACTIVE CASES" << endl;
    cout << "2 ... PRINT ACTIVE CASES" << endl;
    cout << "3 ... PRINT AVERAGE NUMBER OF ACTIVE CASES" << endl;
    cout << "4 ... PRINT NUMBER OF DAYS WITH MORE ACTIVE CASES THAN AVERAGE" << endl;
    cout << "5 ... PRINT PERCENTAGE OF DAYS WITH MORE ACTIVE CASES THAN AVERAGE" << endl;
    cout << "6 ... PRINT NUMBER OF DAYS WITH EACH AMOUNT OF CASES" << endl;
    cout << "7 ... PRINT SMALLEST NUMBER OF CASES" << endl;
    cout << "8 ... ADD DATA" << endl;
    cout << "9 ... FILTER DATA" << endl;
    cout << "0 ... EXIT" << endl;
    cout << "============================" << endl;
    cout << "Select: ";
}



int calculateAvg(vector<CovidData*> vector){
    int avg = 0;
    for (int i = 0; i < vector.size(); ++i) {
        avg+=vector[i]->getActiveCases();                  //we add up all values from "array"
    }
    return avg = avg / vector.size();            //we calculate the average value by diving with size
}

void fillVector(vector<CovidData*> &vector, const unsigned int size) {
    for (int i = 0; i < size; ++i) {
        vector.push_back(new CovidData(i+1,3,2021, rand() % 4000 + 1000)); //generate random numbers between 500 and 5000
    }

    //avg = calculateAvg(vector);    //when filling an array we also calculate average value for future purposes
}

void printVector(vector<CovidData*> vector) {
    for (unsigned int i = 0; i < vector.size(); i++) {
        cout << vector[i]->toString() << ((i < vector.size() - 1) ? ", " : ".") << std::endl;
    }
}



void printAvg(vector<CovidData*> vector) {
    cout << "Average number of active cases is " << calculateAvg(vector) << endl;    //output of the avg value
}

int aboveAverage(vector<CovidData*> vector) {
    int avg = calculateAvg(vector);
    int nod = 0;                        //number of days
    for (int i = 0; i < vector.size(); ++i) {
        if (avg < vector[i]->getActiveCases()) nod++;
    }
    return nod;
}

void printAboveAverage(vector<CovidData*> vector) {
    cout << "Number of days with more active cases than average: " << aboveAverage(vector) << endl;
}

void printPercentage(vector<CovidData*> vector) {
    cout << "Percentage of days with more active cases than average: " <<
         ((double)(aboveAverage(vector))/30)*100 << "%" << endl;
}

void printNum(vector<CovidData*> vector) {
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;

    for (int i = 0; i < vector.size(); ++i) {
        if (vector[i]->getActiveCases() < 2000) num1++;
        else if(vector[i]->getActiveCases() < 3000) num2++;
        else if(vector[i]->getActiveCases() < 4000) num3++;
        else num4++;
    }

    cout << "Number of active cases: " << endl;
    cout << " - 1000-1999: " << num1 << endl;
    cout << " - 2000-2999: " << num2 << endl;
    cout << " - 3000-3999: " << num3 << endl;
    cout << " - 4000-4999: " << num4 << endl;
}

void printMax5Days(vector<CovidData*> vector){
    int max = 0;
    int length = vector.size() - (vector.size() % 5);
    for (int i = 0; i < length; i++) {
        cout << vector[i]->getActiveCases() << ", ";
        if (vector[i]->getActiveCases() > max) max = vector[i]->getActiveCases();

        if ((i + 1) % 5 == 0){
            cout << "max: " << max << endl;
            max = 0;
        }
    }
    if (vector.size() % 5 != 0)
        cout << "Naslednji podatek bo cez " <<  (5 - (vector.size() % 5)) << " dan/dni";
}

void printMin(vector<CovidData*> vector){
    int min = INT_MAX;
    for (int i = 0; i < vector.size(); ++i) {
        if (vector[i]->getActiveCases() < min) min = vector[i]->getActiveCases();
    }
    cout << min << endl;
}

void addData(vector<CovidData*> &vector){
    vector.push_back(new CovidData(vector.size()+1,3,2021, rand() % 4000 + 1000)); //generate random numbers between 500 and 5000

    //avg = calculateAvg(vector);    //when filling an array we also calculate average value for future purposes
}

vector<CovidData*> filterData(vector<CovidData*> vec, int limit){
    vector<CovidData*> aboveLimit;
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i]->getActiveCases() > limit) aboveLimit.push_back(vec[i]);
    }
    return aboveLimit;
}

void printFiltered(vector<CovidData*> vec, int limit){
    printVector(filterData(vec, limit));
}

int main() {
    //const unsigned int days = 10;
    const int num = 31;
    vector<CovidData*> covidStats;

    srand(time(nullptr));

    //printMax5Days(covidStats, num);

    bool running = true;
    int selection;

    do {
        menu();
        cin >> selection;
        switch (selection) {
            case 1:
                fillVector(covidStats, num);
                break;
            case 2:
                printVector(covidStats);
                break;
            case 0:
                running = false;
                break;
            case 3:
                printAvg(covidStats);
                break;
            case 4:
                printAboveAverage(covidStats);
                break;
            case 5:
                printPercentage(covidStats);
                break;
            case 6:
                printNum(covidStats);
                break;
            case 7:
                printMin(covidStats);
                break;
            case 8:
                addData(covidStats);
                break;
            case 9:
                int limit;
                cout << "Choose the limit: ";
                cin >> limit;
                printFiltered(covidStats, limit);
                break;
            default:
                cout << "Wrong selection!" << endl;
                break;
        }
        cout << endl;
    } while (running);


    for (int i = 0; i < num; ++i) {
        delete[] covidStats[i];
    }

    covidStats.clear();

    return 0;
}