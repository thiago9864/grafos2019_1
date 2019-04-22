//
// Created by victor on 04/04/19.
//

#ifndef GRAFOMATRIX_GRAFO_H
#define GRAFOMATRIX_GRAFO_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Grafo {

public:

    Grafo(int n_nos);
    Grafo(string entrada, string saida);
    Grafo(string entrada, string saida, bool direcional);
    Grafo(string entrada, string saida, bool direcional, bool ponderadoAresta);
    Grafo(string entrada, string saida, bool direcional, bool ponderadoAresta, bool ponderadoNo);
    ~Grafo();

    void imprime();
    void imprime(string arquivo);

    void setNo(int id);
    void setAresta(int idOrigem, int idFim, float peso);
    void setAresta(int idOrigem, int idFim);

    int getGrauNoEntrada(int id);
    int getGrauNoSaida(int id);

private:

    float **matrix;     // Matriz de Adjacência
    int *ids;           // Vetor para armazenar o id de cada nó

    int ordem;
    int m;
    int grau;
    bool direcional;
    bool ponderadoNo;
    bool ponderadoAresta;

    void inicializa_matrix(int n_nos);
    void leitura_arquivo(string arquivo);
    int findId(int id);
    int lastPos(int *v);
    void atualizaGrau(int grau);

};


#endif //GRAFOMATRIX_GRAFO_H
