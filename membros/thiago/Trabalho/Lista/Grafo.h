/**
    Universidade Federal de Juiz de Fora
    Grafo.h
    Propósito: Classe que representa o grafo e contém metodos de manipulação.

    @author Thiago Almeida
    @version 1.0 30/03/19 
*/

#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Log.h"
#include "No.h"
#include "ListaArestas.h"
#include "ListaGrafos.h"
#include "Indice.h"
#include "PilhaAresta.h"

using namespace std;

class ListaGrafos; /// https://stackoverflow.com/questions/17333934/class-name-does-not-name-a-type-in-c

class Grafo
{
    public:
        Grafo();
        Grafo(bool isDirecionado, bool isPonderadoVertice, bool isPonderadoAresta);
        ~Grafo();

        void parse(string arquivo);
        void imprimir();
        void sequenciaGrau();
        No* getGrafo();
        No* getNo(int id);

        bool adicionaVertice(int id, float peso);
        bool adicionaAresta(int idOrigem, float pesoIdOrigem, int idDestino, float pesoIdDestino, float pesoAresta);
        bool removerVertice(int id);
        bool removerAresta(int idOrigem, int idDestino);
        Grafo* geraGrafoComplementar();
        No* buscaEmLargura(int id);
        ListaArestas* buscaEmProfundidade(int idOrigem, int idDestino);
        ListaGrafos* listaComponentesConexas();
        ListaGrafos* listaComponentesFortementeConexas();
        Grafo* ordenacaoTopologica();

    private:
        No *listaNos;
        No *ultimoNo;
        int ordem;
        int numArestas;
        int grau;
        bool isDirecionado;
        bool isPonderadoVertice;
        bool isPonderadoAresta;

        void addNoEArestaPonderada(int id, float pesoVertice, int idAresta, float pesoVerticeAresta, float pesoAresta);
        void addNoEArestaPonderadaDigrafo(int id, float pesoVertice, int idAresta, float pesoVerticeAresta, float pesoAresta);

        
        Aresta* procuraArestaAdjacente(int idAdjacente, No*& origem);
        Aresta* getAresta(int idOrigem, int idDestino);
        No* criaNo(int id, float peso);
        Aresta* criaAresta(int id, float peso, No*& vertice); //esse & junto com o * do ponteiro é pra variavel ficar por referencia
        bool removeItemListaAresta(No*& verticeOrigem, int idDestino); //esse & junto com o * do ponteiro é pra variavel ficar por referencia
};

#endif // GRAFO_H