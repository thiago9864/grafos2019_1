#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <fstream>
#include <sstream>
#include "No.h"
#include"aresta.h"
using namespace std;
class Grafo{
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

    Aresta* caminho_largura(int id);//retornar lista de arestas

    Aresta** prim();
    void ordenar(Aresta **a, int n);
    int binarySearch(Aresta **a, Aresta *item, int low, int high);

    int getOrdem(){return ordem;};

    //poda
    void poda(No **solucao,int n);

private:
    No *listaNos;//lista de nós no grafo
    int ordem;//tamanho do grafo informado pelo usuário
    bool direcional;
    int grau;
    int m;
    bool ponderadoNo;
    bool ponderadoAresta;

    void atualizaGrau(int grau);
    void atualizaGrau();
    void leitura_arquivo(string arquivo);
};


#endif // GRAFO_H_INCLUDED
