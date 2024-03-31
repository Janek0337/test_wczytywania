#ifndef _WCZYTAJ_LABIRYNT_DOBRE_H
#define _WCZYTAJ_LABIRYNT_DOBRE_H
#include <stdio.h>
//#include "graf.h"
typedef struct _tab{
    short r,c;
    char** buf;
}tab;


short* wyznaczRozmiar (FILE* plik);
tab* stworzTablice(short* rozmiar);
void zwolnijTablice(tab* t);
void wczytajPlik(FILE* plik, tab* t);
int czyDobryZnak(char c);
void wypisz(tab* t);
#endif
