/**
    Universidade Federal de Juiz de Fora
    Steiner.h
    Propósito: Resolve o problema de Steiner.

    @author Thiago Almeida
    @version 1.0 09/05/19
*/

#ifndef STEINER_H
#define STEINER_H
#include <iostream>
#include "Grafo.h"
#include "CaminhoMinimoDijkstra.h"

class Steiner
{
    public:
        Steiner(Grafo* grafo);
        ~Steiner();
        float obtemMenorDistancia(int origem, int destino);

    private:
        Grafo* grafo;
        CaminhoMinimoDijkstra* caminhoMinimo;

};

#endif // STEINER_H
