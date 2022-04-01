#include "stdio.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]){
    char id[20];
    char tel[20];
    char ime[20];
    char priimek[20];
    char dan[20];
    char mesec[20];
    char leto[20];

    for (size_t i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-c") == 0){
            open("xpo.dat", O_RDWR | O_CREAT);
        }
    }
    
}