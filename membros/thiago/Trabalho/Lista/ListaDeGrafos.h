#ifndef LISTADEGRAFOS_H
#define LISTADEGRAFOS_H
#include <iostream>
#include "Aresta.h"
#include "No.h"

class ListaDeGrafos
{
    public:
        ListaDeGrafos();
        ~ListaDeGrafos();
        void addGrafo(No* grafo);
    private:
        No* lista;
        No* ultimoLista;
};

#endif //LISTADEGRAFOS_H
