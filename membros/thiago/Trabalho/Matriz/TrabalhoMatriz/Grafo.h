#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Log.h"
#include "Matriz.h"
#include "Indice.h"

using namespace std;

class Grafo
{
    public:
        Grafo(bool _direcional, int ponderado);
        ~Grafo();

        void parse(string nomeArquivo);
        void imprimir();

    private:
        Matriz *matriz;
        Indice *indice;
        int ordem;
        int n;
        int m;
        int grau;
        bool direcional;
        bool ponderadoNos;
        bool ponderadoAresta;
        int ponderado;

        void criaMatriz(int n);
        void CriaIndices(int n);
        void addNoEArestaPonderada(int id, int idAresta, float peso);
};

#endif // GRAFO_H
