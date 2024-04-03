#include <stdio.h>
#include <stdlib.h>
#include "preprocesor.h"
#include "nody.h"
#include "wczytajPlikTxt.h"
#include "graf.h"

void polaczPoziomo(tab* t, listaNodow* l){
    node_t* n1 = NULL;
    node_t* n2 = NULL;
    for(int i = 0; i < t->r; i++){
        for (int j = 0; j < t->c; j++){
            if(jedenZeZnakow(t,i,j) == 1){ //jesli tu moze byc przejscie/nod sprawczamy
                if(n1 == NULL){ //jak nie ma nic na n1 to sprbuj zlapac za linke od tad jesli to node
                    n1 = istniejeTakiNode(l,i,j);
                }
                else{ //jak mam sznurek z n1 to sprobuj go przyczepic tutaj
                    n2 = istniejeTakiNode(l,i,j);
                    if(n2 != NULL){
                        link_nodes(n1,n2);
                        n1 = n2;
                        n2 = NULL;
                    }
                }
            }
            else{ //jesli trafilismy na sciane to puszczam sznurek
                n1 = NULL;
            }
        }
    }
}

void polaczPionowo(tab* t, listaNodow* l){
    node_t* n1 = NULL;
    node_t* n2 = NULL;
    for(int j = 0; j < t->c; j++){
        for (int i = 0; i < t->r; i++){
            if(jedenZeZnakow(t,i,j) == 1){ //jesli tu moze byc przejscie/nod sprawczamy
                if(n1 == NULL){ //jak nie ma nic na n1 to sprbuj zlapac za linke od tad jesli to node
                    n1 = istniejeTakiNode(l,i,j);
                }
                else{ //jak mam sznurek z n1 to sprobuj go przyczepic tutaj
                    n2 = istniejeTakiNode(l,i,j);
                    if(n2 != NULL){
                        link_nodes(n1,n2);
                        n1 = n2;
                        n2 = NULL;
                    }
                }
            }
            else{ //jesli trafilismy na sciane to puszczam sznurek
                n1 = NULL;
            }
        }
    }
}

void txtNaGraf(FILE* plik){
    fseek(plik,0, SEEK_SET);
    tab* buf = stworzTablice(wyznaczRozmiarLabiryntu(plik));
    fseek(plik,0, SEEK_SET);
    wczytajPlikTxtDoTablicy(plik,buf);
    wypiszTablice(buf);
    listaNodow* l;
    stworzListeNodow(l);
    l = stworzNody(buf,l);
    wypiszListeNodow(l);
    polaczPionowo(buf,l);
    polaczPoziomo(buf,l);
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