#ifndef _NODE_LIST_H
#define _NODE_LIST_H
//#include "graf.h"
typedef struct n {
  short x, y;
  struct n **links;
  char count;
} node_t;

typedef struct lista{
    int n;
    node_t** nody;
}*listaNodow;

listaNodow stworzListeNodow();
void dodajDoListyNodow(listaNodow lista, node_t* n);
void zwolnijListeNodow(listaNodow lista);
listaNodow istniejeTakiNode(listaNodow lista, node_t* n);


#endif