/**
    Universidade Federal de Juiz de Fora
    Steiner.cpp
    Propósito: Resolve o problema de Steiner.

    @author Thiago Almeida
    @version 1.0 09/05/19
*/

#include "Steiner.h"

Steiner::Steiner(Grafo *grafo){
    this->grafo = grafo;
    this->caminhoMinimo = new CaminhoMinimoDijkstra(grafo);
};
Steiner::~Steiner(){
    //destrutor
};

float Steiner::obtemMenorDistancia(int origem, int destino)
{
    caminhoMinimo->calcular(origem, destino);
    return caminhoMinimo->getDistanciaMinima();
}
