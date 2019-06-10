//
// Created by victor on 11/05/19.
//

#ifndef GRAFOLISTA_CAMINHOMINIMODIJKSTRA_H
#define GRAFOLISTA_CAMINHOMINIMODIJKSTRA_H


#include <iostream>
#include <stack>
#include "Grafo.h"
#include "No.h"


class CaminhoMinimoDijkstra {
public:
    CaminhoMinimoDijkstra(Grafo* grafo);
    ~CaminhoMinimoDijkstra();

    void calcular(int origem, int destino);
    int* getCaminhoMinimo();
    float getDistanciaMinima();
    int getTamCaminho();

private:
    Grafo* grafo;
    float** matriz;
    int* caminhoMinimo;
    int tamCaminho;
    float distanciaMinima;
    int* visitados;
    int numVisitados;
    float maxFloat = 99999999999999999999.9;

    void setVisitado(int id);
    bool isVisitado(int id);
    int getIndiceMatriz(int id);
    int getAnterior(int id);
    float getDistancia(int id);
    void updateDistanciaVertice(int id, int idAnt, float distancia);
};


#endif //GRAFOLISTA_CAMINHOMINIMODIJKSTRA_H
