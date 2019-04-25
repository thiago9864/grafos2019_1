//
// Created by victor on 23/04/19.
//

#ifndef GRAFOLISTA_ORDENACAOTOPOLOGICA_H
#define GRAFOLISTA_ORDENACAOTOPOLOGICA_H

#include <iostream>
#include "No.h"
#include "Grafo.h"

using namespace std;

class OrdenacaoTopologica {

public:

    int* ordenacao(Grafo* g);
    void imprime();

private:
    Grafo* g;
    No** semEntrada;
    int lenSemEntrada = 0;
    int* ordenados;
    int* visitados;

    void visita(No* n, int ordem);
    int find(int* vetor, int valor, int tam);
    int* inverteVetor(int* vetor, int tam);

};


#endif //GRAFOLISTA_ORDENACAOTOPOLOGICA_H
