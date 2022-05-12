#include <iostream>

using namespace std;

//funkcija za preverjanje nezadostnosti vnesenega stevila
bool isDeficientNumber(int st){
    int sum = 0;

    //z zanko preverimo ali je ostanek pri deljenju enak 0
    for (int i = 1; i <= st/2; ++i) {
        //ce je stevilo delitelj ga pristeje skupku
        if(st%i==0) sum+=i;
    }

    //ce je skupek manjsi od stevila vrne true, drugace false
    return sum < st;
}

//funkcija za preverjanje ali je stevilo prastevilo
bool isPrimeNumber(int num) {
    int numOfDividers = 0;

    //Z zanko gre do korena vnesenega stevila in poveca num deliteljev
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            numOfDividers++;

            //Ce je stevilo delitevljev vec kot 0 konca zanko
            if (numOfDividers > 0) break;
        }
    }

    //stevilo je prastevilo takrat, ko je num deliteljev = 0 in hkrati je stevilo vecje od 1
    if (num > 1 && numOfDividers == 0) {
        return true;
    }

    else return false;
}

void printPrime(int st){
    cout << "Prastevila, ki so manjsa ali enaka stevilu " << st << ": ";
    //z zanko preverimo vsa stevila
    for (int i = 1; i <= st; ++i) {
        //ce je stevilo i prastevilo ga izpise
        if(isPrimeNumber(i)){
            cout << i << ", ";
        }
    }
    cout << endl;
}


void order3(int&a,int&b,int&c){
    int tmp;
    if (b<a){
        tmp = b;
        b = a;
        a = tmp;
    }

    if (c<b){
        tmp = b;
        b = c;
        c = tmp;

        if (b<a){
            tmp = b;
            b = a;
            a = tmp;
        }
    }
}

void printDeficientBetween(int lBound, int rBound){
    for (int i = lBound; i <= rBound; ++i) {
        if (isDeficientNumber(i)) cout << i << " ";
    }
}

int main() {
    int num;
    do {
        cout << "Vnesite stevilo: ";
        cin >> num;

        //klic funkcije za izpis
        printPrime(num);
    }while(isDeficientNumber(num));

    cout << "Stevilo " << num << " ni nezadostno stevilo. Zato se je program zakljucil." << endl;

    int a = 5;
    int b = 10;
    int c = 2;

    order3(a,b,c);
    cout << a << " " << b << " " << c << endl;

    printDeficientBetween(10,40);


    return 0;
}
