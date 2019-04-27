/**
    Universidade Federal de Juiz de Fora
    ListaArestas.h
    Propósito: Encapsular uma lista de arestas.

    @author Thiago Almeida
    @version 1.0 27/04/19 
*/

#ifndef LISTAARESTAS_H
#define LISTAARESTAS_H
#include <iostream>
#include "Aresta.h"

class ListaArestas
{
    public:
        ListaArestas();
        ~ListaArestas();
        void addAresta(Aresta* aresta);
        void removeAresta(Aresta* aresta);
        Aresta* getAresta(int idOrigem, int idDestino);
        Aresta* getArrayArestas();
        int getTamanho();
    private:
        Aresta* lista;
        Aresta* ultimoLista;
        int tamanho;
};

#endif //LISTAARESTAS_H
