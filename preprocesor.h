#ifndef _PREPROCESOR_H
#define _PREPROCESOR_H

#include "graf.h"
#include "node_list.h"
typedef struct wynik{
    node_t* poczatek;
    node_t* koniec;
}wyniki;

void txtNaGraf(FILE* plik);
int main();


#endif