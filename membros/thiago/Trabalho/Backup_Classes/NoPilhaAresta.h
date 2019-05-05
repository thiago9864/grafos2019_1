/**
    Universidade Federal de Juiz de Fora
    NoPilhaAresta.h
    Propósito: Classe que representa um nó da pilha.

    @author Thiago Almeida
    @version 1.0 27/04/19 
*/

#ifndef NOPILHAARESTA_H_INCLUDED
#define NOPILHAARESTA_H_INCLUDED

#include "Aresta.h"

class NoPilhaAresta
{
    private:
        Aresta *info;
        NoPilhaAresta *prox;

    public:
        NoPilhaAresta() {}
        ~NoPilhaAresta() {}

        Aresta* getInfo() { return info; }
        void setInfo(Aresta *c) { info = c; }
        void setProx(NoPilhaAresta *p) { prox = p; }
        NoPilhaAresta* getProx() { return prox; }
};

#endif // NOPILHAARESTA_H_INCLUDED
