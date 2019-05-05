//
// Created by victor on 01/04/19.
//

#ifndef GRAFOLISTA_GRAFO_H
#define GRAFOLISTA_GRAFO_H

#include <fstream>
#include <sstream>
#include <stack>
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

    No* getNo(int id);
    Aresta* getAresta(int idOrigem, int idFim);
    Grafo* getComplementar();

    void removeAresta(int idOrigem, int idFim);
    void removeNo(int id);

    //metodos da atividade2
    Aresta* buscaEmProfundidade(int idOrigem, int idDestino);
    int* ordenacaoTopologica();
    Aresta* caminho_largura(int id);//retornar lista de arestas

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

    //variaveis do indice da busca por profundide
    int **indices;
    int tamIndice, tamMatrizIndice;

    //metodos do indice da busca por profundide
    void iniciaIndices();
    int insereOuAtualizaVerticeNoIndice(int id, int status);
    int getStatusDoIndice(int id);

};


#endif //GRAFOLISTA_GRAFO_H
