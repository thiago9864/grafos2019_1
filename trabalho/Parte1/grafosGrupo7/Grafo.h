/**
    Universidade Federal de Juiz de Fora
    Grafo.h
    Propósito: Representa o grafo.

    @author Victor Aquiles
    @version 1.0 01/04/19
*/


#ifndef GRAFOLISTA_GRAFO_H
#define GRAFOLISTA_GRAFO_H

#include <fstream>
#include <sstream>
#include <stack>
#include "No.h"
#include "VetorOrdenado.h"

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
    No* getListaNos();
    Aresta* getAresta(int idOrigem, int idFim);
    Grafo* getComplementar();
    bool getConexo();
    int getOrdem();
    int getGrau();
    int getNumArestas();

    bool isDirecionado();
    bool isPonderadoAresta();
    bool isPonderadoNo();

    // Matriz de Adjacência e auxiliares
    float** getMatrizAdj();
    int noIdToPos(int id);
    int noPosToId(int pos);

    // Caminho Mínimo
    Aresta* getCaminhoFloyd(int origem, int destino);
    float getDistanciaFloyd(int origem, int destino);
    Aresta* getCaminhoDijkstra(int origem, int destino);
    Grafo* KruskalAGM(float *soma);
    Grafo* PrimAGM();

    void removeAresta(int idOrigem, int idFim);
    void removeNo(int id);

    //metodos da atividade2
    Aresta* buscaEmProfundidade(int idOrigem, int idDestino);
    int* ordenacaoTopologica();
    Aresta* caminho_largura(int id);//retornar lista de arestas
    int componenteConexa(int *indComp, int *idNos);

    //metodos da atividade 3

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

#include "Utils.h"
#include "OrdenacaoTopologica.h"
#include "Floyd.h"
#include "Dijkstra.h"
#include "CaminhoProfundidade.h"
#include "CaminhoLargura.h"
#include "ComponentesConexas.h"
#include "Kruskal.h"
#include "Prim.h"

#endif //GRAFOLISTA_GRAFO_H
