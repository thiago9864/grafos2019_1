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

    int getNoPos(int id);
    No* getNo(int id);
    No* getNo();
    Aresta* getAresta(int idOrigem, int idFim);
    int getOrdem();
    bool getDirecional();

    void removeAresta(int idOrigem, int idFim);
    void removeNo(int id);

    int componenteConexa(int *indComp, int *idNos);

private:

    No* listaNos;
    int ordem;
    int m;
    int grau;
    bool direcional;
    bool ponderadoNo;
    bool ponderadoAresta;

    void buscaProfCompConexa(int *indComp, int i, int numComp, int *idNos);
    void vetorIdNos(int* idNos);
    int encontraIndice(int *idNos, int id);

    void atualizaGrau(int grau);
    void atualizaGrau();
    void leitura_arquivo(string arquivo);

};


#endif //GRAFOLISTA_GRAFO_H
