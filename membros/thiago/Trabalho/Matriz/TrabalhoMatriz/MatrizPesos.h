#ifndef MATRIZPESOS_H
#define MATRIZPESOS_H
#include <iostream>
#include <iomanip> //esse import é pro espacamento dos numeros no metodo de impressao
#include "Indice.h"

using namespace std;

class MatrizPesos
{
    public:
        MatrizPesos(int n);
        ~MatrizPesos();
        void setValor(int i, int j, float valor);
        void imprime(Indice *indices);
    private:
        float **matriz;
        int _n;
};

#endif // MATRIZPESOS_H
