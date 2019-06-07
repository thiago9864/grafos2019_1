//
// Created by victor on 07/05/19.
//

#include "Floyd.h"

Floyd::Floyd(Grafo *g) {
    this->g = g;
    No* head = g->getNo();

    this->ordem = g->getOrdem();
    this->matrizAdj = g->getMatrizAdj();

    // inicializando matrizes auxiliares
    this->dist = new int*[this->ordem];
    this->path = new int*[this->ordem];

    for (int i = 0; i < this->ordem; i++) {
        dist[i] = new int[this->ordem];
        path[i] = new int[this->ordem];

        for (int j = 0; j < this->ordem; j++) {
            int peso = matrizAdj[i][j];

            if (peso > 0) {
                dist[i][j] = peso;  // Peso da aresta
                path[i][j] = j;     // Destino da aresta
            } else {
                dist[i][j] = 10000000; //INF
                path[i][j] = -1;
            }
        }
    }

    for (int i = 0; i < this->ordem; i++) {
        dist[i][i] = 0;
        path[i][i] = -1;
    }

    this->floydAlgorithm();

}

void Floyd::floydAlgorithm() {

    for (int k = 0; k < this->ordem; k++) {
        for (int i = 0; i < this->ordem; i++) {
            for (int j = 0; j < this->ordem; j++) {
                if (this->dist[i][j] > this->dist[i][k] + this->dist[k][j]) {
                    this->dist[i][j] = this->dist[i][k] + this->dist[k][j];
                    this->path[i][j] = this->path[i][k];
                }
            }
        }
    }

}

Aresta* Floyd::getCaminho(int origem, int destino) {

    int origemPos = this->g->noIdToPos(origem);
    int destinoPos = this->g->noIdToPos(destino);
    Aresta *listaAresta;
    Aresta *headAresta;

    int prox = this->path[origemPos][destinoPos];

    if (prox != -1)
       listaAresta = new Aresta(this->g->noPosToId(prox), origem, this->dist[origemPos][prox]);
    else
        return nullptr;

    headAresta = listaAresta;   // Armazenando o inicio da lista de arestas

    while (prox != origemPos && prox != -1) {
        origemPos = prox;
        origem = this->g->noPosToId(prox);
        prox = this->path[prox][destinoPos]; //Próximo nó no caminho
        if (prox != -1) {
            Aresta *a = new Aresta(this->g->noPosToId(prox), origem, this->dist[origemPos][prox]);
            listaAresta->setProx(a);
            listaAresta = listaAresta->getProx(); //Percorrendo a lista
        }
    }

    return headAresta;

}

int Floyd::getDistancia(int origem, int destino) {

    int i = this->g->noIdToPos(origem);
    int j = this->g->noIdToPos(destino);

    return this->dist[i][j];

}

// void Floyd::imprime() {

//     int numCasas = 3;
//     char fillchar = ' ';
//     string espaco = " ";

//     this->g->imprime();

//     cout << "Distancia:" << endl;

//     cout << "    ";

//     for (int i = 0; i < this->ordem; i++) {
//         cout << setfill(fillchar) << setw(numCasas) << this->g->noPosToId(i) << espaco;
//     }

//     cout << endl;

//     for (int i = 0; i < this->ordem; i++) {
//         cout << setfill(fillchar) << setw(numCasas) << this->g->noPosToId(i) << espaco;

//         for (int j = 0; j < this->ordem; j++) {
//             cout << setfill(fillchar) << setw(numCasas) << this->dist[i][j] << espaco;
//         }

//         cout << endl;

//     }

//     cout << "Caminho:" << endl;

//     cout << "    ";

//     for (int i = 0; i < this->ordem; i++) {
//         cout << setfill(fillchar) << setw(numCasas) << this->g->noPosToId(i) << espaco;
//     }

//     cout << endl;

//     for (int i = 0; i < this->ordem; i++) {
//         cout << setfill(fillchar) << setw(numCasas) << this->g->noPosToId(i) << espaco;

//         for (int j = 0; j < this->ordem; j++) {
//             cout << setfill(fillchar) << setw(numCasas) << this->g->noPosToId(this->path[i][j]) << espaco;
//         }

//         cout << endl;

//     }
// }