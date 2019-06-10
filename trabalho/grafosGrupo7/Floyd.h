//
// Created by victor on 07/05/19.
//

#ifndef GRAFOLISTA_FLOYD_H
#define GRAFOLISTA_FLOYD_H


// #include "Grafo.h"
#include "No.h"
#include <limits>
#include <iomanip>

class Floyd {

public:
    // Floyd(Grafo *g);
    Floyd(No* listaNos, float** matrizAdj);

    Aresta* getCaminhoAresta(int origem, int destino);
    int* getCaminhoInt(int origem, int destino);
    float getDistancia(int origem, int destino);

    void imprime();

private:
    // Grafo* g;
    No* listaNos;
    float** matrizAdj;
    float** dist;
    int** path;
    int ordem;

    void floydAlgorithm();
    int noIdToPos(int id);
    int noPosToId(int pos);

};


#endif //GRAFOLISTA_FLOYD_H
