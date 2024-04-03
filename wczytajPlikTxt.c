#include <stdio.h>
#include <stdlib.h>
#include "wczytajPlikTxt.h"
#include "nody.h"
#include "graf.h"

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
    if (c == 'X' || c == 'P' || c == 'K' || c == ' ' || c == '\n') return 1;
    return 0;
}

int wczytajPlikTxtDoTablicy (FILE* plik, tab* t){ //zwraca 0 gdy udalo sie wczytac plik poprawnie, 1 gdy znaleziono nieodpowiednie znaki
    char c;
    int i = 0;
    int j = 0;
    while ((c = fgetc(plik) ) != EOF){
        if (czyDobryZnak(c) != 1){
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