//
// Created by victor on 23/04/19.
//

#ifndef GRAFOLISTA_ORDENACAOTOPOLOGICA_H
#define GRAFOLISTA_ORDENACAOTOPOLOGICA_H

#include <iostream>
#include "No.h"

using namespace std;

class OrdenacaoTopologica {

    public:

        OrdenacaoTopologica(Grafo *grafo) {
            this->grafo = grafo;
            this->semEntrada = new No*[grafo->getOrdem()];
            this->ordenados = new int[grafo->getOrdem()];
            this->visitados = new int[grafo->getOrdem()];
            this->lenSemEntrada = 0;

            // Inicializando vetores
            for (int i = 0; i < grafo->getOrdem(); i++) {
                this->ordenados[i] = -1;
                this->visitados[i] = -1;
                this->semEntrada[i] = nullptr;
            }

        }

        ~OrdenacaoTopologica(){}

    private:
        Grafo *grafo;
        No** semEntrada;
        int lenSemEntrada = 0;
        int* ordenados;
        int* visitados;

        /// Função recursiva para visitar nós a partir ordem de precedência
        void visita(No* n, int ordem) {

            int nId = n->getId();
            int lastPosVis = find(this->visitados, -1, ordem);
            int lastPosOrd;

            if (!this->find(this->visitados, nId, ordem)) {     // Verificando se o n já foi visitado
                this->visitados[lastPosVis] = nId;              // Marcando n como visitado

                // Percorrendo todos os nós m que n tem aresta
                for (Aresta* a = n->getAresta(); a != nullptr; a = a->getProx()) {
                    No* m = this->findNo(a->getNoAdj());
                    this->visita(m, ordem);
                }

                lastPosOrd = find(this->ordenados, -1, ordem);
                this->ordenados[lastPosOrd] = n->getId();       // Adicionando n aos ordenados

            }

        }

        /// Encontra um valor dentro de um vetor de inteiros.
        int find(int *vetor, int valor, int tam) {
            for (int i = 0; i < tam; i++) {
                if (vetor[i] == valor) return i;
            }
            return 0;
        }

        /// Encontra nó pelo id.
        No* findNo(int id) {
            No *n;

            // Percorrendo lista de nós até encontrar o desejado
            for (n = grafo->getListaNos(); n != nullptr && n->getId() != id; n = n->getProx());

            return n;
        }

        /// Inverte um vetor de inteiros.
        int* inverteVetor(int *vetor, int tam) {
            int* invertido = new int[tam];
            int i = tam-1;
            int j = 0;

            for (; j < tam; j++, i--) {
                invertido[j] = vetor[i];
            }

            return invertido;

        }

    public:

        /// Realiza ordenação topológica
        int* ordenacao() {

            // Encontrando nós sem arestas de entrada
            for (No* n = grafo->getListaNos(); n != nullptr; n = n->getProx()) {
                if (n->getGrauEntrada() == 0) {
                    this->semEntrada[lenSemEntrada] = n;
                    this->lenSemEntrada++;
                }
            }

            if (lenSemEntrada == 0) {
                cout << "Grafo contem um ciclo" << endl;
                return nullptr;
            }

            // Visitando todos os nós recursivamente, começando pelos que não tem arestas de entrada
            for (int i = 0; i < lenSemEntrada; i++) {
                visita(semEntrada[i], grafo->getOrdem());
            }

            this->ordenados = this->inverteVetor(this->ordenados, grafo->getOrdem());

            return this->ordenados;

        }

};


#endif //GRAFOLISTA_ORDENACAOTOPOLOGICA_H
