#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"

void* zacetekStrani = NULL;

//naredimo novo stran (mmap)
void* novaStran(size_t skupajVelikost){
    void* data = mmap(NULL, skupajVelikost, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED , -1, 0);
    if(data == MAP_FAILED){
        //printf("Napaka\n");
        return NULL;
    }
    else{
        //printf("Ni napake\n");
    }
    return data;
}

void* mymalloc(size_t size){
    void* trenutnaStran = NULL;
    void* prejsnjaStran = NULL;
    void* nProst = NULL;
    void* curPodatki = NULL;
    void* prejsnjiPodatki = NULL;
    size_t skupajVelikost = 0;
    size_t preko = 0;
    size_t kolikoProsto = 0;

    // ce se nimamo strani gremo sem
    if(zacetekStrani == NULL){
        //printf("if\n");
        
        //dolocimo potrebno skupno velikost
        skupajVelikost = size + sizeof(struct MyMalloc) + sizeof(struct Podatki);
        preko = skupajVelikost % getpagesize();
        if(preko > 0){
            skupajVelikost += getpagesize() - preko;
        }

        zacetekStrani = novaStran(skupajVelikost);

        if(zacetekStrani == NULL) return NULL;          //prislo je do napake

        struct MyMalloc *cur = (struct MyMalloc*) zacetekStrani;
        //----------------------------------------------------------

        //ker je prva stran ima st. podatkov 0 in nima next ter prev
        cur[0].stPodatkov = 1;
        cur[0].prostora = skupajVelikost;
        cur[0].next = NULL;
        cur[0].prev = NULL;

        nProst = zacetekStrani + sizeof(struct MyMalloc);
        //----------------------------------------------------------

        //dolocanje prostora za podatke
        struct Podatki *podatki = (struct Podatki *)nProst;
        podatki[0].velikost = size;
        podatki[0].stran = zacetekStrani; 
        podatki[0].uporabljen = true;
        podatki[0].next = NULL;
        //----------------------------------------------------------

        //vrnemo naslov
        return nProst + sizeof(struct Podatki);
    }
    // ce ze imamo dolocen zacetek strani
    else{
        //printf("else\n");
        // postavimo se na zacetek strani
        trenutnaStran = zacetekStrani;

        //loopamo skozi strani
        while (trenutnaStran != NULL){
            prejsnjaStran = trenutnaStran;      
            //iz trenutne strani dobimo MyMalloc struct, ki vsebuje podatke o strani
            struct MyMalloc *cur = (struct MyMalloc *) trenutnaStran;
            //pomaknemo se naprej in dobimo se prve vstavljene podatke
            curPodatki =  trenutnaStran + sizeof(struct MyMalloc);
            prejsnjiPodatki = NULL;

            //loopamo skozi podatke
            while(curPodatki != NULL){
                //dobimo se strukturo za te podatke, ki vsebuje info o podatkih
                struct Podatki * podatki = (struct Podatki * ) curPodatki;
                prejsnjiPodatki = curPodatki;           //pomaknili se bomo naprej
                if(podatki[0].uporabljen){              //ce so ze uporabljeni
                    curPodatki = podatki[0].next;       //pomik
                }
                else{                                   //ce niso uporabljeni
                    if(podatki[0].velikost >= size){    //preverimo velikost
                        podatki[0].uporabljen = true;   //ce dovolj prostora
                        cur[0].stPodatkov++;            //vstavimo podatke
                        return curPodatki + sizeof(struct Podatki);
                    }
                    else {                              //drugace se pomaknemo naprej
                        curPodatki = podatki[0].next;   
                    }
                }
            }
            // 
            struct Podatki* ptrPrejsnjiPodatki = (struct Podatki *) prejsnjiPodatki;
            nProst = prejsnjiPodatki + sizeof(struct Podatki) + ptrPrejsnjiPodatki[0].velikost;
            kolikoProsto = (trenutnaStran + sizeof(struct MyMalloc) + cur[0].prostora) - (nProst + sizeof(struct Podatki) + size);
            
            //odvisno od nasega prostora
            //dodamo nove vrednosti
            if(kolikoProsto <= 0){
                //nastavimo next ptr prejsnjega na novo vrednost
                ptrPrejsnjiPodatki[0].next = nProst;
                struct Podatki* ptrPodatki = (struct Podatki *)nProst;
                ptrPodatki[0].velikost = size;
                ptrPodatki[0].next = NULL;
                ptrPodatki[0].uporabljen = true;
                ptrPodatki[0].stran = trenutnaStran;
                cur[0].stPodatkov++;

                return nProst + sizeof(struct Podatki);
            }
            //ali se pa pomaknemo naprej
            else {
                trenutnaStran = cur[0].next; 
            }
        }
        // ce ne najdemo prostora za podatke naredimo novo stran

        //dolocimo potrebno skupno velikost
        skupajVelikost = size + sizeof(struct MyMalloc) + sizeof(struct Podatki);
        preko = skupajVelikost % getpagesize();
        if(preko > 0){
            skupajVelikost += getpagesize() - preko;
        }
        
        //naredimo novo stran
        void* nStran = novaStran(skupajVelikost);

        if(nStran == NULL) return NULL;          //prislo je do napake

        // nastavimo next prejsnje strani
        struct MyMalloc *ptrPrejsnjaStran = (struct MyMalloc *) prejsnjaStran;
        ptrPrejsnjaStran[0].next = nStran;
        //cur nastavimo na novo stran
        struct MyMalloc *cur = (struct MyMalloc *) nStran;
        cur[0].prev = prejsnjaStran;
        cur[0].next = NULL;
        cur[0].prostora = skupajVelikost;
        //prosto je na zacetku nove strani
        nProst = nStran + sizeof(struct MyMalloc);
        //nastavimo podatke
        struct Podatki* ptrPodatki = (struct Podatki *) nProst;
        ptrPodatki[0].next = NULL;
        ptrPodatki[0].velikost = size;
        ptrPodatki[0].uporabljen = true;
        ptrPodatki[0].stran = nStran;
        //vrnemo naslov
        return nProst + sizeof(struct Podatki);
    }
}

void myfree(void* data) {
    // naslov do potakov, ki jih bomo brisali
    struct Podatki *ptrPodatki = (struct Podatki *)(data - sizeof(struct Podatki));
    //trenutna stran
    struct MyMalloc *curStran = (struct MyMalloc *)(ptrPodatki[0].stran);
    //ce je stevilo podatkov na trenutni strani vec kot en
    if (curStran[0].stPodatkov > 1){
        curStran[0].stPodatkov--;           //odstranimo en podatek
        ptrPodatki[0].uporabljen = false;   //in oznacimo kot neuporabljeno
        return;
    }
    // ce ni prejsnje ali naslednje strani in ni vec kot 1 podatkov
    else if(curStran[0].prev == NULL && curStran[0].next == NULL){
        // brisemo stran
        munmap(ptrPodatki[0].stran, curStran[0].prostora);
        // ponastavimo zacetek strani
        zacetekStrani = NULL;
        return;
    }
    // ce naslednja stran obstaja odstranimo trenutno in se prestavimo na naslednjo
    else if(curStran[0].prev == NULL && curStran[0].next != NULL){
        //postavimo se na naslednjo stran
        zacetekStrani = curStran[0].next;
        struct MyMalloc *ptrNaslednji = (struct MyMalloc *)(curStran[0].next);
        ptrNaslednji[0].prev = NULL;
        munmap(ptrPodatki[0].stran, curStran[0].prostora);
        return;
    }
    // ce obstajata naslednja in prejsnja 
    else if(curStran[0].prev != NULL && curStran[0].next != NULL){
        //zbrisemo trenutno in povezemo prejsnjo in naslednjo
        struct MyMalloc *ptrPrejsnji = (struct MyMalloc *)(curStran[0].prev);
        ptrPrejsnji[0].next = curStran[0].next;
        struct MyMalloc *ptrNaslednji = (struct MyMalloc *)(curStran[0].next);
        ptrNaslednji[0].prev = curStran[0].prev;
        munmap(ptrPodatki[0].stran, curStran[0].prostora);
        return;
    }
    // ce ni naslednjega
    else if(curStran[0].prev != NULL && curStran[0].next == NULL){
        // next prejsnjega nastavimo na null in zbrisemo trenutnega
        struct MyMalloc *ptrPrejsnji = (struct MyMalloc *)(curStran[0].prev);
        ptrPrejsnji[0].next = NULL;
        munmap(ptrPodatki[0].stran, curStran[0].prostora);
        return;
    }
}