#include <stdio.h>
#include <stdlib.h>
#include "wczyt.h"

int main(){
    FILE* plik;
    plik = fopen("test.txt","r");
    tab* buf = stworzTablice(wyznaczRozmiar(plik));
    wczytajPlik(plik,buf);
    wypisz(buf);
    zwolnijTablice(buf);
    fclose(plik);
    return 0;
}
