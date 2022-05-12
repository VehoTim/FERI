#include "podatki.h"
#include "math.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

uint16_t* rezerviraj(int velikostZlogi){
    uint16_t* pos = (uint16_t*)malloc(velikostZlogi);
    for (size_t i = 0; i < (velikostZlogi / sizeof(int)); i++)
    {
        pos[i] = 24562;
    }
    
    return pos;
}

void brisi(uint16_t* pomnilnik){
    free(pomnilnik);
}

uint16_t* vstavi(uint16_t* pomnilnik){
    *(char *)&pomnilnik[0] = 'X';
    *(char *)&pomnilnik[1] = 'P';
    *(char *)&pomnilnik[2] = 'O';
    *(float *)&pomnilnik[3] = (float)M_PI;
    *(int32_t *)&pomnilnik[7] = 24562;
    *(char *)&pomnilnik[11] = '!';
}

void izpis(uint16_t* pomnilnik){
    printf("%c\n", (char)pomnilnik[0]);
    printf("%c\n", (char)pomnilnik[1]);
    printf("%c\n", (char)pomnilnik[2]);
    printf("%.8f\n", (float) *(float *)&pomnilnik[3]);
    printf("%d\n", (int32_t)pomnilnik[7]);
    printf("%c\n", (char)pomnilnik[11]);
}