//
// Created by victor on 01/04/19.
//

#ifndef GRAFOLISTA_GRAFO_H
#define GRAFOLISTA_GRAFO_H

#include <fstream>
#include <sstream>
#include "No.h"

using namespace std;

class Grafo {

public:

    Grafo();
    Grafo(string entrada, string saida);
    Grafo(string entrada, string saida, bool direcional);
    Grafo(string entrada, string saida, bool direcional, bool ponderadoAresta);
    Grafo(string entrada, string saida, bool direcional, bool ponderadoAresta, bool ponderadoNo);
    ~Grafo();


    void imprime();
    void imprime(string arquivo);

    void setNo(int id, float peso);
    void setNo(int id);
    void setAresta(int idOrigem, int idFim, float peso);
    void setAresta(int idOrigem, int idFim);

    No* getNo(int id);
    Aresta* getAresta(int idOrigem, int idFim);

    void removeAresta(int idOrigem, int idFim);
    void removeNo(int id);

private:

    No* listaNos;
    int ordem;
    int m;
    int grau;
    bool direcional;
    bool ponderadoNo;
    bool ponderadoAresta;

    void atualizaGrau(int grau);
    void leitura_arquivo(string arquivo);

};


#endif //GRAFOLISTA_GRAFO_H
