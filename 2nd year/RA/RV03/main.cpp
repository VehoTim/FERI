#include <iostream>

using namespace std;

//izpis menija
void printMeni(){
    cout << "Meni:" << endl;
    cout << "1) Kodiranje" << endl;
    cout << "2) Dekodiranje" << endl;
    cout << "0) Izhod" << endl;
    cout << endl << "Izbira: ";
}

//preverjanje znaka pri kodiranju
bool preveriZnak(unsigned int i){
    if(i > 1114111){
        cout << "Znak ne obstaja" << endl;
        return false;
    }
    else if(i == 32) cout << "Vpisan znak 32 (space)" << endl;
    else if(i == 127) cout << "Vpisan znak 127 (delete)" << endl;
    else cout << "Vpisan znak: " << char(i) << endl;
    return true;
}

//preverjanje oblike UTF pri dekodiranju
bool preveriUTF(unsigned int utf){
    bool byte1[8];
    bool byte2[8];
    bool byte3[8];
    bool byte4[8];
    unsigned int tmp = utf;

    if(utf < 256 && utf > 0){
        for (int i = 7; i >= 0; --i) {
            byte1[i] = tmp % 2;
            tmp = tmp / 2;
        }

        if (byte1[0] == 1) return false;
        else return true;
    }
    else if(utf < 65535){
        for (int i = 7; i >= 0; --i) {
            byte2[i] = tmp % 2;
            tmp = tmp / 2;
        }
        for (int i = 7; i >= 0; --i) {
            byte1[i] = tmp % 2;
            tmp = tmp / 2;
        }
        if((byte1[0] == 0 || byte1[1] == 0 || byte1[2] == 1 || byte2[0] == 0 || byte2[1] == 1) || (utf - 49280) <= 0) return false;
        else return true;
    }
    else if(utf < 16777215){
        for (int i = 7; i >= 0; --i) {
            byte3[i] = tmp % 2;
            tmp = tmp / 2;
        }
        for (int i = 7; i >= 0; --i) {
            byte2[i] = tmp % 2;
            tmp = tmp / 2;
        }
        for (int i = 7; i >= 0; --i) {
            byte1[i] = tmp % 2;
            tmp = tmp / 2;
        }

        if((byte1[0] == 0 || byte1[1] == 0 || byte1[2] == 0 || byte1[3] == 1 || byte2[0] == 0 || byte2[1] == 1 ||
           byte3[0] == 0 || byte3[1] == 1) || (utf - 14712960) <= 0) return false;
        else return true;
    }
    else if(utf < 4294967295 ){
        for (int i = 7; i >= 0; --i) {
            byte4[i] = tmp % 2;
            tmp = tmp / 2;
        }
        for (int i = 7; i >= 0; --i) {
            byte3[i] = tmp % 2;
            tmp = tmp / 2;
        }
        for (int i = 7; i >= 0; --i) {
            byte2[i] = tmp % 2;
            tmp = tmp / 2;
        }
        for (int i = 7; i >= 0; --i) {
            byte1[i] = tmp % 2;
            tmp = tmp / 2;
        }

        if((byte1[0] == 0 || byte1[1] == 0 || byte1[2] == 0 || byte1[3] == 0 || byte1[4] == 1 || byte2[0] == 0 ||
           byte2[1] == 1 || byte3[0] == 0 || byte3[1] == 1 || byte4[0] == 0 || byte4[1] == 1) || (utf - 4034953344) <= 0)
                return false;
        else return true;
    }
    else return false;
}

//funkcija za potenciranje
int pow(int x, int p)
{
    if (p == 0) return 1;
    if (p == 1) return x;

    int tmp = pow(x, p/2);
    if (p % 2 == 0) return tmp * tmp;
    else return x * tmp * tmp;
}

//izpis kodiranja (vnese se decimalno stevilo in izhod je binarni utf izpis)
void printKodiranje(unsigned int znak){
    bool byte1[8];
    bool byte2[8];
    bool byte3[8];
    bool byte4[8];
    byte2[0] = byte3[0] = byte4[0] = true;
    byte2[1] = byte3[1] = byte4[1] = false;
    if(znak < 128){
        byte1[0] = false;
        for (int i = 7; i > 0; --i) {
            byte1[i] = znak % 2;
            znak = znak / 2;
        }
        cout << "UTF-8 binarna oblika: ";
        for (bool b : byte1) cout << b;
    }
    else if(znak < 2048){
        byte1[0] = byte1[1] = true;
        byte1[2] = false;
        for (int i = 7; i > 1; --i) {
            byte2[i] = znak % 2;
            znak = znak / 2;
        }
        for (int i = 7; i > 2; --i) {
            byte1[i] = znak % 2;
            znak = znak / 2;
        }
        cout << "UTF-8 binarna oblika: ";
        for (bool b : byte1) cout << b;
        cout << " ";
        for (bool b : byte2) cout << b;
    }
    else if(znak < 65536){
        byte1[0] = byte1[2] = byte1[1] = true;
        byte1[3] = false;
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
        for (bool b : byte1) cout << b;
        cout << " ";
        for (bool b : byte2) cout << b;
        cout << " ";
        for (bool b : byte3) cout << b;
    }
    else if(znak < 1114111 ){
        byte1[0] = byte1[1] = byte1[2] = byte1[3] = true;
        byte1[4] = false;
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
        for (bool b : byte1) cout << b;
        cout << " ";
        for (bool b : byte2) cout << b;
        cout << " ";
        for (bool b : byte3) cout << b;
        cout << " ";
        for (bool b : byte4) cout << b;
    }
    cout << endl;
}

//izpis dekodiranja (vnese se hex stevilo kot string  preveri oblika in vrne se decimalno stevilo)
void printDekodiranje(string znak){
    if(!(znak.length() == 2 && toupper(znak[0]) =='F' && (toupper(znak[1]) =='F' || toupper(znak[1]) =='E'))){

        unsigned int vrednost = 0;
        int utez = 0;
        for (unsigned int i = znak.length() - 1; i >= 0 ; --i) {
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

        if(preveriUTF(vrednost)){
            if (char(vrednost) == 32) cout << "Vnesen znak je presledek (32)" << endl;
            else if (char(vrednost) == 127) cout << "Vnesen znak je delete (127)" << endl;
            else cout << "Vnesen znak je " << char(vrednost) << "(" << vrednost << ")"  <<endl;
        }
        else cout << "Vnesen znak ne obstaja." << endl;
    }
    else cout << "Ta koda ni dovoljena za dekodiranje";
}

//glavni program
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
