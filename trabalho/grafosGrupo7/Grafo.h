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
    Grafo(string formato, string entrada, string saida);
    Grafo(string formato, string entrada, string saida, bool direcional);
    Grafo(string formato, string entrada, string saida, bool direcional, bool ponderadoAresta);
    Grafo(string formato, string entrada, string saida, bool direcional, bool ponderadoAresta, bool ponderadoNo);
    ~Grafo();


    void imprime();
    void imprime(string arquivo);

    void setNo(int id, float peso);
    void setNo(int id);
    void setAresta(int idOrigem, int idFim, float peso);
    void setAresta(int idOrigem, int idFim);

    No* getNo(int id);
    No* getNo();
    Aresta* getAresta(int idOrigem, int idFim);
    Grafo* getComplementar();
    bool getConexo();
    int getOrdem();

    void removeAresta(int idOrigem, int idFim);
    void removeNo(int id);

    //metodos da atividade2
    Aresta* buscaEmProfundidade(int idOrigem, int idDestino);
    int* ordenacaoTopologica();
    Aresta* caminho_largura(int id);//retornar lista de arestas
    int componenteConexa(int *indComp, int *idNos);

    //metodos da atividade 3
    No* getCoberturaVertices();

private:

    No* listaNos;
    int *terminais;
    int numTerminais;
    int ordem = 0;
    int m = 0;
    int grau = 0;
    bool direcional;
    bool ponderadoNo;
    bool ponderadoAresta;
    bool conexo;

    void atualizaGrau(int grau);
    void atualizaGrau();
    void leitura_arquivo(string arquivo);//para ler o arquivo txt
    void leitura_arquivo_stp(string arquivo);//para ler os arquivos das instancias

    //variaveis do indice da busca por profundidade
    int **indices;
    int tamIndice, tamMatrizIndice;

    //metodos do indice da busca por profundide
    void iniciaIndices();
    int insereOuAtualizaVerticeNoIndice(int id, int status);
    int getStatusDoIndice(int id);

    //metodos para componentes conexas
    void buscaProfCompConexa(int *indComp, int i, int numComp, int *idNos);
    void vetorIdNos(int* idNos);
    int encontraIndice(int *idNos, int id);

};


#endif //GRAFOLISTA_GRAFO_H
