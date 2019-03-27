//
// Created by victor on 22/03/19.
//

#ifndef TEORIADOSGRAFOS_GRAFO_H
#define TEORIADOSGRAFOS_GRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Estrutura de nó do grafo
struct No {
    int nome;
    int valor = -1;
};

// Criando o tipo lista de sucessores
typedef vector<No> NoVector;
typedef vector<NoVector> ListSuc;

class Grafo {
public:

    Grafo();
    Grafo(string arquivo);
    ~Grafo();

    void insert_no(int nome);
    void imprime();

private:

    ListSuc *grafo; //lista de_sucessores

    int leitura_arquivo(vector<vector<string>> *dados, string arquivo);
    void split(vector<string> *v, string str, char c);
};


#endif //TEORIADOSGRAFOS_GRAFO_H
