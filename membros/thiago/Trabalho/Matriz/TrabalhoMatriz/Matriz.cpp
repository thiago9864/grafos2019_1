#include "Matriz.h"

Matriz::Matriz(int n)
{
    // aloca o vetor de vetores
    matriz = new float*[n];

    // aloca cada um dos vetores (cada linha)
    for(int i = 0; i < n; i++)
    {
        //aloca um vetor temporario
        float *tmp = new float[n];

        //seta valores 0
        for(int i = 0; i < n; i++)
        {
            tmp[i] = 0;
        }

        //passa ponteiro do vetor tmp pra matriz
        matriz[i] = tmp;
    }

}

Matriz::~Matriz()
{
    // desaloca a matriz
    for(int i = 0; i < _n; i++)
    {
        delete [] matriz[i];
    }
    delete [] matriz;
}


