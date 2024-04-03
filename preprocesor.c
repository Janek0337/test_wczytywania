#include <stdio.h>
#include <stdlib.h>
#include "preprocesor.h"
#include "node_list.h"
#include "wczyt.h"
#include "graf.h"

void txtNaGraf(FILE* plik){
    tab* buf = stworzTablice(wyznaczRozmiarLabiryntu(plik));
    fseek(plik,0, SEEK_SET);
    wczytajPlikTxtDoTablicy(plik,buf);
    wypiszTablice(buf);
    listaNodow* l;
    stworzListeNodow(l);
    l = stworzNody(buf,l);
    //polaczWertykalnie(buf,l);
    //polaczHoryzontalnie(buf,l);
    zwolnijListeNodow(l);
    zwolnijTablice(buf);
}

int main(){
    FILE* plik;
    plik = fopen("test.txt","r");
    if (plik == NULL) {
        printf("Nie udalo otworzyc sie pliku\n");
        return 1;
    }
    txtNaGraf(plik);
    fclose(plik);
    return 0;
}