#include <stdio.h>
#include <stdlib.h>
//#include "graf.h"
#include "node_list.h"


void stworzListeNodow(listaNodow* lista){
    lista = malloc(sizeof(*lista));
    if(lista == NULL){
        fprintf(stderr,"Nie udalo sie zaalokowac pamieci na liste nodow\n");
        return;
    }
    lista->n = 0;
    lista->nody = NULL;
}

void dodajDoListyNodow(listaNodow* lista, node_t* node){
    lista->n++;
    lista->nody = realloc(lista->nody,(lista->n)*sizeof(node_t*));
    if(lista->nody == NULL){
        fprintf(stderr,"Nie udalo sie dodac nowego elementu do tablicy\n");
        return;
    }
    lista->nody[lista->n - 1] = node;
}

void zwolnijListeNodow(listaNodow* lista){
    for(int i = 0; i < lista->n; i++){
        free(lista->nody[i]);
        free(lista->nody);
        free(lista);
    }
}

node_t* istniejeTakiNode(listaNodow* lista, node_t* n){
    for (int i = 0; i < lista->n; i++){
        if(lista->nody[i]->x == n->x && lista->nody[i]->y == n->y) return lista->nody[i];
        return lista->nody[i];
    }
    return NULL;
}
