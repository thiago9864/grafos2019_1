#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Log.h"
#include "MatrizPesos.h"
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
        MatrizPesos *matriz;
        Indice *indice;
        Log *log;
        int ordem;
        int n;
        int m;
        int grau;
        bool direcional;
        bool ponderadoNos;
        bool ponderadoAresta;
        int ponderado;
        void addNoEAresta(int id, int idAresta, float peso);
};

#endif // GRAFO_H
