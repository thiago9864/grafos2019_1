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

        bool adicionaVertice(int id, float peso);
        bool adicionaAresta(int idOrigem, float pesoIdOrigem, int idDestino, float pesoIdDestino, float pesoAresta);
        bool removerVertice(int id);
        bool removerAresta(int idOrigem, int idDestino);
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
        Aresta* procuraArestaAdjacente(int idAdjacente, No*& origem);
        bool arestaExiste(int idOrigem, int idDestino);
        No* criaNo(int id, float peso);
        Aresta* criaAresta(int id, float peso, No*& vertice); //esse & junto com o * do ponteiro é pra variavel ficar por referencia
        bool removeItemListaAresta(No*& verticeOrigem, int idDestino); //esse & junto com o * do ponteiro é pra variavel ficar por referencia
};

#endif // GRAFO_H
