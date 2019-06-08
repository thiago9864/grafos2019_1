//
// Created by victor on 07/05/19.
//

#ifndef GRAFOLISTA_CAMINHOMAISCURTO_H
#define GRAFOLISTA_CAMINHOMAISCURTO_H


#include "Grafo.h"
#include <limits>
#include <iomanip>

class Floyd {

public:
    Floyd(Grafo *g);

    Aresta* getCaminho(int origem, int destino);
    float getDistancia(int origem, int destino);

    void imprime();

private:
    Grafo* g;
    float** matrizAdj;
    float** dist;
    int** path;
    int ordem;

    void floydAlgorithm();

};


#endif //GRAFOLISTA_CAMINHOMAISCURTO_H
