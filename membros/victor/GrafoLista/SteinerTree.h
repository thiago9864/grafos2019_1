//
// Created by victor on 08/05/19.
//

#ifndef GRAFOLISTA_STEINERTREE_H
#define GRAFOLISTA_STEINERTREE_H


#include "Grafo.h"
#include "No.h"
#include "CaminhoMinimo.h"
#include "CaminhoMinimoDijkstra.h"

class SteinerTree {

public:
    SteinerTree(Grafo* g, int* terminais, int tam);

    Grafo* getSteinerTree();

private:
    Grafo* grafoOrigem;
    Grafo* arvore;
    int* terminais;
    int lenTerminais;
    bool* atendidos;
    CaminhoMinimo* caminhos;

    int menorCaminho(int origem);
    bool todosAtendidos();
    int primeiroNaoAtendido();
    void setCaminho(int origem, int destino);
    void geraSteinerTree();

};


#endif //GRAFOLISTA_STEINERTREE_H
