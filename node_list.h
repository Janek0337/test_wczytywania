#ifndef _NODE_LIST_H
#define _NODE_LIST_H
#include "graf.h"

typedef struct lista{
    int n;
    node_t** nody;
}listaNodow;

listaNodow* stworzListeNodow();
void dodajDoListyNodow(listaNodow* lista, node_t* node);
void zwolnijListeNodow(listaNodow* lista);
node_t* istniejeTakiNode(listaNodow* lista, short x, short y);


#endif