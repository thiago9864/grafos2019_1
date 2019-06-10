//
// Created by victor on 09/05/19.
//

#ifndef GRAFOLISTA_GRAFOMATRIZ_H
#define GRAFOLISTA_GRAFOMATRIZ_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class GrafoMatriz {

public:

    GrafoMatriz(int n_nos);
    GrafoMatriz(string entrada, string saida);
    GrafoMatriz(string entrada, string saida, bool direcional);
    GrafoMatriz(string entrada, string saida, bool direcional, bool ponderadoAresta);
    GrafoMatriz(string entrada, string saida, bool direcional, bool ponderadoAresta, bool ponderadoNo);
    ~GrafoMatriz();

    void imprime();
    void imprime(string arquivo);

    void setNo(int id);
    void setAresta(int idOrigem, int idFim, int peso);
    void setAresta(int idOrigem, int idFim);

    int getArestaPos(int i, int j);
    int getArestaId(int origem, int destino);
    int getGrauNoEntrada(int id);
    int getGrauNoSaida(int id);

    int findId(int id);
    int idPos(int pos);

private:

    int **matrix = nullptr;     // Matriz de Adjacência
    int *ids = nullptr;           // Vetor para armazenar o id de cada nó

    int ordem;
    int m;
    int grau;
    bool direcional;
    bool ponderadoNo;
    bool ponderadoAresta;

    void inicializa_matrix(int n_nos);
    void leitura_arquivo(string arquivo);
    int lastPos(int *v);
    void atualizaGrau(int grau);

};


#endif //GRAFOLISTA_GRAFOMATRIZ_H
