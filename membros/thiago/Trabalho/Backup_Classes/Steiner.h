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
#include <ctime>
#include "Grafo.h"
#include "CaminhoMinimoDijkstra.h"

using namespace std;

class Steiner
{
    public:
        Steiner(Grafo* grafo);
        ~Steiner();
        float obtemMenorDistancia(int origem, int destino);
        float calcular();
    private:
        Grafo* grafo;
        CaminhoMinimoDijkstra* caminhoMinimo;
        float maxFloat = 99999999999999999999.9;
        bool estaNoTerminal(int id);

};

#endif // STEINER_H
