#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char *argv[]){

    //spremenljivke
    void* handle = NULL;
    void (*nizVeliki)(char*);
    uint32_t (*funDeli)(uint32_t,uint32_t);

    //odpremo knjiznico
    handle = dlopen("./libXPO.so",RTLD_LAZY);

    //poiscemo funkcijo niz veliki
    nizVeliki = (void(*)(char*))dlsym(handle,"niz_veliki");

    //izvedemo funkcijo
    nizVeliki(argv[1]);

    //poiscemo funkcijo deli 
    funDeli=(uint32_t(*)(uint32_t,uint32_t))dlsym(handle,"deli");

    //izvedemo funkcijo
    uint32_t rezultat = funDeli(atoi(argv[2]), atoi(argv[3]));

    printf("rezultat: %d", rezultat);

    //zapremo knjiznico
    dlclose(handle);

    return 0;
}