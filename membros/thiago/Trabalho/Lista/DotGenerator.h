#ifndef DOTGENERATOR_H
#define DOTGENERATOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "No.h"

using namespace std;

class DotGenerator 
{
    public:
        DotGenerator(); 
        ~DotGenerator();

        void gerar(No* grafo, int direcional, int ponderado);
    private:
        ofstream outFile;
        stringstream ss;
        bool checarArestaParaRepetidas(int id1, int id2);
};

#endif // DOTGENERATOR_H
