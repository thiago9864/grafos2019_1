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
#include "Utils.h"
#include "Floyd.h"

using namespace std;

class Steiner {

public:

    Steiner(Grafo *grafo);

    float GulosoConstrutivo();
    float GulosoRandomizado(float alfa, int maxiter);
    float GulosoRandomizadoReativo(int maxiter, float *melhor_alfa);
    float ConstrutivoHeuristicaCaminhoMinimo();

    void gerarSemente();
    int getSemente();
    void setSemente(int semente);

private:

    Grafo* g;
    int *terminais;
    int tam_terminais;
    int semente;

    //guloso randomizado
    void ordenaAdj(No** adj, No** sol, int tam_adj, int tam_sol);
    int binarySearch(float a[], int item, int low, int high);
    void atualizaLista(No** solucao, int tam_sol, No** solucao_adj, int *tam_adj);
    void colocaAresta(No* inserido, int tam_solucao,No** solucao,Grafo* steinerSol);

    void poda(Grafo* grafo_novo);
    void auxPoda(Grafo* grafo_novo, No *aux, No *ant);

    //construtivo heuristica caminho minimo
    void remover(int *vetor, int *tam, int valor);
    void adicionar(int *vetor, int *tam, int valor);

};



#endif //GRAFOLISTA_STEINER_H
