
#include <stdio.h>
#include <stdlib.h>
#include "wczyt.h"

short* wyznaczRozmiar (FILE* plik){
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
    printf("Rozmiar tego labiryntu to: %d rzedow = rozmiar[0] x %d kolumn = rozmiar[1]\n",rozmiar[0],rozmiar[1]);
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

void wczytajPlik (FILE* plik, tab* t){
    char c;
    int i = 0;
    int j = 0;
    while ((c = fgetc(plik)) != EOF){
	    printf("Wczytano znak '%c' o kodzie '%d'\n",c,c);
        if (czyDobryZnak(c) != 0){
            printf("'%c' to zly znak\n",c);
            //return;
        }
        if (c == '\n'){
            i++;
            j = 0;
            continue;
        }
        t->buf[i][j] = c;
        j++;
    }
}

void wypisz(tab* t){
    for(int i = 0; i < t->r; i++){
        for(int j = 0; j < t->c; j++){
            printf("%c",t->buf[i][j]);
        }
        printf("\n");
    }
}

