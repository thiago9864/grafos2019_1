//
// Created by victor on 01/04/19.
//

#include "Aresta.h"

Aresta::Aresta(int no) {
    this->noAdj = no;
    this->peso = -1;
    this->prox = nullptr;
}

Aresta::Aresta(int no, int peso) {
    this->noAdj = no;
    this->peso = peso;
    this->prox = nullptr;
}

Aresta::~Aresta() {
    // Deletando todas as arestas
    Aresta* ant = this;
    for (Aresta *a = ant->getProx(); a != nullptr; a = a->getProx()) {
        delete ant;
    }
}

// *** Getters ***

float Aresta::getPeso() { return this->peso; }

Aresta* Aresta::getProx() { return this->prox; }

int Aresta::getNoAdj() { return this->noAdj; }

// *** Setters ***

void Aresta::setProx(Aresta *aresta) {
    this->prox = aresta;
}
