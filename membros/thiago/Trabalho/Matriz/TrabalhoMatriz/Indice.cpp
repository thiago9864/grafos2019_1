#include "Indice.h"

Indice::Indice(int n)
{
    _n = n;
    // aloca o vetor de vetores
    indices = new int*[n];
    // aloca cada um dos vetores (cada linha)
    for(int i = 0; i < n; i++)
    {
        int *tmp = new int[2];
        tmp[0] = 0;
        tmp[1] = 0;
        indices[i] = tmp;
    }
}

Indice::~Indice()
{
    // desaloca os indices
    for(int i = 0; i < _n; i++)
    {
        delete [] indices[i];
    }
    delete [] indices;
}


void Indice::insereVerticeNoIndice(int id)
{
    indices[contIndice] = id;
}

void Indice::procuraPosicaoNoIndice(int id)
{
    for(int i = 0; i < n; i++)
    {
        indices[i][1];
    }
}
