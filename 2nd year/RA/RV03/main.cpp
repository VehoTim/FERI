#include <iostream>

using namespace std;

void printMeni(){
    cout << "Meni:" << endl;
    cout << "1) Dekodiranje" << endl;
    cout << "2) Kodiranje" << endl;
    cout << "0) Izhod" << endl;
    cout << endl << "Izbira: ";
}

bool preveriZnak(int i){
    if(i > 1114111){
        cout << "Znak ne obstaja" << endl;
        return false;
    }
    else if(i == 32){
        cout << "Vpisan znak 32 (space)" << endl;
    }
    else if(i == 127){
        cout << "Vpisan znak 127 (delete)" << endl;
    }
    else cout << "Vpisan znak: " << char(i) << endl;
    return true;
}

bool preveriZnak2(string s){
    if (s.length() == 2 && toupper(s[0]) =='F' && (toupper(s[1]) =='F' || toupper(s[1]) =='E')) return false;
    return true;
}

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
    byte2[0] = byte3[0] = byte4[0] = 1;
    byte2[1] = byte3[1] = byte4[1] = 0;
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
    cout << endl;
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

    if (char(vrednost) == 32) cout << "Vnesen znak je presledek (32)" << endl;
    else if (char(vrednost) == 127) cout << "Vnesen znak je delete (127)" << endl;
    else if (vrednost > 1114111) cout << "Vnesen znak ne obstaja." << endl;
    else cout << "Vnesen znak je " << vrednost  << endl;
}

int main() {
    bool nadaljuj = true;
    int izbira;
    int kodZnak = 0;
    string dekZnak;
    do {
        printMeni();
        cin >> izbira;

        switch (izbira) {
            case 1:
                cout << "Vpisi znak v obliki desetiskega stevila:";
                cin >> kodZnak;
                if (preveriZnak(kodZnak)) printKodiranje(kodZnak);
                break;
            case 2:
                cout << "Vpisi znak v obliki heksadecimalnega stevila:";
                cin.ignore();
                getline(cin, dekZnak);
                printDekodiranje(dekZnak);
                break;
            case 0:
                nadaljuj = false;
                break;
            default:
                cout << "Napacen vnos poskusi povnovno" << endl;
                break;
        }
    }while(nadaljuj);

    return 0;
}
