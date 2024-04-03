#ifndef _NODY_H
#define _NODY_H
#include "graf.h"
#include "wczytajPlikTxt.h"

typedef struct lista{
    int n;
    node_t** nody;
}listaNodow;

typedef struct wynik{
    node_t* poczatek;
    node_t* koniec;
}wyniki;

int czyToNode(tab* t, short i, short j, int mode);
listaNodow* stworzNody(tab* t, listaNodow* l);
listaNodow* stworzListeNodow();
void dodajDoListyNodow(listaNodow* lista, node_t* node);
void zwolnijListeNodow(listaNodow* lista);
node_t* istniejeTakiNode(listaNodow* lista, short x, short y);
void wypiszListeNodow(listaNodow* l);

#endif