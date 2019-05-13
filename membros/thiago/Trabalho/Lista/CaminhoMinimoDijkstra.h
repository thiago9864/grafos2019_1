/**
    Universidade Federal de Juiz de Fora
    CaminhoMinimoDijkstra.h
    Propósito: Calcula o caminho mínimo usando o algoritmo de Dijkstra.

    @author Thiago Almeida
    @version 1.2 09/05/19
*/

#ifndef CAMINHOMINIMODIJKSTRA_H
#define CAMINHOMINIMODIJKSTRA_H
#include <iostream>
#include <stack>
#include "No.h"

using namespace std;

class CaminhoMinimoDijkstra
{
    public:
        CaminhoMinimoDijkstra(No* grafo, int ordem);
        ~CaminhoMinimoDijkstra();

        void calcular(int origem, int destino);
        int* getCaminhoMinimo();
        float getDistanciaMinima();

    private:
        No* grafo;
        int ordem;
        float** matriz;
        int* caminhoMinimo;
        float distanciaMinima;
        int* visitados;
        int numVisitados;
        float maxFloat = 99999999999999999999.9;

        No* getNo(int id);
        void setVisitado(int id);
        bool isVisitado(int id);
        int getIndiceMatriz(int id);
        int getAnterior(int id);
        float getDistancia(int id);
        void updateDistanciaVertice(int id, int idAnt, float distancia);
};

#endif // CAMINHOMINIMODIJKSTRA_H
