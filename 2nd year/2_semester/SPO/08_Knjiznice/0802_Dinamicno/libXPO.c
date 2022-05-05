#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "libXPO.h"

uint32_t deli(uint32_t a, uint32_t b){
    return (uint32_t)(a / b);
}

void niz_veliki(char* c){
    int i = 0;
    char znak = c[i];
    while(znak != '\0'){
        if(znak >= 97 && znak <= 122){
            printf("%c", znak - 32);
        }
        else printf("%c", znak);
        i++;
        znak = c[i];
    }
    printf("\n");
}