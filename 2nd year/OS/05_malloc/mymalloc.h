#ifndef MYMALLOC_H
#define MYMALLOC_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/mman.h>

struct MyMalloc{
    int stPodatkov;
    int prostora;
    void *next;
    void *prev;
};

struct Podatki{
    int velikost;
    void *stran;
    bool uporabljen;
    void *next;
};

void* novaStran();

void* mymalloc(size_t size);

void myfree(void* alloc_ptr);

#endif


