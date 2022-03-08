#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <iterator>
#include <chrono>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

using namespace std;

int main(int argc, char** argv)
{
    string zastavica;
    int predpomnilnik;
    const char* bf;
    string tip;
    const char* ime;
    
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();

    map<char, int> histogram;

    for (int i = 0; i < argc; ++i){
        zastavica = argv[i];

        if(zastavica == "-t"){
            tip = argv[i + 1];
            i++;
        }

        if(zastavica == "-b"){
            bf = argv[i + 1];
            predpomnilnik = atoi(bf);
            i++;
        }

        else{
            ime = argv[i];
        }
    }

    if(tip == "mmap"){
        
        start = std::chrono::steady_clock::now();

        int file = open(ime, O_RDONLY);
        
        struct stat statbuf;
        int err = fstat(file, &statbuf);

        char *ptr = (char*)mmap(NULL,statbuf.st_size, PROT_READ ,MAP_SHARED, file ,0);

        for(int i = 0; i < statbuf.st_size; i++){
            if ( histogram.find(ptr[i]) == histogram.end() ) {
                histogram.insert({ptr[i], 1});
            } else {
                map<char, int>::iterator it = histogram.find(ptr[i]);  
                it->second = it->second + 1;
            }
        }

        munmap((int*)ptr, statbuf.st_size);

        for (auto itr = histogram.begin(); itr != histogram.end(); ++itr) {
            cout << "\"" << itr->first << "\""
             << " - " << itr->second << '\n';
        }

        end = std::chrono::steady_clock::now();

        cout << "Cas read: " << std::chrono::duration_cast<std::chrono::microseconds>
            (end - start).count() << "μs." << std::endl;
    }
    else if(tip == "fread"){
        
        start = std::chrono::steady_clock::now();

        ifstream branje(ime, ios::binary);

        bool konec = false;

        // get length of file:
        branje.seekg (0, branje.end);
        int length = branje.tellg();
        branje.seekg (0, branje.beg);

        char * buffer = new char [length];

        while(branje){

            //if(length > predpomnilnik) cout << "Berem " << predpomnilnik << " znakov... " << endl;
            //else cout << "Berem " << length << " znakov... " << endl;

            branje.read(buffer, predpomnilnik);

            for(int j = 0; j < predpomnilnik; j++){
                if ( histogram.find(buffer[j]) == histogram.end() ) {
                    histogram.insert({buffer[j], 1});
                } else {
                    map<char, int>::iterator it = histogram.find(buffer[j]);  
                    it->second = it->second + 1;
                }
                length--;
            }
            
            if(length <= 0)
                break;

            branje.seekg(0, branje.cur);
        }

        for (auto itr = histogram.begin(); itr != histogram.end(); ++itr) {
            cout << "\"" << itr->first << "\""
             << " - " << itr->second << '\n';
        }

        branje.close();

        delete[] buffer;
        
        end = std::chrono::steady_clock::now();

        cout << "Cas fread (ifstream): " << std::chrono::duration_cast<std::chrono::microseconds>
            (end - start).count() << "μs." << std::endl;
    }
    else if(tip == "read"){
        
        start = std::chrono::steady_clock::now();

        bool konec = false;

        int file = open(ime, O_RDONLY);

        char buffer[predpomnilnik];

        while(true){

            ssize_t r = read(file, buffer, predpomnilnik);
            
            for(int j = 0; j < predpomnilnik; j++){
                if ( histogram.find(buffer[j]) == histogram.end() ) {
                    histogram.insert({buffer[j], 1});
                } else {
                    map<char, int>::iterator it = histogram.find(buffer[j]);  
                    it->second = it->second + 1;
                }

                if(r == 0) {
                    konec = true;
                    break;
                }
            }
            if(konec){
                break;
            }
        }

        close(file);

        for (auto itr = histogram.begin(); itr != histogram.end(); ++itr) {
            cout << "\"" << itr->first << "\""
             << " - " << itr->second << '\n';
        }
        
        end = std::chrono::steady_clock::now();

        cout << "Cas read: " << std::chrono::duration_cast<std::chrono::microseconds>
            (end - start).count() << "μs." << std::endl;
    }
}