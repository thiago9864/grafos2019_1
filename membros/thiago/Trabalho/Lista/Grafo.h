#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Log.h"
#include "No.h"
#include "ListaDeGrafos.h"

using namespace std;

class Grafo
{
    public:
        Grafo(bool _direcional, int ponderado);
        ~Grafo();

        void parse(string nomeArquivo);
        void imprimir();
        void sequenciaGrau();
        No* getGrafo();

        void adicionaVertice(int id, float peso);
        void adicionaAresta(int idOrigem, float pesoIdOrigem, int idDestino, float pesoIdDestino, float pesoAresta);
        void removerVertice(int id);
        void removerAresta(int idOrigem, int idDestino, float peso);
        Grafo* geraGrafoComplementar();
        No* buscaEmLargura(int id);
        No* buscaEmProfundidade(int id);
        ListaDeGrafos* listaComponentesConexas();
        ListaDeGrafos* listaComponentesFortementeConexas();
        Grafo* ordenacaoTopologica();

    private:
        No *listaNos;
        No *ultimoNo;
        int ordem;
        int numArestas;
        int grau;
        bool direcional;
        int ponderado;

        void addNoEArestaPonderada(int id, float pesoVertice, int idAresta, float pesoVerticeAresta, float pesoAresta);
        void addNoEArestaPonderadaDigrafo(int id, float pesoVertice, int idAresta, float pesoVerticeAresta, float pesoAresta);

        No* procuraNo(int id);
        Aresta* procuraArestaAdjacente(int idAdjacente, float peso, No*& origem);
        bool arestaExiste(int idOrigem, int idDestino, float peso);
        No* criaNo(int id, float peso);
        Aresta* criaAresta(int id, float peso, No*& vertice); //esse & junto com o * do ponteiro é pra variavel ficar por referencia
};

#endif // GRAFO_H
