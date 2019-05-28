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
#include <stack> 
#include "No.h"
#include "ListaArestas.h"
#include "ListaGrafos.h"
#include "Vetor.h"

using namespace std;

class ListaGrafos; /// https://stackoverflow.com/questions/17333934/class-name-does-not-name-a-type-in-c

class Grafo
{
    public:
        Grafo();
        Grafo(bool isDirecionado, bool isPonderadoVertice, bool isPonderadoAresta);
        ~Grafo();

        void parseTXT(string arquivo);
        void parseSTP(string arquivo);
        void imprimir();
        void sequenciaGrau();
        No* getGrafo();
        int getOrdem();
        No* getNo(int id);

        bool adicionaVertice(int id, float peso);
        bool adicionaAresta(int idOrigem, float pesoIdOrigem, int idDestino, float pesoIdDestino, float pesoAresta);
        bool removerVertice(int id);
        bool removerAresta(int idOrigem, int idDestino);
        ///
        Grafo* geraGrafoComplementar();
        No* buscaEmLargura(int id);
        Aresta* buscaEmProfundidade(int idOrigem, int idDestino);
        ListaGrafos* listaComponentesConexas();
        ListaGrafos* listaComponentesFortementeConexas();
        Grafo* ordenacaoTopologica();
        ///
        void obtemDistanciaMinima(int idOrigem, int idDestino);
        No* getCoberturaVertices();
        Aresta* caminhoMinimoDijkstra(int origem, int destino);
        ///
        int getNumTerminais();
        int* getTerminais();

    private:
        //variaveis do grafo
        No *listaNos;
        No *ultimoNo;
        int *terminais;
        int numTerminais;
        int ordem;
        int numArestas;
        int grau;
        bool isDirecionado;
        bool isPonderadoVertice;
        bool isPonderadoAresta;
        float maxFloat = 99999999999999999999.9;

        //variaveis do indice (auxiliar)
        int **indices;
        int tamIndice, tamMatrizIndice;

        //metodos do indice
        void iniciaIndices();
        int insereOuAtualizaVerticeNoIndice(int id, int status);
        int getStatusDoIndice(int id);
        void imprimeIndice();

        //metodos de construção do grafo
        void addNoEArestaPonderada(int id, float pesoVertice, int idAresta, float pesoVerticeAresta, float pesoAresta);
        void addNoEArestaPonderadaDigrafo(int id, float pesoVertice, int idAresta, float pesoVerticeAresta, float pesoAresta);

        //metodos auxiliares
        Aresta* procuraArestaAdjacente(int idAdjacente, No*& origem);
        Aresta* getAresta(int idOrigem, int idDestino);
        No* criaNo(int id, float peso);
        Aresta* criaAresta(int id, float peso, No*& vertice); //esse & junto com o * do ponteiro é pra variavel ficar por referencia
        bool removeItemListaAresta(No*& verticeOrigem, int idDestino); //esse & junto com o * do ponteiro é pra variavel ficar por referencia
};

#endif // GRAFO_H
