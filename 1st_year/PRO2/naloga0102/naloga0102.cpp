#include <iostream>
#include <ctime>

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
    cout << "0 ... EXIT" << endl;
    cout << "============================" << endl;
    cout << "Select: ";
}


int avg;                                //global variable average

int calculateAvg(const unsigned int* array, const unsigned int size){
    avg = 0;
    for (int i = 0; i < size; ++i) {
        avg+=array[i];                  //we add up all values from "array"
    }
    return avg = avg / size;            //we calculate the average value by diving with size
}

void fillArray(unsigned int* array, const unsigned int size) {
    for (int i = 0; i < size; ++i) {
        array[i] = rand() % 4000 + 1000; //generate random numbers between 1000 and 5000
    }
    /*
    for (unsigned int i = 0; i < size; i++) {
        array[i] = 1000 + i * 100;
    }*/

    avg = calculateAvg(array, size);    //when filling an array we also calculate average value for future purposes
}

void printArray(const unsigned int* array, const unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        cout << ((i > 0) ? ", " : "") << array[i];
    }
    cout << "." << endl;
}



void printAvg(const unsigned int* array, const unsigned int size) {
    cout << "Average number of active cases is " << avg << endl;    //output of the avg value
}

int aboveAverage(const unsigned int* array, const unsigned int size) {
    int nod = 0;                        //number of days
    for (int i = 0; i < size; ++i) {
        if (avg < array[i]) nod++;
    }
    return nod;
}

void printAboveAverage(const unsigned int* array, const unsigned int size) {
    cout << "Number of days with more active cases than average: " << aboveAverage(array,size) << endl;
}

void printPercentage(const unsigned int* array, const unsigned int size) {
    cout << "Percentage of days with more active cases than average: " <<
            ((double)(aboveAverage(array,size))/30)*100 << "%" << endl;
}

void printNum(const unsigned int* array, const unsigned int size) {
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
    int num4 = 0;

    for (int i = 0; i < size; ++i) {
        if (array[i] < 2000) num1++;
        else if(array[i] < 3000) num2++;
        else if(array[i] < 4000) num3++;
        else num4++;
    }

    cout << "Number of active cases: " << endl;
    cout << " - 1000-1999: " << num1 << endl;
    cout << " - 2000-2999: " << num2 << endl;
    cout << " - 3000-3999: " << num3 << endl;
    cout << " - 4000-4999: " << num4 << endl;
}

void printMax5Days(const unsigned int* array, const unsigned int size){
    int max = 0;
    int length = size - (size % 5);
    for (int i = 0; i < length; i++) {
        cout << array[i] << ", ";
        if (array[i] > max) max = array[i];

        if ((i + 1) % 5 == 0){
            cout << "max: " << max << endl;
            max = 0;
        }
    }
    if (size % 5 != 0)
        cout << "Naslednji podatek bo cez " <<  (5 - (size % 5)) << " dan/dni";
}

void printMin(const unsigned int* array, const unsigned int size){
    int min = INT_MAX;
    for (int i = 0; i < size; ++i) {
        if (array[i] < min) min = array[i];
    }
    cout << min << endl;
}

int main() {
    //const unsigned int days = 10;
    const int num = 30;
    unsigned int* activeCases = new unsigned int[num];

    srand(time(nullptr));
    fillArray(activeCases, num);

    //printMax5Days(activeCases, num);

    bool running = true;
    int selection;

    do {
        menu();
        cin >> selection;
        switch (selection) {
            case 1:
                fillArray(activeCases, num);
                break;
            case 2:
                printArray(activeCases, num);
                break;
            case 0:
                running = false;
                break;
            case 3:
                printAvg(activeCases, num);
                break;
            case 4:
                printAboveAverage(activeCases, num);
                break;
            case 5:
                printPercentage(activeCases, num);
                break;
            case 6:
                printNum(activeCases, num);
                break;
            case 7:
                printMin(activeCases, num);
                break;
            default:
                cout << "Wrong selection!" << endl;
                break;
        }
        cout << endl;
    } while (running);

    delete[] activeCases;

    return 0;
}