/**
    Universidade Federal de Juiz de Fora
    CaminhoMinimoDijkstra.h
    Propósito: Calcula o caminho mínimo usando o algoritmo de Dijkstra.

    @author Thiago Almeida
    @version 1.0 09/05/19
*/

#ifndef CAMINHOMINIMODIJKSTRA_H
#define CAMINHOMINIMODIJKSTRA_H
#include <iostream>
#include "Grafo.h"
#include "No.h"


class CaminhoMinimoDijkstra
{
    public:
        CaminhoMinimoDijkstra(Grafo* grafo);
        ~CaminhoMinimoDijkstra();

        float calcular(int origem, int destino);

    private:
        Grafo* grafo;
        int* visitados;
        int numVisitados;
        float* distancias;
        int* indice;

        float getDistancia(int id);
        void updateDistancia(int id, float distancia);
        bool isVisitado(int id);

};

#endif // CAMINHOMINIMODIJKSTRA_H
