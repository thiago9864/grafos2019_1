#include "Aresta.h"

Aresta::Aresta(){}

Aresta::Aresta(int noOrigem, int noFim) {
    this->origem = noOrigem;
    this->noAdj = noFim;
    this->peso = -1.0;
    this->prox = nullptr;
}

Aresta::Aresta(int noOrigem, int noFim, float peso) {
    this->origem = noOrigem;
    this->noAdj = noFim;
    this->peso = peso;
    this->prox = nullptr;
}

/*Aresta::~Aresta() {
    // Deletando todas as arestas
    Aresta* ant = this;
    for (Aresta *a = ant->getProx(); a != nullptr; a = a->getProx()) {
        delete ant;
    }
}*/

// *** Getters ***

float Aresta::getPeso()
{
    return peso;
}

Aresta* Aresta::getProx()
{
    return prox;
}

int Aresta::getNoAdj()
{
    return noAdj;
}

int Aresta:: getOrigem()
{
    return origem;
}

// *** Setters ***

void Aresta::setProx(Aresta *aresta) {
    prox = aresta;
}
