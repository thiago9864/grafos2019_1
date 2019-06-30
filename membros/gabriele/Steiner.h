/**
    Universidade Federal de Juiz de Fora
    Steiner.h

    @author Victor Aquiles
    @version 1.0 01/04/19
*/


#ifndef GRAFOLISTA_STEINER_H
#define GRAFOLISTA_STEINER_H

#include <fstream>
#include <sstream>
#include <time.h>
#include "Grafo.h"

using namespace std;

class Steiner {

public:

    Steiner(int* terminais, int tam_terminais);

    int* steiner(float alfa, int maxiter);

    void poda(Grafo* grafo_novo);
    void auxPoda(Grafo* grafo_novo,No* aux);

    void colocaAresta(No* inserido, int tam_solucao,No** solucao,Grafo* steinerSol);
private:

    Grafo* g;
    int *terminais;
    int tam_terminais;

    void ordenaAdj(No** adj, No** sol, int tam_adj, int tam_sol);
    int binarySearch(float a[], int item, int low, int high);
    int atualizaLista(No** adj, int tam, int pos);

};



#endif //GRAFOLISTA_STEINER_H
