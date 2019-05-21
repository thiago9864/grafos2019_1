/**
    Universidade Federal de Juiz de Fora
    ListaArestas.h
    Propósito: Encapsular um vetor de arestas e o tamanho dele.

    @author Thiago Almeida
    @version 1.0 04/05/19 
*/

#ifndef LISTAARESTAS_H
#define LISTAARESTAS_H
#include <iostream>
#include "Aresta.h"

class ListaArestas
{
    public:
        ListaArestas(){};
        ~ListaArestas(){delete this->vetor;};
        void setVetorArestas(Aresta* vetor){this->vetor = vetor;};
        Aresta* getVetorArestas(){return this->vetor;};
        void setTamanho(int tamanho){this->tamanho = tamanho;};
        int getTamanho(){return tamanho;};
    private:
        Aresta* vetor;
        int tamanho;
};

#endif //LISTAARESTAS_H
