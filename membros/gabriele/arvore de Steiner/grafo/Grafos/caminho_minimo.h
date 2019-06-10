#ifndef CAMINHO_MINIMO_H_INCLUDED
#define CAMINHO_MINIMO_H_INCLUDED
#include "matrix.h"
#include "grafo.h"
class caminho{
public:
    caminho(Grafo *g);
    ~caminho();
    void montandoMatriz();
    void auxMontando(int ind);

private:
    Matrix_adj caminho;
    bool marcador[ordem];
    int indNo[ordem];
    int indCaminho[ordem];
    float caminhoPeso[ordem];
    Grafo *g;
    No *no;
};


#endif // CAMINHO_MINIMO_H_INCLUDED
