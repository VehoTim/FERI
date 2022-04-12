#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int id = 0;
    char* tel = NULL;
    char* ime = NULL;
    char* priimek = NULL;
    char* dan = NULL;
    char* mesec = NULL;
    char* leto = NULL;

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
            id = atoi(argv[i + 1]);
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

                buffer[i + 1] = tel[i];

                index++;
            }
            else{

                for (int j = index; j < 20; j++)
                {
                    index++;
                    buffer[j + 1] = '\0';
                }
                break;
            }
        }
        int por = index;
        for (int i = por; i < por + 20; i++){
            if(ime[i - por] != '\0'){

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
        for (int i = por; i < por + 20; i++){
            if(priimek[i - por] != '\0'){

                buffer[i + 1] = priimek[i - por];

                index++;
            }
            else{
                for (int j = index; j < por + 20; j++)
                {
                    index++;
                    buffer[j + 1] = '\0';
                }
                break;
            }
        }
        por = index;
        uint8_t pad;
        for (int i = por; i < por + 20; i++){
            if(dan[i - por] != '\0'){
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
        for (int i = por; i < por + 20; i++){
            if(mesec[i - por] != '\0'){
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
        for (int i = por; i < por + 5; i++){
            if(leto[i - por] != '\0'){

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

            off_t fsize = lseek(oprimek, 0, SEEK_END);
            lseek(oprimek, 0, 0);
            uint8_t *branje = (uint8_t*)malloc(fsize);
            read(oprimek, branje, fsize);
            lseek(oprimek, 0, 0);

            int iskaniI = id;

            for (int i = 0; i < fsize - 1; i++){
                if(branje[i] == ';'){
                    iskaniI--;
                    if(iskaniI == 1){
                        int j = i + 2;

                        if(tel != NULL){
                            for (int k = 0; k < 20; k++){
                                if(tel[k] != '\0'){
                                    branje[j] = tel[k];
                                    j++;
                                }
                                else{
                                    for (int l = k; l < 20; l++){
                                        branje[j] = '\0';
                                        j++;
                                    }
                                    break;
                                }
                            }
                        }
                        else j = j + 20;
                        
                        
                        if(ime != NULL){
                            for (int k = 0; k < 20; k++){
                                if(ime[k] != '\0'){
                                    branje[j] = ime[k];
                                    j++;
                                }
                                else{
                                    for (int l = k; l < 20; l++){
                                        branje[j] = '\0';
                                        j++;
                                    }
                                    break;
                                }
                            }
                        }
                        else j = j + 20;
                        
                        if(priimek != NULL){
                            for (int k = 0; k < 20; k++){
                                if(priimek[k] != '\0'){
                                    branje[j] = priimek[k];
                                    j++;
                                }
                                else{
                                    for (int l = k; l < 20; l++){
                                        branje[j] = '\0';
                                        j++;
                                    }
                                    break;
                                }
                            }
                        }
                        else j = j + 20;
                        
                        uint8_t pad;
                        if(dan != NULL){
                            for (int k = 0; k < 3; k++){
                                if(dan[k] != '\0'){

                                    printf("k: %d", k);

                                    printf("j: %d", j);

                                    if(k == 0){
                                        branje[j] = '0';
                                        pad = dan[k];
                                        j++;
                                    }
                                    else{
                                        branje[j] = dan[k];
                                        branje[j - 1] = pad;
                                        j++;
                                    }
                                }
                                else {
                                    if((k) == 1){
                                        branje[j] = pad;
                                        j++;
                                        
                                        branje[j] = '.';
                                        j++;
                                        break;
                                    }
                                    else branje[j] = '.';
                                    j++;
                                    break;
                                }
                            }
                        }
                        else j = j + 3;
                        
                        
                        if(mesec != NULL){
                            for (int k = 0; k < 3; k++){
                                if(mesec[k] != '\0'){
                                    if(k == 0){
                                        branje[j] = '0';
                                        pad = mesec[k];
                                    }
                                    else{
                                        branje[j] = mesec[k];
                                        branje[j - 1] = pad;
                                    }
                                    j++;
                                }
                                else {
                                    if((k) == 1){
                                        branje[j] = pad;
                                        j++;
                                        
                                        branje[j] = '.';
                                        j++;
                                        break;
                                    }
                                    else branje[j] = '.';
                                    j++;
                                    break;
                                }
                            }
                        }
                        else j = j + 3;

                        
                        if(leto != NULL){
                            for (int k = 0; k < 5; k++){
                                if(leto[k] != '\0'){

                                    branje[j] = leto[k];

                                    j++;
                                }
                                else {
                                    j++;
                                    break;
                                }
                            }
                        }

                        j = j + 5;
                        
                        write(oprimek, branje, fsize);
                        
                        break;
                    }
                }
            }
            free(branje);
        }
        else{
            //brisemo
            off_t fsize = lseek(oprimek, 0, SEEK_END);
            lseek(oprimek, 0, 0);
            uint8_t *branje = (uint8_t*)malloc(fsize);
            read(oprimek, branje, fsize);
            lseek(oprimek, 0, 0);

            int iskaniI = id;

            for (int i = 0; i < fsize - 1; i++){
                if(branje[i] == ';'){
                    iskaniI--;
                    if(iskaniI == 1){
                        int j = i + 2;
                        while (branje[j] != ';'){
                            branje[j] = '\0';
                            j++;
                        }
                        
                        write(oprimek, branje, fsize);
                        
                        break;
                    }
                }
            }
            
        }
    }
    else if(ime != NULL || priimek != NULL){
        //iscemo

        off_t fsize = lseek(oprimek, 0, SEEK_END);

        lseek(oprimek, 0, 0);

        int loop = 0;

        while (loop < fsize - 1){

            char* cur = malloc(72);

            read(oprimek, cur, 72);

            int pos = 0;
            int k = 20;

            if(ime != NULL) {
                k = strlen(ime);
                for (int i = 21; i < 41; i++){
                    if(ime[pos] == cur[i]) {
                        pos++;
                        if(pos == k) break;
                    }
                    else pos = 0;
                }
                //izpisemo tega
            }

            if(pos == k){
                uint16_t beri = 1;
                printf("%d\t", cur[0]);
                uint8_t tab = 20;
                while(beri < 72){
                    printf("%c", cur[beri]);
                    beri++;
                    tab--;
                    if(tab == 0){
                        printf("\t");
                        tab = 20;
                    }
                }
                printf("\n");

                loop = loop + 72;
                continue;
            }

            k = 20;
            pos = 0;

            if(priimek != NULL) {
                k = strlen(priimek);
                for (int i = 41; i < 61; i++){
                    if(priimek[pos] == cur[i]) {
                        pos++;
                        if(pos == k) break;
                    }
                    else pos = 0;
                }
                //izpisemo tega
            }
            if(pos == k){
                uint16_t beri = 1;
                printf("%d\t", cur[0]);
                uint8_t tab = 20;
                while(beri < 72){
                    printf("%c", cur[beri]);
                    beri++;
                    tab--;
                    if(tab == 0){
                        printf("\t");
                        tab = 20;
                    }
                }
                printf("\n");

                loop = loop + 72;
                continue;
            }
            free(cur);

            loop = loop + 72;
        }
        
        
    }
    else{
        off_t fsize = lseek(oprimek, 0, SEEK_END);

        lseek(oprimek, 0, SEEK_SET);
        
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