/**
    Universidade Federal de Juiz de Fora
    Aresta.h
    Propósito: Representar arestas de um grafo.

    @author Thiago Almeida
    @version 1.0 30/03/19 
*/

#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>

class Aresta 
{
    public:
        Aresta(); 
        ~Aresta();

        int getNoOrigem();
        void setNoOrigem(int _noOrigem);

        int getNoAdj();
        void setNoAdj(int _noAdjacente);

        float getPeso();
        void setPeso(float _peso);

        Aresta* getProx();
        void setProx(Aresta* _proximo);

    private:
        int noOrigem;
        int noAdjacente;
        float peso;
        Aresta *proximo;
};

#endif // ARESTA_H