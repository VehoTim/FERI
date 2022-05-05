#include "libXPO.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    niz_veliki(argv[1]);

    uint32_t rezultat = deli(atoi(argv[2]), atoi(argv[3]));

    printf("rezultat: %d", rezultat);

    return 0;
}