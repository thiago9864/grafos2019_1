//
// Created by victor on 07/05/19.
//

#ifndef GRAFOLISTA_CAMINHOMAISCURTO_H
#define GRAFOLISTA_CAMINHOMAISCURTO_H


#include "Grafo.h"
#include <limits>

class Floyd {

public:
    Floyd(Grafo *g);

    Aresta* getCaminho(int origem, int destino);
    int getDistancia(int origem, int destino);

    void imprime();

private:
    Grafo* g;
    int** matrizAdj;
    int** dist;
    int** path;
    int ordem;

    void floydAlgorithm();

};


#endif //GRAFOLISTA_CAMINHOMAISCURTO_H
