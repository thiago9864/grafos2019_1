#include <iostream>
#include "aresta.h"
using namespace std;

Aresta::Aresta(){}
Aresta::~Aresta(){}

int Aresta::getNoAd(){
    return no_adj;
}
void Aresta::setProx(Aresta *proximo){
    prox=proximo;
}
void Aresta::setNoAd(int id){
    no_adj=id;
}
int Aresta::getPeso(){
    return peso;
}
void Aresta::setPeso(int p){
    peso=p;
}
Aresta Aresta::*getProx(){
    return *prox;
}


