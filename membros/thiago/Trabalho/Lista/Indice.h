#ifndef INDICE_H
#define INDICE_H
#include <iostream>

using namespace std;

class Indice
{
    public:
        Indice(int n);
        ~Indice();
        int insereVerticeNoIndice(int id);
        int procuraPosicaoNoIndice(int id);
        int getPos(int pos);
        int getTamIndice();
    private:
        int *indices;
        int _n;
        int tamIndice;        
        
};

#endif // INDICE_H
