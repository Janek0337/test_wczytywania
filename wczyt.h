#ifndef _WCZYTAJ_LABIRYNT_DOBRE_H
#define _WCZYTAJ_LABIRYNT_DOBRE_H
#include <stdio.h>
//#include "graf.h"
typedef struct _tab{
    short r,c;
    char** buf;
}tab;


short* wyznaczRozmiarLabiryntu(FILE* plik);
tab* stworzTablice(short* rozmiar);
void zwolnijTablice(tab* t);
void wczytajPlikTxtDoTablicy(FILE* plik, tab* t);
int czyDobryZnak(char c);
void wypiszTablice(tab* t);
listaNodow stworzNody(tab* t, listaNodow* lista);
#endif
