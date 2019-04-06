#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include"matrix_adj.h"
class Grafo{
public:
    Grafo(bool direcao);
    ~Grafo();
    void leitura_arquivo(string arquivo);
    void caminhamento_lagura();
    void caminhamento_profundidade();

private:
    Matrix_adj matrix;
    bool direcionado;
    int ordem;
};
#endif // GRAFO_H_INCLUDED
