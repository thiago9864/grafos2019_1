/**
    Universidade Federal de Juiz de Fora
    Indice.cpp
    Propósito: Armazena o indice da busca por profundidade.

    @author Thiago Almeida
    @version 1.0 22/04/19 
*/

#ifndef INDICE_H
#define INDICE_H
#include <iostream>

using namespace std;

class Indice
{
    public:
        Indice(int n);
        ~Indice();
        int insereOuAtualizaVertice(int id, int status, int marcador);
        int procuraPosicaoNoIndice(int id);
        int getStatus(int id);
        int getMarcador(int id);
        int getTamIndice();
        void imprimeIndice();
    private:
        int **indices;
        int _n;
        int tamIndice;
};

#endif // INDICE_H
