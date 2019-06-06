//
// Created by victor on 01/04/19.
//

#include "Aresta.h"

Aresta::Aresta() {} //thiago

Aresta::Aresta(int no) {
    this->noAdj = no;
    this->peso = -1;
    this->prox = nullptr;
}

Aresta::Aresta(int no, float peso) {
    this->noAdj = no;
    this->peso = peso;
    this->prox = nullptr;
}

//thiago
Aresta::Aresta(int no, int noOrigem, float peso) {
    this->noAdj = no;
    this->peso = peso;
    this->noOrigem = noOrigem;
    this->prox = nullptr;
}

Aresta::~Aresta() {
    // Deletando todas as arestas
    Aresta* p = prox;
    while(p != NULL){
        Aresta *a = p->getProx();
        //rever o porque esse delete dá erro com o stack do c++
        //delete p;
        p = a;
    }
}

// *** Getters ***

float Aresta::getPeso() { return this->peso; }

Aresta* Aresta::getProx() { return this->prox; }

int Aresta::getNoAdj() { return this->noAdj; }

int Aresta::getNoOrigem() { return this->noOrigem; } //thiago

// *** Setters ***

void Aresta::setProx(Aresta *aresta) {
    this->prox = aresta;
}
