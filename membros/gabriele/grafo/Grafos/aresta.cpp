#include <iostream>
#include "aresta.h"
using namespace std;

Aresta::Aresta(int id){
    prox=NULL;
    no_adj=id;
    peso=-1.0;
}
Aresta::Aresta(int id,float peso){
    no_adj=id;
    this->peso=peso;
    prox=NULL;
}
Aresta::~Aresta(){
    while(prox!=NULL){
        Aresta* prox_aresta=prox->getProx();
        delete prox;
        prox=prox_aresta;
    }
}
//*** Get ***
int Aresta::getNoId(){
    return no_adj;
}
float Aresta::getPeso(){
    return peso;
}

Aresta* Aresta::getProx(){
    return prox;
}
//*** Set ***
void Aresta::setProx(Aresta *proximo){
    prox=proximo;
}


