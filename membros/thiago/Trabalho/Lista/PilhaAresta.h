/**
    Universidade Federal de Juiz de Fora
    PilhaAresta.h
    Propósito: Classe que representa uma pilha de arestas.

    @author Thiago Almeida
    @version 1.0 27/04/19 
*/

#ifndef PILHA_H
#define PILHA_H
#include "Aresta.h"
#include "NoPilhaAresta.h"

class NoPilhaAresta;/// https://stackoverflow.com/questions/17333934/class-name-does-not-name-a-type-in-c

class PilhaAresta
{

    private:
        NoPilhaAresta *topo;
        int tamanho;
    public:
        PilhaAresta();
        ~PilhaAresta();

        Aresta *getTopo();
        void empilha(Aresta *aresta);
        Aresta *desempilha();
        bool isVazia();
        int getTamanho();
        void imprime();
};

#endif // PILHA_H
