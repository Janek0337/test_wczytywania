#include <stdio.h>
#include <stdlib.h>
//#include "graf.h"
#include "node_list.h"


listaNodow* stworzListeNodow(){
    listaNodow* lista = malloc(sizeof(listaNodow));
    if(lista == NULL){
        fprintf(stderr,"Nie udalo sie zaalokowac pamieci na liste nodow\n");
        return NULL;
    }
    lista->n = 0;
    lista->nody = NULL;
    return lista;
}

void dodajDoListyNodow(listaNodow* lista, node_t* node){
    lista->n++;
    lista->nody = realloc(lista->nody,(lista->n)*sizeof(node_t));
    if(lista->nody == NULL){
        printf("Nie udalo sie dodac nowego elementu do tablicy\n");
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

node_t* istniejeTakiNode(listaNodow* lista, short x, short y){
    for (int i = 0; i < lista->n; i++){
        if(lista->nody[i]->x == x && lista->nody[i]->y == y) return lista->nody[i];
        return lista->nody[i];
    }
    return NULL;
}
