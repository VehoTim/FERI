#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int id = 0;
    char* tel;
    char* ime;
    char* priimek;
    char* dan;
    char* mesec;
    char* leto;

    int oprimek = -1;

    for (int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-c") == 0){
            creat("xpo.dat", 0644);
            return 0;
        }
    }

    for (int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-o") == 0){
            oprimek = atoi(argv[i + 1]);
            break;
        }
    }

    if(oprimek == -1) {
        printf("Prosim vnesi oprimek");
        return 0;
    }

    for (int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-id") == 0){
            id = (int)argv[i + 1];
            i++;
        }
        if(strcmp(argv[i], "-tel") == 0){
            tel = argv[i + 1];
            i++;
        }
        if(strcmp(argv[i], "-ime") == 0){
            ime = argv[i + 1];
            i++;
        }
        if(strcmp(argv[i], "-priimek") == 0){
            priimek = argv[i + 1];
            i++;
        }
        if(strcmp(argv[i], "-dan") == 0){
            dan = argv[i + 1];
            i++;
        }
        if(strcmp(argv[i], "-mesec") == 0){
            mesec = argv[i + 1];
            i++;
        }
        if(strcmp(argv[i], "-leto") == 0){
            leto = argv[i + 1];
            i++;
        }
    }

    if(tel != NULL && ime != NULL && priimek != NULL && dan != NULL && mesec != NULL && leto != NULL){

        off_t fsize = lseek(oprimek,0,SEEK_END);
        
        lseek(oprimek, 0, 0);

        int stevilo = 1;

        uint8_t * buffer;

        //ce datoteka ze ima vsebino
        if(fsize > 0){
            buffer = (uint8_t*)malloc(fsize);
            read(oprimek, buffer, fsize);

            int i = 0;
            stevilo = buffer[0];
            while(i < fsize){
                if(buffer[i - 1] == ';') {
                    stevilo = buffer[i];
                }
                i++;
            }
            free(buffer);
            stevilo++;
        }

        buffer = (uint8_t*)malloc(121 * sizeof(char) + sizeof(uint8_t));

        buffer[0] = stevilo;

        char* byte;

        int index = 0;

        for (int i = 0; i < 20; i++){
            if(tel[i] != '\0'){
                /*byte = charToBin(tel[i]);
                printf("%c = ", tel[i]);
                for (int j = 0; j < 8; j++)
                {
                    printf("%c " , byte[j]);
                    buffer[i + 1 + j] = byte[j];
                }
                printf("\n");*/

                buffer[i + 1] = tel[i];

                index++;
            }
            else{

                for (size_t j = index; j < 20; j++)
                {
                    index++;
                    buffer[j + 1] = '\0';
                }
                break;
            }
        }
        int por = index;
        for (size_t i = por; i < por + 20; i++){
            if(ime[i - por] != '\0'){
                /*byte = charToBin(ime[i - por]);
                printf("%c = ", ime[i - por]);
                for (int j = 0; j < 8; j++)
                {
                    printf("%c " , byte[j]);
                    buffer[i + 1 + j] = byte[j];
                }
                printf("\n");*/

                buffer[i + 1] = ime[i - por];

                index++;
            }
            else{
                for (size_t j = index; j < por + 20; j++)
                {
                    index++;
                    buffer[j + 1] = '\0';
                }
                break;
            }
        }
        por = index;
        for (size_t i = por; i < por + 20; i++){
            if(priimek[i - por] != '\0'){
                /*byte = charToBin(priimek[i - por]);
                printf("%c = ", priimek[i - por]);
                for (int j = 0; j < 8; j++)
                {
                    printf("%c " , byte[j]);
                    buffer[i + 1 + j] = byte[j];
                }
                printf("\n");*/

                buffer[i + 1] = priimek[i - por];

                index++;
            }
            else{
                for (size_t j = index; j < por + 20; j++)
                {
                    index++;
                    buffer[j + 1] = '\0';
                }
                break;
            }
        }
        por = index;
        uint8_t pad;
        for (size_t i = por; i < por + 20; i++){
            if(dan[i - por] != '\0'){

                /*byte = charToBin(dan[i - por]);
                printf("%c = ", dan[i - por]);
                for (int j = 0; j < 8; j++)
                {
                    printf("%c " , byte[j]);
                    buffer[i + 1 + j] = byte[j];
                }
                printf("\n");*/
                if(i == por){
                    buffer[i + 1] = '0';
                    pad = dan[i - por];
                }
                else{
                    buffer[i + 1] = dan[i - por];
                    buffer[i] = pad;
                }

                index++;
            }
            else {
                if(por + 2 != index){
                    buffer[i + 1] = pad;
                    index++;
                    
                    buffer[i + 2] = '.';
                }
                else buffer[i + 1] = '.';
                index++;
                break;
            }
        }
        por = index;
        for (size_t i = por; i < por + 20; i++){
            if(mesec[i - por] != '\0'){

                /*byte = charToBin(dan[i - por]);
                printf("%c = ", dan[i - por]);
                for (int j = 0; j < 8; j++)
                {
                    printf("%c " , byte[j]);
                    buffer[i + 1 + j] = byte[j];
                }
                printf("\n");*/
                if(i == por){
                    buffer[i + 1] = '0';
                    pad = mesec[i - por];
                }
                else{
                    buffer[i + 1] = mesec[i - por];
                    buffer[i] = pad;
                }

                index++;
            }
            else {
                if(por + 2 != index){
                    buffer[i + 1] = pad;
                    index++;
                    
                    buffer[i + 2] = '.';
                }
                else buffer[i + 1] = '.';
                index++;
                break;
            }
        }
        por = index;
        for (size_t i = por; i < por + 5; i++){
            if(leto[i - por] != '\0'){
                /*byte = charToBin(mesec[i - por]);
                printf("%c = ", mesec[i - por]);
                for (int j = 0; j < 8; j++)
                {
                    printf("%c " , byte[j]);
                    buffer[i + 1 + j] = byte[j];
                }
                printf("\n");*/

                buffer[i + 1] = leto[i - por];

                index++;
            }
            else {
                buffer[i + 1] = ';';
                index++;
                break;
            }
        }

        write(oprimek, buffer, index * sizeof(char) + sizeof(uint8_t));
        
        free(buffer);

        return 0;
    }
    else if(id != 0){
        if(tel != NULL || ime != NULL || priimek != NULL || dan != NULL || mesec != NULL || leto != NULL){
            //urejamo
        }
        else{
            //brisemo
        }
    }
    /*else if(ime != NULL || priimek != NULL){
        //iscemo
    }*/
    else{

        printf("Tukaj");

        off_t fsize = lseek(oprimek, 0, SEEK_END);

        lseek(oprimek, 0, 0);
        
        if(fsize != 0){
            uint8_t *branje = (uint8_t*)malloc(fsize);

            read(oprimek, branje, fsize);

            uint16_t i = 1;
            printf("%d", branje[0]);
            while(i < fsize - 1){
                if(branje[i] == ';'){
                    printf(";%d", branje[i + 1]);
                    i += 2;
                    continue;
                }
                printf("%c", branje[i]);
                i++;
            }
            free(branje);
        }
    }
    return 0;
}