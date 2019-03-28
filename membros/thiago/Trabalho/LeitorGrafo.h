#ifndef LEITORGRAFO_H
#define LEITORGRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Log.h"
#include "ObjGrafo.h"

using namespace std;

class LeitorGrafo {
    public:
        //construtor
        LeitorGrafo(string arquivoEntrada); 
        //destrutor
        ~LeitorGrafo();

        //metodos publicos
        void parse();
        void imprimir();
    private:
        //variaveis
        string nomeArquivoEntrada;
        int numVertices;
        int indice_add_grafo;
        ifstream inFile;
        Log log;
        ObjGrafo **grafo;

        //metodos
        void addNo(int rotulo, int peso);
};

#endif // LEITORGRAFO_H