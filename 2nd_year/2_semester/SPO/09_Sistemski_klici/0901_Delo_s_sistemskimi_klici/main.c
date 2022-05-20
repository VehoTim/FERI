#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <syscall.h>

int main(){   

    char* imenik = "XPOimenik";
    char* datoteka = "XPOdatoteka.dat";
    //int pid = 0;
    __asm__ __volatile__(
        "mov    $0x27, %%eax\n"
        "int    $0x80\n"
        :: "b"(imenik), "c"(0777)
    );

    __asm__ __volatile__(
        "mov    $0x24, %%eax\n"
        "int    $0x80\n"
        ::
    );

    __asm__ __volatile__(
        "mov    $0x0c, %%eax\n"
        "int    $0x80\n"
        :: "a"(imenik)
    );

    __asm__ __volatile__(
        "mov    $0x08, %%eax\n"
        "int    $0x80\n"
        :: "b"(datoteka), "c"(0000)
    );
    

    __asm__ __volatile__(
        "mov    $0x24, %%eax\n"
        "int    $0x80\n"
        ::
    );

    __asm__ __volatile__(
        "mov    $0x0f, %%eax\n"
        "int    $0x80\n"
        :: "b"(datoteka), "c"(0640)
    );

    return 0;
}