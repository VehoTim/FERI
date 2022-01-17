#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
    string imeo;
    string imei;
    const char* nastaveko;
    const char* nastaveki;

    string zastavica;
    vector<char> bytes;

    int oprimek;

    bool najdenaZastavica = false;
    bool najdenaZastavica_i = false;
    bool najdenaZastavica_I = false;
    bool najdenaZastavica_o = false;
    bool najdenaZastavica_O = false;

    ofstream pisanje;



    for (int i = 0; i < argc; ++i){
        zastavica = argv[i];

        if(zastavica == "-i"){
            najdenaZastavica_i = true;
            najdenaZastavica_I = false;
            imei = argv[i + 1];
            /*//cout << zastavica << "\n";
            ime = argv[i +  1];

            ifstream branje(ime, ios::binary);

            if (branje)
            {
                vector<char> b((istreambuf_iterator<char>(branje)), (istreambuf_iterator<char>()));
                bytes = b;

                branje.close();
            }

            i++;*/
        }
        if(zastavica == "-I"){
            najdenaZastavica_i = false;
            najdenaZastavica_I = true;
            nastaveki = argv[i + 1];
        }
        if(zastavica == "-o"){
            najdenaZastavica_o = true;
            najdenaZastavica_O = false;
            imeo = argv[i + 1];
        }
        if(zastavica == "-O"){
            najdenaZastavica_o = false;
            najdenaZastavica_O = true;
            nastaveko = argv[i + 1];
        }
    }    




    if(najdenaZastavica_i){
        if(najdenaZastavica_o){

            ifstream branje(imei, ios::binary);

            if (branje)
            {
                vector<char> b((istreambuf_iterator<char>(branje)), (istreambuf_iterator<char>()));
                bytes = b;

                branje.close();
            }


            pisanje.open(imeo, ios::binary);

            if (pisanje)
            {
                for(char c : bytes){
                    int k = int(c);
                    //cout << k << " " << c << endl;
                    string s = to_string(k);
                    for(char pc : s){
                        pisanje.write(&pc, 1);
                    }
                    pisanje.write(" ", 1);
                }

                pisanje.close();
            }
        }
        else if(najdenaZastavica_O){
            ifstream branje(imei, ios::binary);

            if (branje)
            {
                vector<char> b((istreambuf_iterator<char>(branje)), (istreambuf_iterator<char>()));
                bytes = b;

                branje.close();
            }

            //najdenaZastavica = true;
            //cout << zastavica << "\n";
            //char* naslov = argv[i +  1];

            write(atoi(nastaveko), bytes.data(), bytes.size());
        }
        else{
            ifstream branje(imei, ios::binary);

            if (branje)
            {
                vector<char> b((istreambuf_iterator<char>(branje)), (istreambuf_iterator<char>()));
                bytes = b;

                branje.close();
            }
            
            vector<char> ascii;
            for(char c : bytes){
                int n = (int)c;
                string s = to_string(n);

                for(char c : s){
                    ascii.push_back(c);
                }
                ascii.push_back(' ');
            }
            
            write(1, ascii.data(), ascii.size());
        }
    }
    else if(najdenaZastavica_I){
        if(najdenaZastavica_o){
            char buffer[40000];
            int nread;
            nread = read(atoi(nastaveki),buffer,40000);

            pisanje.open(imeo, ios::binary);

            if (pisanje)
            {
                for(int i = 0; i < nread; i++){
                    int k = int(buffer[i]);
                    //cout << k << " " << c << endl;
                    string s = to_string(k);
                    for(char pc : s){
                        pisanje.write(&pc, 1);
                    }
                    pisanje.write(" ", 1);
                }

                pisanje.close();
            }
        }
        else if(najdenaZastavica_O){
            char buffer[40000];
            int nread;
            nread = read(atoi(nastaveki),buffer,40000);

            vector<char> ascii;
            for(int i = 0; i < nread; i++){
                int n = (int)buffer[i];
                string s = to_string(n);

                for(char c : s){
                    ascii.push_back(c);
                }
                ascii.push_back(' ');
            }
                        
            write(atoi(nastaveko), ascii.data(), ascii.size());
        }
        else{
            char buffer[40000];
            int nread;
            nread = read(atoi(nastaveki),buffer,40000);

            vector<char> ascii;
            for(int i = 0; i < nread; i++){
                int n = (int)buffer[i];
                string s = to_string(n);

                for(char c : s){
                    ascii.push_back(c);
                }
                ascii.push_back(' ');
            }
            
            write(1, ascii.data(), ascii.size());
        }
    }
    else{
        if(najdenaZastavica_o){
            char buffer[40000];
            int nread;
            nread = read(0,buffer,40000);

            //cout << nread << endl;

            pisanje.open(imeo, ios::binary);

            if (pisanje)
            {
                for(int i = 0; i < nread; i++){
                    int k = int(buffer[i]);
                    //cout << k << " " << c << endl;
                    string s = to_string(k);
                    for(char pc : s){
                        pisanje.write(&pc, 1);
                    }
                    pisanje.write(" ", 1);
                }

                pisanje.close();
            }
        }
        else if(najdenaZastavica_O){
            char buffer[40000];
            int nread;
            nread = read(0,buffer,40000);

            vector<char> ascii;
            for(int i = 0; i < nread; i++){
                int n = (int)buffer[i];
                string s = to_string(n);

                for(char c : s){
                    ascii.push_back(c);
                }
                ascii.push_back(' ');
            }

            write(1, ascii.data(), ascii.size());
        }
        else{
            char buffer[40000];
            int nread;
            nread = read(0,buffer,40000);
            
            vector<char> ascii;
            for(int i = 0; i < nread; i++){
                int n = (int)buffer[i];
                string s = to_string(n);

                for(char c : s){
                    ascii.push_back(c);
                }
                ascii.push_back(' ');
            }
            
            write(1, ascii.data(), ascii.size());
        }
    }


    /*if(!najdenaZastavica){
        cout << "Vpisi podatke: ";
        getline(cin, ime);
        
        vector<char> b(ime.begin(), ime.end());

        bytes = b;
    }

    najdenaZastavica = false;
    for (int i = 0; i < argc; ++i) {
        zastavica = argv[i];

        if(zastavica == "-o"){
            najdenaZastavica = true;
            //cout << zastavica << "\n";
            ime = argv[i +  1];

            pisanje.open(ime, ios::binary);

            if (pisanje)
            {
                for(char c : bytes){
                    int k = int(c);
                    //cout << k << " " << c << endl;
                    string s = to_string(k);
                    for(char pc : s){
                        pisanje.write(&pc, 1);
                    }
                    pisanje.write(" ", 1);
                }

                pisanje.close();
            }

            i++;
        }
    }

    for (int i = 0; i < argc; ++i){
        zastavica = argv[i];

        if(zastavica == "-O"){
            ime = argv[i +  1];

            najdenaZastavica = true;
            //cout << zastavica << "\n";
            char* naslov = argv[i +  1];

            write(atoi(naslov), bytes.data(), bytes.size());
            i++;
        }
    }

    for (int i = 0; i < argc; ++i){
        zastavica = argv[i];

        if(zastavica == "-I"){
            najdenaZastavica = true;
            //cout << zastavica << "\n";
            const char* naslov = argv[i +  1];
            
            bytes.clear();

            int nread = read(atoi(naslov), bytes.data(), 40000);

            cout << nread << endl;

            for(int i = 0; i < 40000; i++){
                cout << (int)bytes[i] << " ";
            }
            
            cout << endl;
            i++;
        }
    }

    if(!najdenaZastavica){
        for(char c : bytes){
            cout << (int)c << " ";
        }
        cout << endl;
    }
    */
    return 0;
}