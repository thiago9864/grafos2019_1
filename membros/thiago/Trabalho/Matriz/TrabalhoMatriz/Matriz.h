#ifndef MATRIZ_H
#define MATRIZ_H
#include <iostream>
#include <iomanip> //esse import é pro espacamento dos numeros no metodo de impressao
#include "Indice.h"

using namespace std;

class Matriz
{
    public:
        Matriz(int n);
        ~Matriz();
        void setValor(int i, int j, int valor);
        void imprime(Indice *indices);
    private:
        int **matriz;
        int _n;
};

#endif // MATRIZ_H
