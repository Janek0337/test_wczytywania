#ifndef _WCZYTAJ_PLIK_TXT_H
#define _WCZYTAJ_PLIK_TXT_H

typedef struct _tab{
    short r,c;
    char** buf;
}tab;

#include <stdio.h>
#include "nody.h"
#include "graf.h"

short* wyznaczRozmiarLabiryntu(FILE* plik);
tab* stworzTablice(short* rozmiar);
void zwolnijTablice(tab* t);
int wczytajPlikTxtDoTablicy(FILE* plik, tab* t);
int czyDobryZnak(char c);
void wypiszTablice(tab* t);
int jedenZeZnakow(tab*t, short i, short j);
int zprawej(tab* t,short i, short j);
int zlewej(tab* t,short i, short j);
int zgory(tab* t,short i, short j);
int zdolu(tab* t,short i, short j);
#endif
