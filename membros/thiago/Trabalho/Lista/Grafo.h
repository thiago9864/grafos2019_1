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
        void sequenciaGrau();

    private:
        No *listaNos;
        No *ultimoNo;
        int ordem;
        int numArestas;
        int grau;
        bool direcional;
        int ponderado;

        void addNoEArestaPonderada(int id, int idAresta, float peso);
        void addNoEArestaPonderadaDigrafo(int id, int idAresta, float peso);
        
        No* procuraNo(int id);
        No* criaNo(int id, No*& listaNos, No*& ultimoNo); //esse & junto com o * do ponteiro é pra variavel ficar por referencia
        Aresta* criaAresta(int id, float peso, No*& vertice); //esse & junto com o * do ponteiro é pra variavel ficar por referencia
};

#endif // GRAFO_H