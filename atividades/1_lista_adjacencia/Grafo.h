//
// Created by victor on 01/04/19.
//

#ifndef GRAFOLISTA_GRAFO_H
#define GRAFOLISTA_GRAFO_H

#include <fstream>
#include <sstream>
#include "No.h"
#include "OrdenacaoTopologica.h"

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

    int getNoPos(int id);
    No* getNo(int id);
    No* getNo();
    Aresta* getAresta(int idOrigem, int idFim);
    int getOrdem();
    bool getDirecional();
    Grafo* getComplementar();

    void removeAresta(int idOrigem, int idFim);
    void removeNo(int id);

    int* ordenacaoTopologica();

private:

    No* listaNos;
    int ordem = 0;
    int m = 0;
    int grau = 0;
    bool direcional;
    bool ponderadoNo;
    bool ponderadoAresta;

    void atualizaGrau(int grau);
    void atualizaGrau();
    void leitura_arquivo(string arquivo);

};


#endif //GRAFOLISTA_GRAFO_H
