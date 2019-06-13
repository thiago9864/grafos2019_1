/**
    Universidade Federal de Juiz de Fora
    Aresta.h
    Propósito: Calcula o caminho mínimo usando o algoritmo de Floyd.

    @author Victor Aquiles
    @version 1.0 07/05/19
*/

#ifndef FLOYD_H
#define FLOYD_H

#include "No.h"
#include <limits>
#include <iomanip>
#include "Grafo.h"

class Floyd {

    public:
        Floyd(Grafo *grafo, float** matrizAdj) {
            this->grafo = grafo;

            this->matrizAdj = matrizAdj;

            // inicializando matrizes auxiliares
            this->dist = new float*[grafo->getOrdem()];
            this->path = new int*[grafo->getOrdem()];

            for (int i = 0; i < grafo->getOrdem(); i++) {
                dist[i] = new float[grafo->getOrdem()];
                path[i] = new int[grafo->getOrdem()];

                for (int j = 0; j < grafo->getOrdem(); j++) {
                    float peso = matrizAdj[i][j];

                    if (peso > -1) {
                        dist[i][j] = peso;  // Peso da aresta
                        path[i][j] = j;     // Destino da aresta
                    } else {
                        dist[i][j] = 10000000.0; //INF
                        path[i][j] = -1;
                    }
                }
            }

            for (int i = 0; i < grafo->getOrdem(); i++) {
                dist[i][i] = 0;
                path[i][i] = -1;
            }

            this->floydAlgorithm();

        }
        ~Floyd(){}
        
    private:
        Grafo* grafo;
        float** matrizAdj;
        float** dist;
        int** path;
        int tamCaminho = 1;

        void floydAlgorithm() {

            for (int k = 0; k < grafo->getOrdem(); k++) {
                for (int i = 0; i < grafo->getOrdem(); i++) {
                    for (int j = 0; j < grafo->getOrdem(); j++) {
                        if (this->dist[i][j] > this->dist[i][k] + this->dist[k][j]) {
                            this->dist[i][j] = this->dist[i][k] + this->dist[k][j];
                            this->path[i][j] = this->path[i][k];
                        }
                    }
                }
            }

        }

        /**
         * Posição do nó na matriz de adjacência.
         * @param id Id do nó a ser procurado
         * @return posição do nó na matriz 
        */
        int noIdToPos(int id) {
            int pos = 0;

            for (No* n = grafo->getListaNos(); n != nullptr; n = n->getProx(), pos++) {
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
        int noPosToId(int pos) {
            int id;
            int i = 0;

            for (No* n = grafo->getListaNos(); n != nullptr; n = n->getProx(), i++) {
                if (i == pos)
                    return n->getId();
            }
            return -1;
        }

    public:

        Aresta* getCaminhoAresta(int origem, int destino) {

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

        int* getCaminhoInt(int origem, int destino) {

            int origemPos = this->noIdToPos(origem);
            int destinoPos = this->noIdToPos(destino);
            Aresta *listaAresta;
            Aresta *headAresta;
            tamCaminho = 1;
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
            caminho[0] = headAresta->getOrigem();
            int i = 1;
            for(Aresta* a = headAresta; a != nullptr; a = a->getProx()) {
                caminho[i] = a->getNoAdj();
                i++;
            }

            return caminho;

        }

        int getTamCaminho(){
            return tamCaminho;
        }

        float getDistancia(int origem, int destino) {

            int i = this->noIdToPos(origem);
            int j = this->noIdToPos(destino);

            return this->dist[i][j];

        }

        void imprime() {

            int numCasas = 3;
            char fillchar = ' ';
            string espaco = " ";

            cout << "Matriz de Adjacencia:" << endl;

            cout << "    ";

            for (int i = 0; i < grafo->getOrdem(); i++) {
                cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;
            }

            cout << endl;

            for (int i = 0; i < grafo->getOrdem(); i++) {
                cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;

                for (int j = 0; j < grafo->getOrdem(); j++) {
                    cout << setfill(fillchar) << setw(numCasas) << this->matrizAdj[i][j] << espaco;
                }

                cout << endl;

            }

            cout << "Distancia:" << endl;

            cout << "    ";

            for (int i = 0; i < grafo->getOrdem(); i++) {
                cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;
            }

            cout << endl;

            for (int i = 0; i < grafo->getOrdem(); i++) {
                cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;

                for (int j = 0; j < grafo->getOrdem(); j++) {
                    cout << setfill(fillchar) << setw(numCasas) << this->dist[i][j] << espaco;
                }

                cout << endl;

            }

            cout << "Caminho:" << endl;

            cout << "    ";

            for (int i = 0; i < grafo->getOrdem(); i++) {
                cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;
            }

            cout << endl;

            for (int i = 0; i < grafo->getOrdem(); i++) {
                cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(i) << espaco;

                for (int j = 0; j < grafo->getOrdem(); j++) {
                    cout << setfill(fillchar) << setw(numCasas) << this->noPosToId(this->path[i][j]) << espaco;
                }

                cout << endl;

            }
        }

};

#endif //FLOYD_H
