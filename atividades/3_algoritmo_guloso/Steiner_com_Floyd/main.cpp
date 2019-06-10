#include <iostream>
#include <string>
#include "Grafo.h"
#include "OrdenacaoTopologica.h"
#include "CaminhoMinimo.h"
#include "SteinerTree.h"

/**
Atividade 3 - Algoritmo guloso

INSTANCIA STEINER 8 TERMINAIS E 64 VERTICES (Resultado exato: 2338)
clear && g++ -std=c++11 *.cpp -o main && ./main ../data/cc3-4p_R2338.txt ../data/saida.txt


Comando descrito
./main <arq entrada> <arq saida> <direcionado> <ponderadoVertice> <ponderadoAresta>

Parametros
<arq entrada>       = Caminho do arquivo contendo a instancia
<arq saida>         = Caminho do arquivo com os logs de saída
<direcionado>       = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoVertice>  = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoAresta>   = 1: Sim, 0: Não (opcional, Sim por padrão)
**/

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 6) {
        cout << "Argumentos passados invalidos";

        return 0;
    }

    Grafo *g;

    // Verificando a quantidade de argumentos passados
    if (argc == 6) {
        g = new Grafo(argv[1], argv[2], stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
    } else if (argc == 5) {
        g = new Grafo(argv[1], argv[2], stoi(argv[3]), stoi(argv[4]));
    } else if (argc == 4) {
        g = new Grafo(argv[1], argv[2], stoi(argv[3]));
    } else {
        g = new Grafo(argv[1], argv[2]);
    }
    /*
    g->setNo(69);
    g->setAresta(69,13,10);
    g->setAresta(69,12,12);
    g->setNo(96);
    g->setAresta(96,25,50);
    g->setAresta(96,24,5);
    */

    //g->imprime();
//    g->caminho_largura(24);
//    int * ord = g->ordenacaoTopologica();
//    for (int i = 0; i < g->getOrdem()-1; i++) {
//        cout << ord[i] << ", ";
//    }
//    cout << ord[g->getOrdem()-1] << endl;

    /*
    CaminhoMinimo caminho = CaminhoMinimo(g);
    caminho.imprime();

    cout << endl;

    Aresta* cam = caminho.getCaminho(10,13);

    cout << "Distancia entre 10 e 13: " << caminho.getDistancia(10,13) << endl;

    cout << "Caminho: " << endl;
    for (Aresta* aresta = cam; aresta != nullptr; aresta = aresta->getProx()) {
        cout << "(" << aresta->getNoOrigem() << "," << aresta->getNoAdj() << ") ";
    }
    */
    int terminais[] = {1,16,20,29,38,43,55,58};
    SteinerTree* steiner = new SteinerTree(g,terminais,8);
    Grafo* tree = steiner->getSteinerTree();

    tree->imprime();

    return 0;
}