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
#include "Grafo.h"

using namespace std;

class CaminhoMinimoDijkstra
{
    public:
        CaminhoMinimoDijkstra(Grafo *grafo);
        ~CaminhoMinimoDijkstra();

        void calcular(int origem, int destino);
        int* getCaminhoMinimo();
        float getDistanciaMinima();
        int getTamanhoCaminhoMinimo();

    private:
        Grafo* grafo;
        float** matriz;
        int numMatriz;
        int* caminhoMinimo;
        int tamCaminhoMinimo;
        float distanciaMinima;
        int* visitados;
        int numVisitados;
        float maxFloat = 99999999999999999999.9;

        void esqueceVisitado(int id);
        void setVisitado(int id);
        bool isVisitado(int id);
        int getIndiceMatriz(int id);
        int getAnterior(int id);
        float getDistancia(int id);
        void updateDistanciaVertice(int id, int idAnt, float distancia);
        void addVerticeNaMatriz(int id);
};

#endif // CAMINHOMINIMODIJKSTRA_H
