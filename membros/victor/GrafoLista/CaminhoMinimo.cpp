//
// Created by victor on 07/05/19.
//

#include "CaminhoMinimo.h"

CaminhoMinimo::CaminhoMinimo(Grafo *g) {
    No* head = g->getNo();

    this->ordem = g->getOrdem();
    this->matrizAdj = new GrafoMatriz(this->ordem);

    // Preenchendo matriz de adjacencia
    for (No* n = head; n != nullptr; n = n->getProx()) {
        for (Aresta* a = n->getAresta(); a != nullptr; a = a->getProx()) {
            matrizAdj->setAresta(n->getId(), a->getNoAdj(), a->getPeso());
        }
    }

    // inicializando matrizes auxiliares
    this->dist = new int*[this->ordem];
    this->path = new int*[this->ordem];

    for (int i = 0; i < this->ordem; i++) {
        dist[i] = new int[this->ordem];
        path[i] = new int[this->ordem];

        for (int j = 0; j < this->ordem; j++) {
            int peso = matrizAdj->getArestaPos(i, j);

            if (peso > 0) {
                dist[i][j] = peso;
                path[i][j] = peso;
            } else {
                dist[i][j] = numeric_limits<int>::max(); //INF
                path[i][j] = -1;
            }

        }
    }

}

void CaminhoMinimo::floydAlgorithm() {

    for (int k = 0; k < this->ordem; k++) {
        for (int i = 0; i < this->ordem; i++) {
            for (int j = 0; j < ordem; j++) {
                if (this->dist[i][j] > this->dist[i][k] + this->dist[k][j]) {
                    this->dist[i][j] = this->dist[i][k] + this->dist[k][j];
                    this->path[i][j] = k;
                }
            }
        }
    }

}

Aresta* CaminhoMinimo::getCaminho(int origem, int destino) {

    int origemPos = this->matrizAdj->findId(origem);
    int destinoPos = this->matrizAdj->findId(destino);
    Aresta *listaAresta;

    int prox = this->path[origemPos][destinoPos];

    if (prox != -1)
       listaAresta = new Aresta(destinoPos, origemPos, this->dist[origemPos][destinoPos]);
    else
        return nullptr;

    while (prox != origemPos && prox != -1) {
        prox = this->path[origemPos][prox]; //Próximo nó no caminho
        if (prox != -1) {
            Aresta *a = new Aresta(prox, origemPos, this->dist[origemPos][prox]);
            listaAresta->setProx(a);
        }
    }

    return listaAresta;

}

int CaminhoMinimo::getDistancia(int origem, int destino) {

    int i = this->matrizAdj->findId(origem);
    int j = this->matrizAdj->findId(destino);

    return this->dist[i][j];

}

void CaminhoMinimo::imprime() {
    this->matrizAdj->imprime();

    cout << "Distancia" << endl;

    for (int i = 0; i < this->ordem; i++) {
        for (int j = 0; j < ordem; j++) {
                cout << this->dist[i][j] << " ";
            }
        }
        cout << endl;
    }
}