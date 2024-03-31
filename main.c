#include <stdio.h>
#include <stdlib.h>
#include "wczyt.h"

int main(){
    FILE* plik = fopen("test.txt","r");
    if (plik == NULL) printf("Nie udalo otworzyc sie pliku\n");
    tab* buf = stworzTablice(wyznaczRozmiar(plik));
    fseek(plik,0, SEEK_SET);
    wczytajPlik(plik,buf);
    wypisz(buf);
    zwolnijTablice(buf);
    fclose(plik);
    return 0;
}