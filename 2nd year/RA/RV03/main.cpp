#include <iostream>

using namespace std;

int pow(int x, int p)
{
    if (p == 0) return 1;
    if (p == 1) return x;

    int tmp = pow(x, p/2);
    if (p % 2 == 0) return tmp * tmp;
    else return x * tmp * tmp;
}

void printKodiranje(int znak){
    bool byte1[8];
    bool byte2[8];
    bool byte3[8];
    bool byte4[8];
    if(znak < 128){
        byte1[0] = 0;
        for (int i = 7; i > 0; --i) {
            byte1[i] = znak % 2;
            znak = znak / 2;
        }
        cout << "UTF-8 binarna oblika: ";
        for (int i = 0; i < 8; ++i) {
            cout << byte1[i];
        }
    }
    else if(znak < 2047){
        byte1[0] = 1;
        byte1[1] = 1;
        byte1[2] = 0;
        byte2[0] = 1;
        byte2[1] = 0;
        for (int i = 7; i > 1; --i) {
            byte2[i] = znak % 2;
            znak = znak / 2;
        }
        for (int i = 7; i > 2; --i) {
            byte1[i] = znak % 2;
            znak = znak / 2;
        }
        cout << "UTF-8 binarna oblika: ";
        for (int i = 0; i < 8; ++i) {
            cout << byte1[i];
        }
        cout << " ";
        for (int i = 0; i < 8; ++i) {
            cout << byte2[i];
        }
    }
    else if(znak < 65535){
        byte1[0] = 1;
        byte1[1] = 1;
        byte1[2] = 1;
        byte1[3] = 0;
        byte2[0] = 1;
        byte2[1] = 0;
        byte3[0] = 1;
        byte3[1] = 0;
        for (int i = 7; i > 1; --i) {
            byte3[i] = znak % 2;
            znak = znak / 2;
        }
        for (int i = 7; i > 1; --i) {
            byte2[i] = znak % 2;
            znak = znak / 2;
        }
        for (int i = 7; i > 3; --i) {
            byte1[i] = znak % 2;
            znak = znak / 2;
        }
        cout << "UTF-8 binarna oblika: ";
        for (int i = 0; i < 8; ++i) {
            cout << byte1[i];
        }
        cout << " ";
        for (int i = 0; i < 8; ++i) {
            cout << byte2[i];
        }
        cout << " ";
        for (int i = 0; i < 8; ++i) {
            cout << byte3[i];
        }
    }
    else if(znak < 1114111 ){
        byte1[0] = 1;
        byte1[1] = 1;
        byte1[2] = 1;
        byte1[3] = 1;
        byte1[4] = 0;
        byte2[0] = 1;
        byte2[1] = 0;
        byte3[0] = 1;
        byte3[1] = 0;
        byte4[0] = 1;
        byte4[1] = 0;
        for (int i = 7; i > 1; --i) {
            byte4[i] = znak % 2;
            znak = znak / 2;
        }
        for (int i = 7; i > 1; --i) {
            byte3[i] = znak % 2;
            znak = znak / 2;
        }
        for (int i = 7; i > 1; --i) {
            byte2[i] = znak % 2;
            znak = znak / 2;
        }
        for (int i = 7; i > 4; --i) {
            byte1[i] = znak % 2;
            znak = znak / 2;
        }
        cout << "UTF-8 binarna oblika: ";
        for (int i = 0; i < 8; ++i) {
            cout << byte1[i];
        }
        cout << " ";
        for (int i = 0; i < 8; ++i) {
            cout << byte2[i];
        }
        cout << " ";
        for (int i = 0; i < 8; ++i) {
            cout << byte3[i];
        }
        cout << " ";
        for (int i = 0; i < 8; ++i) {
            cout << byte4[i];
        }

    }
}

void printDekodiranje(string znak){
    int vrednost = 0;
    int utez = 0;
    for (int i = znak.length() - 1; i >= 0 ; --i) {
        if (znak[i] < 58 && znak[i] != 32){
            vrednost += (znak[i] - '0') * pow(16, utez);
            utez++;
        }
        else if (znak[i] > 64 && znak[i] < 91){
            vrednost += (znak[i] - 'A' + 10) * pow(16, utez);
            utez++;
        }
        else if(znak[i] > 96 && znak[i]  < 123){
            vrednost += (znak[i] - 'a' + 10) * pow(16, utez);
            utez++;
        }
    }

    //po potrebi odstrani
    cout << "Vnesen znak je " << char(vrednost) << "(" << vrednost << ")";
}

int main() {
    int kodZnak = 0;
    cout << "Vpisi kodZnak v obliki desetiskega stevila:";
    cin >> kodZnak;
    if(kodZnak > 1114111){
        cout << "Znak ne obstaja";
        return 1;
    }
    else if(kodZnak == 32){
        cout << "Vpisan kodZnak 32 (space)" << endl;
    }
    else if(kodZnak == 127){
        cout << "Vpisan kodZnak 127 (delete)" << endl;
    }
    else cout << "Vpisan kodZnak: " << char(kodZnak) << endl;
    printKodiranje(kodZnak);

    string dekZnak;
    cout << "Vpisi kodZnak v obliki heksadecimalnega stevila:";
    getline(cin, dekZnak);
    printDekodiranje(dekZnak);
    return 0;
}
