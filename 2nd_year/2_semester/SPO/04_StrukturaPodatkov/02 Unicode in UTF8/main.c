#include "pretvori.h"
#include "stdio.h"

int main(int argc, char *argv[]){

    int st = preberiVhod(argv);

    izpisiZnak(pretvoriZnak(st));
}