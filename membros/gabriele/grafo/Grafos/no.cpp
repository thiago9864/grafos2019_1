#include <iostream>
//#include "aresta.h"
#include "no.h"
using namespace std;

 No::No(int id){
     marca=false;
     this->id=id;
     peso=-1.0;
     grauEntrada=0;
     grauSaida=0;
     aresta_adj=NULL;
     prox=NULL;
 }
 No::No(int id, float peso){
     marca=false;
     this->id=id;
     this->peso=peso;
     grauEntrada=0;
     grauSaida=0;
     aresta_adj=NULL;
     prox=NULL;
 }
 No::~No(){
    while(prox!=NULL){
        No *prox_no=prox->getProx();
        delete prox;
        prox=prox_no;
    }
 }
 //*** GET ***
 int No::getGrauEntrada(){
          return grauEntrada;
 }
 int No::getGrauSaida(){
     return grauSaida;
 }
 Aresta* No:: getAresta(){
     return aresta_adj;
 }

 int No::getId(){
     return id;
 }
 float No::getPeso(){
     return peso;
 }
No* No:: getProx(){
    return prox;
}
Aresta* No::getAresta(int i){
    Aresta *a = this->aresta_adj;
    int c = 0;

    for (a, c; a != NULL || c < i; a = a->getProx(), c++);

    if (c == i)
        return a;
    else
        return NULL;
}
bool No::getMarca(){
    return marca;
}

//*** SET ***
void No::setPeso(float peso){
     this->peso=peso;
 }
 void No::setId(int num){
     id=num;
 }
bool No::setAresta(Aresta *aresta){
    Aresta *a = this->aresta_adj;

    // Inicialzando arestas
    if (a == NULL) {
        this->aresta_adj = aresta;
        this->aumentaGrauSaida();

        return true;
    }

    // Encontrando a ultima aresta inserida e certificando que não existe essa aresta
    for (a; a->getProx() != NULL && a->getNoId() != aresta->getNoId(); a = a->getProx());

    // Inserindo aresta ou imprimindo erro se já existe aresta
    if (a->getNoId() != aresta->getNoId()) {
        a->setProx(aresta);
    } else {
        std::cout << "Aresta ja inserida: " << this->getId() << " ---> " << aresta->getNoId() << std::endl;
        return false;
    }

    this->aumentaGrauSaida();

    return true;
 }

void No::setProx(No *n) { this->prox = n; }
void No::setMarca() {marca=true;}

void No::aumentaGrauEntrada() { this->grauEntrada++; }

void No::aumentaGrauSaida() { this->grauSaida++; }

//*** Remoção ***
bool No::removeAresta(int idNo) {

    Aresta *aresta = this->getAresta();
    Aresta *ant = this->getAresta();
    bool encontrou = false;

    // Percorrendo lista de arestas a fim de encontrar aresta desejada
    for (aresta; aresta != NULL; aresta = aresta->getProx()) {
        if (aresta->getNoId() == idNo) {
            encontrou = true;
            break;
        }
        ant = aresta;
    }

    // Se o nó foi encontrado é retirado o nó e colocado os seguintes para o nó anterior
    if (encontrou) {
        Aresta *prox = aresta->getProx();

        if (ant == aresta)
            this->aresta_adj = prox;     // Se a aresta for a primeira reiniciamos a sequencia a partir do próximo
        else
            ant->setProx(prox);   // Senão colocamos o seguinte no anterior

        aresta->setProx(NULL); // Evita apagar o nó subsequente
        delete aresta;

        this->diminuiGrauSaida();
    }

    return encontrou;

}
void No::diminuiGrauEntrada() {
    if (this->grauEntrada > 0)
        this->grauEntrada--;
}

void No::diminuiGrauSaida() {
    if (this->grauSaida > 0)
        this->grauSaida--;
}
