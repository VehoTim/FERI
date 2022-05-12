#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

//TODO memory leak?

//iz argumentov preberemo heksimalno vrednost
//vrnemo decimalno vrednost v obliki int
int preberiVhod(char* cmd[]){
    char* c = cmd[1];
    int st = 0;
    int potenca;
    int length = 0;

    //najprej preverimo dolzino vnosa
    for (size_t i = 0; isdigit(c[i]) || isalpha(c[i]); i++){
        length++;
    }

    for (int i = 0; i < length; i++){

        int power = 1;
        int exp = length - (i + 1);

        while (exp != 0) {
            power *= 16;
            --exp;
        }

        if(isdigit(c[i])){
            int mn = c[i] - '0';
            st += mn * power;
        }
        else if (c[i] > 64 && c[i] < 91){
            st += (c[i] - 'A' + 10) * power;
        }
        else if(c[i] > 96 && c[i]  < 123){
            st += (c[i] - 'a' + 10) * power;
        }
    }
    
    return st;
}

//znak pretvorimo iz decimalne oblike v UTF8 binarno obliko in nato v decimalno
int pretvoriZnak(int znak){
    int vrednost = 0;
    //bajti za utf8 obliko
    bool byte1[8];
    bool byte2[8];
    bool byte3[8];
    byte2[0] = byte3[0] = true;
    byte2[1] = byte3[1] = false;
    //ce je vrednost znaka mansja od 128 bo uporabljen samo en bajt
    if(znak < 128){
        //prvi bit je 0
        byte1[0] = false;
        //nastavimo ostale bite
        for (int i = 7; i > 0; --i) {
            byte1[i] = znak % 2;
            znak = znak / 2;
        }
        //sestejemo vrednosti bitov za decimalno vrednost
        for (size_t i = 0; i < 8; i++)
        {
            vrednost += pow(2, (8 - i -1)) * byte1[i];
        }
        
    }
    //ce je vrednost znaka manjsa od 2048 bosta uporabljena 2 bajta
    else if(znak < 2048){
        //prva dva sta 1
        byte1[0] = byte1[1] = true;
        //tretji je 0
        byte1[2] = false;
        for (int i = 7; i > 1; --i) {
            byte2[i] = znak % 2;
            znak = znak / 2;
        }
        for (int i = 7; i > 2; --i) {
            byte1[i] = znak % 2;
            znak = znak / 2;
        }
        
        for (size_t i = 0; i < 8; i++)
        {
            vrednost += pow(2, (8 - i - 1)) * byte2[i];
        }
        for (size_t i = 0; i < 8; i++)
        {
            vrednost += pow(2, (16 - i - 1)) * byte1[i];
        }
    }
    //ce je vrednost znaka manjsa od 65536 bojo uporabljeni 3 bajti
    else if(znak < 65536){
        //prvi trije biti so 1
        byte1[0] = byte1[2] = byte1[1] = true;
        //cetrti je 0
        byte1[3] = false;
        for (int i = 7; i > 1; --i) {
            byte3[i] = znak % 2;
            znak = znak / 2;
        }
        for (int i = 7; i > 1; --i) {
            byte2[i] = znak % 2;
            znak = znak / 2;
        }
        for (int i = 7; i > 3; --i) {
            byte1[i] = znak % 2;
            znak = znak / 2;
        }

        for (size_t i = 0; i < 8; i++)
        {
            vrednost += pow(2, (8 - i -1)) * byte3[i];
        }
        for (size_t i = 0; i < 8; i++)
        {
            vrednost += pow(2, (16 - i -1)) * byte2[i];
        }
        for (size_t i = 0; i < 8; i++)
        {
            vrednost += pow(2, (24 - i -1)) * byte1[i];
        }
    }   

    return vrednost;
}


//izpis UTF8 vrednosti
void izpisiZnak(int znak){
    int byte1[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int byte2[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int byte3[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int tmp = znak;

    //iz decimalne vrednosti nastavimo vrednosti bajtov
    if(znak < 256 && znak > 0){
        for (int i = 7; i >= 0; --i) {
            byte1[i] = (tmp % 2);
            tmp = tmp / 2;
        }
    }
    else if(znak < 65535){
         for (int i = 7; i >= 0; --i) {
            byte2[i] = (tmp % 2);
            tmp = tmp / 2;
        }
        for (int i = 7; i >= 0; --i) {
            byte1[i] = (tmp % 2);
            tmp = tmp / 2;
        }
    }
    else if(znak < 16777215){
        for (int i = 7; i >= 0; --i) {
            byte3[i] = (tmp % 2);
            tmp = tmp / 2;
        }
        for (int i = 7; i >= 0; --i) {
            byte2[i] = (tmp % 2);
            tmp = tmp / 2;
        }
        for (int i = 7; i >= 0; --i) {
            byte1[i] = (tmp % 2);
            tmp = tmp / 2;
        }
    }

    //izpis teh bajtov
    printf("\nUTF-8 binarno: ");
    for (size_t i = 0; i < 8; i++){
        printf("%d", byte1[i]);
        if(i == 3) printf(" ");
    }
    if(byte2[0] != 0){
        printf(" ");
        for (size_t i = 0; i < 8; i++){
            printf("%d", byte2[i]);
            if(i == 3) printf(" ");
        }
        if(byte3[0] != 0){
            printf(" ");
            for (size_t i = 0; i < 8; i++){
                printf("%d", byte3[i]);
                if(i == 3) printf(" ");
            }
        }
    }
    
    //izpis v hex obliki
    printf("\n");
    printf("\nUTF-8 hex: ");
    int h = 0;
    for (size_t i = 0; i < 4; i++){
        h += pow(2, 3 - i) * byte1[i];
    }
    if(h > 9){
        if(h == 10) printf("A");
        else if(h == 11) printf("B");
        else if(h == 12) printf("C");
        else if(h == 13) printf("D");
        else if(h == 14) printf("E");
        else if(h == 15) printf("F");
    }
    else printf("%d", h);
    h = 0;
    for (size_t i = 4; i < 8; i++){
        h += pow(2, 7 - i) * byte1[i];
    }
    if(h > 9){
        if(h == 10) printf("A");
        else if(h == 11) printf("B");
        else if(h == 12) printf("C");
        else if(h == 13) printf("D");
        else if(h == 14) printf("E");
        else if(h == 15) printf("F");
    }
    else printf("%d", h);
    h = 0;
    if(byte2[0] != 0){
        for (size_t i = 0; i < 4; i++){
            h += pow(2, 3 - i) * byte2[i];
        }
        if(h > 9){
            if(h == 10) printf("A");
            else if(h == 11) printf("B");
            else if(h == 12) printf("C");
            else if(h == 13) printf("D");
            else if(h == 14) printf("E");
            else if(h == 15) printf("F");
        }
        else printf("%d", h);
        h = 0;
        for (size_t i = 4; i < 8; i++){
            h += pow(2, 7 - i) * byte2[i];
        }
        if(h > 9){
            if(h == 10) printf("A");
            else if(h == 11) printf("B");
            else if(h == 12) printf("C");
            else if(h == 13) printf("D");
            else if(h == 14) printf("E");
            else if(h == 15) printf("F");
        }
        else printf("%d", h);
        h = 0;
        if(byte3[0] != 0){
            for (size_t i = 0; i < 4; i++){
                h += pow(2, 3 - i) * byte3[i];
            }
            if(h > 9){
                if(h == 10) printf("A");
                else if(h == 11) printf("B");
                else if(h == 12) printf("C");
                else if(h == 13) printf("D");
                else if(h == 14) printf("E");
                else if(h == 15) printf("F");
            }
            else printf("%d", h);
            h = 0;
            for (size_t i = 4; i < 8; i++){
                h += pow(2, 7 - i) * byte3[i];
            }
            if(h > 9){
                if(h == 10) printf("A");
                else if(h == 11) printf("B");
                else if(h == 12) printf("C");
                else if(h == 13) printf("D");
                else if(h == 14) printf("E");
                else if(h == 15) printf("F");
            }
            else printf("%d", h);
        }
    }
    printf("\n");
}
