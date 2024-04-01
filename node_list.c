#include <stdio.h>
#include <stdlib.h>
//#include "graf.h"
#include "node_list.h"


listaNodow stworzListeNodow(){
    listaNodow lista = malloc(sizeof(*lista));
    if(lista == NULL){
        fprintf(stderr,"Nie udalo sie zaalokowac pamieci na liste nodow\n");
        return NULL;
    }
    lista->n = 0;
    lista->nody = NULL;
    return lista;
}

void dodajDoListyNodow(listaNodow lista, node_t* n){
    lista->n++;
    lista->nody = realloc(lista->nody,(lista->n)*sizeof(node_t*));
    if(lista->nody == NULL){
        fprintf(stderr,"Nie udalo sie dodac nowego elementu do tablicy\n");
        return;
    }
    lista->nody[lista->n - 1] = n;
}

void zwolnijListeNodow(listaNodow lista){
    for(int i = 0; i < lista->n; i++){
        free(lista->nody[i]);
        free(lista->nody);
        free(lista);
    }
}

node_t* istniejeTakiNode(listaNodow lista, node_t* n){
    for (int i = 0; i < lista->n; i++){
        if(lista->nody[i]->x == n->x && lista->nody[i]->y == n->y) return lista->nody[i];
        return lista->nody[i];
    }
    return NULL;
}
