#include <stdio.h>
#include <stdlib.h>
#include "graf.h"
#include "nody.h"
#include "wczytajPlikTxt.h"

int czyToNode(tab*t, short i, short j, int mode) { // zasada dzialania int mode jak chmod
    if (jedenZeZnakow(t,i,j) != 1) return 0;
    int wynik = 0;
    int gora = 0;
    int dol = 0;
    int prawo = 0;
    int lewo = 0;
    if (mode & 1) { //gora
        if (zgory(t,i,j) == 1){
             wynik++;
             gora = 1;
        }
    }
    if (mode & 2) { //prawo
        if (zprawej(t,i,j) == 1){
            wynik++;
            prawo = 1;
        }
    }
    if (mode & 4) { //dol
        if (zdolu(t,i,j) == 1){
            wynik++;
            dol = 1;
        }
    }
    if (mode & 8) { //lewo
        if (zlewej(t,i,j) == 1){
            wynik++;
            lewo = 1;
        }
    }
    if((wynik >= 3) || (t->buf[i][j] == 'P') || (t->buf[i][j] == 'K')) return 1; // to skrzyzowanie
    if (wynik == 2 && !((gora == 1 && dol == 1) || (prawo == 1 && lewo == 1))) return 1; // to zakret
    return 0;
}

listaNodow* stworzNody(tab* t, listaNodow* l){
    node_t* nodeTymaczasowy = NULL;
    l = stworzListeNodow();
    //czytam pierwszy rzad
    for(int j = 1; j < (t->c)-1; j++){
        //printf("Sprawdzam (%d,%d)\n",0,j);
        if (czyToNode(t,0,j,14) == 1){
            //printf("Dodaje noda na (0,%d)\n",j);
            nodeTymaczasowy = init_node(0,j);
            dodajDoListyNodow(l,nodeTymaczasowy);
        }
    }
    //czytam wszystko bez pierwszego i bez ostatniego rzedu
    for(int i = 1; i < (t->r)-1; i++){
        for (int j = 0; j < t->c; j++){
            //printf("Sprawdzam (%d,%d)\n",i,j);
            if(j == 0){ //lewa banda
                if(czyToNode(t,i,j,7) == 1){
                    //printf("Dodaje noda na (%d,%d)\n",i,j);
                    nodeTymaczasowy = init_node(i,j);
                    dodajDoListyNodow(l,nodeTymaczasowy);
                }
            }
            else if(j == (t->c)-1){ //prawa banda
                if(czyToNode(t,i,j,13) == 1){
                    //printf("Dodaje noda na (%d,%d)\n",i,j);
                    nodeTymaczasowy = init_node(i,j);
                    dodajDoListyNodow(l,nodeTymaczasowy);
                }
            }
            else{ //wszystko inne
                if(czyToNode(t,i,j,15) == 1){
                    //printf("Dodaje noda na (%d,%d)\n",i,j);
                    nodeTymaczasowy = init_node(i,j);
                    dodajDoListyNodow(l,nodeTymaczasowy);
                }
            }
        }
    }
    //czytam ostatni rzad
    for (int j = 1; j < (t->c)-1; j++){
        //printf("Sprawdzam (%d,%d)\n",t->c,j);
        if(czyToNode(t,(t->r)-1,j,11) == 1){
            nodeTymaczasowy = init_node(t->r-1,j);
            dodajDoListyNodow(l,nodeTymaczasowy);
        }
    }
    free(nodeTymaczasowy);
    return l;
}

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
    }
    return NULL;
}

void wypiszListeNodow(listaNodow* l){
    for (int i = 0; i < l->n; i++){
        printf ("Node %d. %ld o wspolrzednych (%d,%d)\n",i+1,l->nody[i],l->nody[i]->x,l->nody[i]->y);
    }
}