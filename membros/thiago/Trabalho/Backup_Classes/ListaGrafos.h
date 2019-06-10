/**
    Universidade Federal de Juiz de Fora
    ListaGrafos.h
    Propósito: Encapsular uma lista de grafos.

    @author Thiago Almeida
    @version 1.0 27/04/19 
*/

#ifndef LISTAGRAFOS_H
#define LISTAGRAFOS_H
#include <iostream>
#include "Grafo.h"

class Grafo; /// https://stackoverflow.com/questions/17333934/class-name-does-not-name-a-type-in-c

class ListaGrafos
{
    public:
        ListaGrafos(int tam);
        ~ListaGrafos();
        void addGrafo(Grafo grafo);
        Grafo* getGrafos();
        int getTamanho();
    private:
        Grafo* lista;
        int tamanho;
        int max;
};

#endif //LISTAGRAFOS_H
