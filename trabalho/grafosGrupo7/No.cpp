//
// Created by victor on 01/04/19.
//

#include <iostream>
#include "No.h"

No::No(){};

No::No(int id, float peso) {
    this->id = id;
    this->peso = peso;
    this->grauSaida = 0;
    this->grauEntrada = 0;
    this->prox = nullptr;
    this->adj = nullptr;
}

No::No(int id) {
    this->id = id;
    this->peso = -1;
    this->grauSaida = 0;
    this->grauEntrada = 0;
    this->prox = nullptr;
    this->adj = nullptr;
}

No::~No() {

    // Deletando todos os nós
    No* ant = this;
    No *n;

    for (No *n = ant->getProx(); n != nullptr; n = n->getProx()) {
        delete ant->adj;
        delete ant;
    }

}

// *** Getters ***

int No::getId() { return this->id; }

void No::setId(int id){
    this->id = id;
}

No* No::getProx() { return this->prox; }

float No::getPeso() { return this->peso; }

int No::getGrauEntrada() { return this->grauEntrada; }
int No::getGrauSaida() { return this->grauSaida; }

void No::setGrauEntrada(int grauEntrada) 
{ 
    if(grauEntrada >= 0){
        this->grauEntrada = grauEntrada; 
    }
}
void No::setGrauSaida(int grauSaida) 
{ 
    if(grauSaida >= 0){
        this->grauSaida = grauSaida; 
    }
}

Aresta *No::getAresta() { return this->adj; }

Aresta *No::getAresta(int i) {
    Aresta *a = this->adj;
    int c = 0;

    for (; a != nullptr || c < i; a = a->getProx(), c++);

    if (c == i)
        return a;
    else
        return nullptr;
}

// *** Setters ***

void No::setProx(No *n) { this->prox = n; }

bool No::setAresta(Aresta *aresta) {
    Aresta *a = this->adj;

    // Inicialzando arestas
    if (a == nullptr) {
        this->adj = aresta;
        this->aumentaGrauSaida();

        return true;
    }

    // Encontrando a ultima aresta inserida e certificando que não existe essa aresta
    for (; a->getProx() != nullptr && a->getNoAdj() != aresta->getNoAdj(); a = a->getProx());

    // Inserindo aresta ou imprimindo erro se já existe aresta
    if (a->getNoAdj() != aresta->getNoAdj()) {
        a->setProx(aresta);
    } else {
        std::cout << "Aresta ja inserida: " << this->getId() << " ---> " << aresta->getNoAdj() << std::endl;
        return false;
    }

    this->aumentaGrauSaida();

    return true;

}

void No::aumentaGrauEntrada() { this->grauEntrada++; }

void No::aumentaGrauSaida() { this->grauSaida++; }

// *** REMOÇÂO ***

bool No::removeAresta(int idNo) {

    Aresta *aresta = this->getAresta();
    Aresta *ant = this->getAresta();
    bool encontrou = false;

    // Percorrendo lista de arestas a fim de encontrar aresta desejada
    for (; aresta != nullptr; aresta = aresta->getProx()) {
        if (aresta->getNoAdj() == idNo) {
            encontrou = true;
            break;
        }
        ant = aresta;
    }

    // Se o nó foi encontrado é retirado o nó e colocado os seguintes para o nó anterior
    if (encontrou) {
        Aresta *prox = aresta->getProx();

        if (ant == aresta)
            this->adj = prox;     // Se a aresta for a primeira reiniciamos a sequencia a partir do próximo
        else
            ant->setProx(prox);   // Senão colocamos o seguinte no anterior

        aresta->setProx(nullptr); // Evita apagar o nó subsequente
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