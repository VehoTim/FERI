#include "podatki.h"

int main(){
    uint16_t* pomnilnik = rezerviraj(128);
    vstavi(pomnilnik);
    izpis(pomnilnik);
    brisi(pomnilnik);
    return 0;
}