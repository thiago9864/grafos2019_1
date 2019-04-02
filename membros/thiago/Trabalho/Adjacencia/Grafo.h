#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Log.h"
#include "No.h"

using namespace std;

class Grafo 
{
    public:
        Grafo(bool _direcional, int ponderado); 
        ~Grafo();

        void parse(string nomeArquivo);
        void imprimir();

    private:
        No *listaNos;
        No *ultimoNo;
        int ordem;
        int n;
        int m;
        int grau;
        bool direcional;
        bool ponderadoNos;
        bool ponderadoAresta;
        int ponderado;

        void addNoEArestaPonderada(int id, int idAresta, float peso);
        No* procuraNo(int id);
};

#endif // GRAFO_H