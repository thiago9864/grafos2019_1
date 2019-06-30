/**
    Universidade Federal de Juiz de Fora
    DotGenerator.h
    Propósito: Geração de arquivos no formato DOT a partir de um grafo armazenado em lista de adjacência.

    @author Thiago Almeida
    @version 1.0 22/04/19 
*/

#ifndef DOTGENERATOR_H
#define DOTGENERATOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "No.h"
#include "Grafo.h"

using namespace std;

class DotGenerator
{
    public:
        DotGenerator();
        ~DotGenerator();

        void gerar(Grafo* grafo, bool isDirecionado, bool isPonderadoVertice, bool isPonderadoAresta, string nomeArquivo);
    private:
        ofstream outFile;
        stringstream ss;
        bool checarArestaParaRepetidas(int id1, int id2);
};

#endif // DOTGENERATOR_H
