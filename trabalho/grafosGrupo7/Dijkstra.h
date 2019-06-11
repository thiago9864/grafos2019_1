/**
    Universidade Federal de Juiz de Fora
    Dijkstra.h
    Propósito: Calcula o caminho mínimo usando o algoritmo de Dijkstra.

    @author Thiago Almeida
    @version 1.2 09/05/19
*/

#ifndef GRAFOLISTA_DIJKSTRA_H
#define GRAFOLISTA_DIJKSTRA_H
#include <iostream>
#include <stack>
#include "No.h"


class Dijkstra
{
    public:
        Dijkstra(No* listaNos);
        ~Dijkstra();

        void calcular(int origem, int destino);
        int* getCaminhoMinimo();
        float getDistanciaMinima();

    private:
        No* listaNos;
        float** matriz;
        int* caminhoMinimo;
        float distanciaMinima;
        int* visitados;
        int numVisitados;
        float maxFloat = 99999999999999999999.9;
        int ordem = 0;

        void setVisitado(int id);
        bool isVisitado(int id);
        int getIndiceMatriz(int id);
        int getAnterior(int id);
        float getDistancia(int id);
        void updateDistanciaVertice(int id, int idAnt, float distancia);
};

#endif // GRAFOLISTA_DIJKSTRA_H
