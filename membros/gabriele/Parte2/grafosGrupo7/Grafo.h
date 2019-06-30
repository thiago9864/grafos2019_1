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
#include "VetorOrdenado.h"
#include "ResultadoGuloso.h"


using namespace std;

class ListaGrafos; /// https://stackoverflow.com/questions/17333934/class-name-does-not-name-a-type-in-c

class Grafo
{
    public:
        Grafo();
        Grafo(bool direcionado, bool ponderadoAresta, bool ponderadoNo);
        Grafo(string formato, string entrada, string saida);
        Grafo(string formato, string entrada, string saida, bool direcionado);
        Grafo(string formato, string entrada, string saida, bool direcionado, bool ponderadoAresta);
        Grafo(string formato, string entrada, string saida, bool direcionado, bool ponderadoAresta, bool ponderadoNo);

        ~Grafo();

        void parseTXT(string arquivo);
        void parseSTP(string arquivo);

        //basico do grafo
        No* getListaNos();
        int getOrdem();
        int getNumArestas();
        No* getNo(int id);
        int getNumTerminais();
        int* getTerminais();

        bool isDirecionado();
        bool isPonderadoAresta();
        bool isPonderadoNo();

        //adicao e remocao
        bool adicionaNo(int id, float peso);
        bool adicionaAresta(int idOrigem, float pesoIdOrigem, int idDestino, float pesoIdDestino, float pesoAresta);
        bool removeNo(int id);
        bool removeAresta(int idOrigem, int idDestino);

        //matriz de adjacencia
        int noIdToPos(int id);
        int noPosToId(int pos);
        float** getMatrizAdj();

        //metodos pedidos pra primeira etapa do trabalho
        Grafo* geraGrafoComplementar();
        Aresta* caminhamentoEmLargura(int id);
        Aresta* caminhamentoEmProfundidade(int idOrigem, int idDestino);
        int listarComponentesConexas(int* indComp, int* idNos);
        int listarComponentesFortementeConexas();
        int* ordenacaoTopologica();
        Aresta* caminhoMinimoDijkstra(int origem, int destino);
        Aresta* getCaminhoMinimoFloyd(int origem, int destino);
        float getDistanciaFloyd(int origem, int destino);
        Grafo* KruskalAGM(float *soma);
        Grafo* PrimAGM(float *soma);

        //metodos pedidos pra segunda etapa do trabalho
        ResultadoGuloso guloso();
        ResultadoGuloso gulosoRandomizado(float alfa, int maxIteracoes);
        ResultadoGuloso gulosoRandomizadoReativo(int maxIteracoes);
        ResultadoGuloso gulosoExtra();


    private:
        //variaveis do grafo
        No *listaNos;
        No *ultimoNo;
        int *terminais;
        int numTerminais;
        int ordem;
        int numArestas;
        int grau;
        bool direcionado;
        bool ponderadoNo;
        bool ponderadoAresta;

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

#include "Utils.h"
#include "OrdenacaoTopologica.h"
#include "Floyd.h"
#include "Dijkstra.h"
#include "CaminhoProfundidade.h"
#include "CaminhoLargura.h"
#include "ComponentesConexas.h"
#include "Kruskal.h"
#include "Prim.h"
#include "CustomSteiner.h"

#endif // GRAFO_H
