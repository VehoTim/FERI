#include<stdio.h>
#include"mymalloc.h"

int main(void) {
    void* addr = mymalloc(10);
    void* add = mymalloc(4043);
    void* ad = mymalloc(15);
    myfree(add);
    myfree(addr);
    myfree(ad);
    void* ad1 = mymalloc(10000);
    void* ad2 = mymalloc(4043);
    void* ad3 = mymalloc(15);
    myfree(ad2);
    myfree(ad1);
    myfree(ad3);
    void* ad4 = mymalloc(10);
    void* ad5 = mymalloc(4043);
    void* ad6 = mymalloc(1345);
    void* ad7 = mymalloc(374);
    void* ad8 = mymalloc(443);
    void* ad9 = mymalloc(115);
    myfree(ad6);
    myfree(ad4);
    myfree(ad7);
    myfree(ad5);
    myfree(ad8);
    myfree(ad9);
    return 0;
}