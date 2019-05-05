//
// Created by victor on 23/04/19.
//

#ifndef GRAFOLISTA_ORDENACAOTOPOLOGICA_H
#define GRAFOLISTA_ORDENACAOTOPOLOGICA_H

#include <iostream>
#include "No.h"

using namespace std;

class OrdenacaoTopologica {

public:

    OrdenacaoTopologica(int ordem, No* listaNos);

    int* ordenacao();

private:
    int ordem;
    No* listaNos;
    No** semEntrada;
    int lenSemEntrada = 0;
    int* ordenados;
    int* visitados;

    void visita(No* n, int ordem);
    int find(int* vetor, int valor, int tam);
    No* findNo(int id);
    int* inverteVetor(int* vetor, int tam);

};


#endif //GRAFOLISTA_ORDENACAOTOPOLOGICA_H
