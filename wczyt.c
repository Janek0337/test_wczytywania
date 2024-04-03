
#include <stdio.h>
#include <stdlib.h>
#include "wczyt.h"
#include "node_list.h"

short* wyznaczRozmiarLabiryntu (FILE* plik){
    short* rozmiar = malloc (2*sizeof(short int));
    short a = 0;
    short b = 0;
    char c;
    while ((c = fgetc(plik)) != EOF){
        if (c == '\n'){
            a++;
            continue;
        }
        else {
            b++;
        }
    }
    rozmiar[0] = a; //rzedy
    rozmiar[1] = b/a; //kolumny
    printf("Rozmiar tego labiryntu to: %d rzedow x %d kolumn\n",rozmiar[0],rozmiar[1]);
    return rozmiar;
}

tab* stworzTablice(short* rozmiar) {
		tab* t = malloc(sizeof(tab));
		if (t != NULL) {
			t->r = rozmiar[0];
			t->c = rozmiar[1];
			t->buf = malloc(sizeof(char*) * rozmiar[0]);
			for (int i = 0; i < rozmiar[0] ;i++) {
					t->buf[i] = malloc(sizeof(char) * rozmiar[1]);
			}
		}

		return t;
}

void zwolnijTablice(tab* t) {
	for (int i=0; i < t->r; i++)
		free(t->buf[i]);
	free(t->buf);
	free(t);
}

int czyDobryZnak(char c){
    if (c == 'X' || c == 'P' || c == 'K' || c == ' ' || c == '\n') return 0;
    return 1;
}

int wczytajPlikTxtDoTablicy (FILE* plik, tab* t){ //zwraca 0 gdy udalo sie wczytac plik poprawnie, 1 gdy znaleziono nieodpowiednie znaki
    char c;
    int i = 0;
    int j = 0;
    while ((c = fgetc(plik) ) != EOF){
        if (czyDobryZnak(c) != 0){
            fprintf(stderr,"'%c' to zly znak\n",c);
            return 1;
        }
        if (c == '\n'){
            i++;
            j = 0;
            continue;
        }
        t->buf[i][j] = c;
        j++;
    }
    return 0;
}

void wypiszTablice(tab* t){
    for(int i = 0; i < t->r; i++){
        for(int j = 0; j < t->c; j++){
            printf("%c",t->buf[i][j]);
        }
        printf("\n");
    }
}

int jedenZeZnakow(tab*t, short i, short j){
    if(t->buf[i][j] == ' ' || t->buf[i][j] == 'K' || t->buf[i][j] == 'P') return 1;
    return 0;
}

int zprawej(tab* t,short i, short j){
    if (jedenZeZnakow(t,i,j+1) == 1) return 1;
    return 0;
}

int zlewej(tab* t,short i, short j){
    if (jedenZeZnakow(t,i,j-1) == 1) return 1;
    return 0;
}

int zgory(tab* t,short i, short j){
    if (jedenZeZnakow(t,i-1,j) == 1) return 1;
    return 0;
}

int zdolu(tab* t,short i, short j){
    if (jedenZeZnakow(t,i+1,j) == 1) return 1;
    return 0;
}


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

listaNodow* stworzNody(tab* t, listaNodow* lista){
    node_t* nodeTymaczasowy = malloc(sizeof(node_t*));
    nodeTymaczasowy = NULL;
    stworzListeNodow(lista);
    //czytam pierwszy rzad
    for(int j = 1; j < (t->c)-1; j++){
        if (czyToNode(t,0,j,14) == 1){
            printf("Dodaje noda na (0,%d)\n",j);
            //nodeTymaczasowy = init_node(0,j);
            //dodajDoListyNodow(l,nodeTymaczasowy);
        }
    }
    //czytam wszystko bez pierwszego i bez ostatniego rzedu
    for(int i = 1; i < (t->r)-1; i++){
        for (int j = 0; j < t->c; j++){
            if(j == 0){ //lewa banda
                if(czyToNode(t,i,j,7) == 1){
                    printf("Dodaje noda na (%d,%d)\n",i,j);
                    //nodeTymaczasowy = init_node(i,j);
                    //dodajDoListyNodow(l,nodeTymaczasowy);
                }
            }
            else if(j == (t->c)-1){ //prawa banda
                if(czyToNode(t,i,j,13) == 1){
                    printf("Dodaje noda na (%d,%d)\n",i,j);
                    //nodeTymaczasowy = init_node(i,j);
                    //dodajDoListyNodow(l,nodeTymaczasowy);
                }
            }
            else{ //wszystko inne
                if(czyToNode(t,i,j,15) == 1){
                    printf("Dodaje noda na (%d,%d)\n",i,j);
                    //nodeTymaczasowy = init_node(i,j);
                    //dodajDoListyNodow(l,nodeTymaczasowy);
                }
            }
        }
    }
    //czytam ostatni rzad
    for (int j = 1; j < (t->c)-1; j++){
        if(czyToNode(t,(t->r)-1,j,11) == 1){
            printf("Dodaje noda na (%d,%d)\n",t->r-1,j);
            //nodeTymaczasowy = init_node(t->r-1,j);
            //dodajDoListyNodow(l,nodeTymaczasowy);
        }
    }
    free(nodeTymaczasowy);
    return lista;
}

void polaczHoryzontalnie(tab* t, listaNodow* l){
    node_t* n1 = malloc(sizeof(node_t*));
    node_t* n2 = malloc(sizeof(node_t*));
    n1 = NULL;
    n2 = NULL;
    for(int i = 0; i < t->r; i++){
        for (int j = 0; j < t->c; j++){
            if(jedenZeZnakow(t,i,j) == 1){ //jesli tu moze byc przejscie/nod sprawczamy
                if(n1 == NULL){ //jak nie ma nic na n1 to sprbuj zlapac za linke od tad jesli to node
                    n1 = istniejeTakiNode(l,i,j);
                }
                else{ //jak mam sznurek z n1 to sprobuj go przyczepic tutaj
                    n2 = istniejeTakiNode(l,i,j);
                    if(n2 != NULL){
                        link(n1,n2);
                        n1 = n2;
                        n2 = NULL;
                    }
                }
            }
            else{ //jesli trafilismy na sciane to puszczam sznurek
                n1 = NULL;
            }
        }
        n1 = NULL;
        n2 = NULL;
    }
    free(n1);
    free(n2);
}

void polaczWertykalnie(tab* t, listaNodow* l){
    node_t* n1 = malloc(sizeof(node_t*));
    node_t* n2 = malloc(sizeof(node_t*));
    n1 = NULL;
    n2 = NULL;
    for(int j = 0; j < t->c; j++){
        for (int i = 0; i < t->r; i++){
            if(jedenZeZnakow(t,i,j) == 1){ //jesli tu moze byc przejscie/nod sprawczamy
                if(n1 == NULL){ //jak nie ma nic na n1 to sprbuj zlapac za linke od tad jesli to node
                    n1 = istniejeTakiNode(l,i,j);
                }
                else{ //jak mam sznurek z n1 to sprobuj go przyczepic tutaj
                    n2 = istniejeTakiNode(l,i,j);
                    if(n2 != NULL){
                        link(n1,n2);
                        n1 = n2;
                        n2 = NULL;
                    }
                }
            }
            else{ //jesli trafilismy na sciane to puszczam sznurek
                n1 = NULL;
            }
        }
        n1 = NULL;
        n2 = NULL;
    }
    free(n1);
    free(n2);
}