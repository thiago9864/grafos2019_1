//
// Created by victor on 07/05/19.
//

#include "Floyd.h"

Floyd::Floyd(No* listaNos, float** matrizAdj) {
    this->listaNos = listaNos;

    this->ordem = 0;
    for (No* n = this->listaNos; n != nullptr; n = n->getProx(), this->ordem++);

    this->matrizAdj = matrizAdj;

    // inicializando matrizes auxiliares
    this->dist = new float*[this->ordem];
    this->path = new int*[this->ordem];

    for (int i = 0; i < this->ordem; i++) {
        dist[i] = new float[this->ordem];
        path[i] = new int[this->ordem];

        for (int j = 0; j < this->ordem; j++) {
            float peso = matrizAdj[i][j];

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

Aresta* Floyd::getCaminhoAresta(int origem, int destino) {

    int origemPos = this->noIdToPos(origem);
    int destinoPos = this->noIdToPos(destino);
    Aresta *listaAresta;
    Aresta *headAresta;

    int prox = this->path[origemPos][destinoPos];

    if (prox != -1)
       listaAresta = new Aresta(this->noPosToId(prox), origem, this->dist[origemPos][prox]);
    else
        return nullptr;

    headAresta = listaAresta;   // Armazenando o inicio da lista de arestas

    while (prox != origemPos && prox != -1) {
        origemPos = prox;
        origem = this->noPosToId(prox);
        prox = this->path[prox][destinoPos]; //Próximo nó no caminho
        if (prox != -1) {
            Aresta *a = new Aresta(this->noPosToId(prox), origem, this->dist[origemPos][prox]);
            listaAresta->setProx(a);
            listaAresta = listaAresta->getProx(); //Percorrendo a lista
        }
    }

    return headAresta;

}

int* Floyd::getCaminhoInt(int origem, int destino) {

    int origemPos = this->noIdToPos(origem);
    int destinoPos = this->noIdToPos(destino);
    Aresta *listaAresta;
    Aresta *headAresta;
    int tamCaminho = 1;
    int* caminho;

    int prox = this->path[origemPos][destinoPos];

    if (prox != -1) {
       listaAresta = new Aresta(this->noPosToId(prox), origem, this->dist[origemPos][prox]);
       tamCaminho++;
    } else
        return nullptr;

    headAresta = listaAresta;   // Armazenando o inicio da lista de arestas

    while (prox != origemPos && prox != -1) {
        origemPos = prox;
        origem = this->noPosToId(prox);
        prox = this->path[prox][destinoPos]; //Próximo nó no caminho
        if (prox != -1) {
            Aresta *a = new Aresta(this->noPosToId(prox), origem, this->dist[origemPos][prox]);
            listaAresta->setProx(a);
            listaAresta = listaAresta->getProx(); //Percorrendo a lista
            tamCaminho++;
        }
    }

    caminho = new int[tamCaminho];
    caminho[0] = headAresta->getNoOrigem();
    int i = 1;
    for(Aresta* a = headAresta; a != nullptr; a = a->getProx()) {
        caminho[i] = a->getNoAdj();
        i++;
    }

    return caminho;

}

float Floyd::getDistancia(int origem, int destino) {

    int i = this->noIdToPos(origem);
    int j = this->noIdToPos(destino);

    return this->dist[i][j];

}

void Floyd::imprime() {

    int numCasas = 3;
    char fillchar = ' ';
    string espaco = " ";

    cout << "Matriz de Adjacencia:" << endl;

    cout << "    ";

    for (int i = 0; i < this->ordem; i++) {
        cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;
    }

    cout << endl;

    for (int i = 0; i < this->ordem; i++) {
        cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;

        for (int j = 0; j < this->ordem; j++) {
            cout << setfill(fillchar) << setw(numCasas) << this->matrizAdj[i][j] << espaco;
        }

        cout << endl;

    }

    cout << "Distancia:" << endl;

    cout << "    ";

    for (int i = 0; i < this->ordem; i++) {
        cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;
    }

    cout << endl;

    for (int i = 0; i < this->ordem; i++) {
        cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;

        for (int j = 0; j < this->ordem; j++) {
            cout << setfill(fillchar) << setw(numCasas) << this->dist[i][j] << espaco;
        }

        cout << endl;

    }

    cout << "Caminho:" << endl;

    cout << "    ";

    for (int i = 0; i < this->ordem; i++) {
        cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;
    }

    cout << endl;

    for (int i = 0; i < this->ordem; i++) {
        cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;

        for (int j = 0; j < this->ordem; j++) {
            cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(this->path[i][j]) << espaco;
        }

        cout << endl;

    }
}

/**
 * Posição do nó na matriz de adjacência.
 * @param id Id do nó a ser procurado
 * @return posição do nó na matriz 
*/
int Floyd::noIdToPos(int id) {
    int pos = 0;

    for (No* n = this->listaNos; n != nullptr; n = n->getProx(), pos++) {
        if (n->getId() == id)
            return pos;
    }
    return -1;
}

/**
 * Id do nó da posição passada na matriz de adjacência.
 * @param pos Posição do nó a ser procurado
 * @return id do nó procurado
*/
int Floyd::noPosToId(int pos) {
    int id;
    int i = 0;

    for (No* n = this->listaNos; n != nullptr; n = n->getProx(), i++) {
        if (i == pos)
            return n->getId();
    }
    return -1;
}
