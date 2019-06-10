#include <iostream>
#include <string>
#include "Grafo.h"
#include "OrdenacaoTopologica.h"
#include "CaminhoMinimo.h"
#include "SteinerTree.h"

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

    g->setNo(69);
    g->setAresta(69,13,10);
    g->setAresta(69,12,12);
    g->setNo(96);
    g->setAresta(96,25,50);
    g->setAresta(96,24,5);

    g->imprime();
//    g->caminho_largura(24);
//    int * ord = g->ordenacaoTopologica();
//    for (int i = 0; i < g->getOrdem()-1; i++) {
//        cout << ord[i] << ", ";
//    }
//    cout << ord[g->getOrdem()-1] << endl;

    CaminhoMinimo caminho = CaminhoMinimo(g);
    caminho.imprime();

    cout << endl;

    Aresta* cam = caminho.getCaminho(10,13);

    cout << "Distancia entre 10 e 13: " << caminho.getDistancia(10,13) << endl;

    cout << "Caminho: " << endl;
    for (Aresta* aresta = cam; aresta != nullptr; aresta = aresta->getProx()) {
        cout << "(" << aresta->getNoOrigem() << "," << aresta->getNoAdj() << ") ";
    }

    int terminais[] = {10,13,96};
    SteinerTree* steiner = new SteinerTree(g,terminais,3);
    Grafo* tree = steiner->getSteinerTree();

    tree->imprime();

    return 0;
}