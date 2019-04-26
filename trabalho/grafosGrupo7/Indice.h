//
// Created by Thiago on 24/04/19.
//

#ifndef INDICE_H
#define INDICE_H
#include <iostream>

using namespace std;

class Indice
{
    public:
        Indice(int n);
        ~Indice();
        int insereOuAtualizaVertice(int id, int status);
        int procuraPosicaoNoIndice(int id);
        int getStatus(int id);
        int getTamIndice();
        void imprimeIndice();
    private:
        int **indices;
        int _n;
        int tamIndice;
};

#endif // INDICE_H
