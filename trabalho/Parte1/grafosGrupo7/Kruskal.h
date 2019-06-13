/**
    Universidade Federal de Juiz de Fora
    Kruskal.h
    Propósito: Calcula a arvore geradora mínima com o algoritmo de Kruskal.

    @author Laura Polverari
    @version 1.0 12/05/19
*/

#ifndef GRAFO_KRUSKAL_H
#define GRAFO_KRUSKAL_H

#include <iostream>
#include "Aresta.h"
#include "No.h"
#include "Grafo.h"
#include "ComponentesConexas.h"

class Kruskal {

    public:
        Kruskal(Grafo *grafo){
            this->grafo = grafo;
        }
        ~Kruskal(){}

    private:
        Grafo *grafo;

        void vetorIdNos(int* idNos) // Função auxiliar que preenche o vetor com os ids dos nós da lista.
        {
            No *n;
            int i;
            for(n = grafo->getListaNos(), i = 0; n != nullptr; n = n->getProx(), i++) {
                idNos[i] = n->getId();
            }

        }

        int encontraIndice(int *idNos, int id) // Função auxiliar que encontra a posição "i" de um id em um vetor idNos.
        {
            int i;
            for(i = 0; i < grafo->getOrdem(); i++) {
                if(idNos[i] == id) {
                    break;
                }
            }
            return i;
        }


        // Função auxiliar que realiza a troca de posições entre valores dos vetores passados como parâmetro.
        void troca(float *pesos, Aresta *conj, int i, int j)
        {
            float pAux = pesos[i];
            pesos[i] = pesos[j];
            pesos[j] = pAux;

            Aresta aAux = conj[i];
            conj[i] = conj[j];
            conj[j] = aAux;
        }

        // Função auxiliar que retorna o índice da partição do QuickSort. Utiliza-se como pivô a última posição do vetor.
        int particao(float *pesos, Aresta *conj, int inicio, int fim)
        {
            float pivo = pesos[fim];
            int i = inicio - 1;

            for(int j = inicio; j < fim; j++) {
                if(pesos[j] <= pivo) {
                    i++;
                    troca(pesos, conj, i, j);
                }
            }
            troca(pesos, conj, i + 1, fim);

            return (i + 1);
        }
        // Fun��o recursiva que implementa um QuickSort para fazer a ordena��o dos vetores passados como par�metro.
        void ordenaVetor(float *pesos, Aresta *conj, int inicio, int fim)
        {
            if(inicio < fim) {
                int indPart = particao(pesos, conj, inicio, fim);

                ordenaVetor(pesos, conj, inicio, indPart - 1);
                ordenaVetor(pesos, conj, indPart + 1, fim);
            }
        }

    public:
        
        // Função usada para encontrar o conjunto de arestas da árvore geradora mínima de um grafo.
        // Retorna a soma dos pesos das arestas desse conjunto.
        float gerar(Aresta *arestasAGM)
        {
            if(grafo->isDirecionado() == false) {
                int cont = 0;
                bool verifica[grafo->getOrdem()][grafo->getOrdem()]; // Matriz auxiliar que será utilizada para que não haja repetição de arestas adicionadas a conjArestas.
                Aresta conjArestas[grafo->getNumArestas()]; // Vetor que será preenchido com todas as arestas do grafo (conjunto de arestas candidatas � solução).
                int idNos[grafo->getOrdem()]; // Vetor que será preenchido com os ids dos nós do grafo.
                vetorIdNos(idNos);
                float pesosArestas[grafo->getNumArestas()]; // Vetor que será preenchido com os pesos das arestas do grafo.

                Aresta *a;
                No *n;
                int i;
                for(i = 0, n = grafo->getListaNos(); i < grafo->getOrdem() && n != nullptr; i++, n = n->getProx()) {
                for(a = n->getAresta(); a!= nullptr; a = a->getProx()) {
                    a->setOrigem(n->getId()); // Identificando a extremidade da aresta que não é 'noAdj'.
                }
                }

                for(int i = 0; i < grafo->getOrdem(); i++) {
                    for(int j = 0; j < grafo->getOrdem(); j++) {
                        verifica[i][j] = false;
                    }
                }

                int r = 0;
                for(i = 0, n = grafo->getListaNos(); i < grafo->getOrdem() && n != nullptr; i++, n = n->getProx()) { // Preenche 'conjArestas' com as arestas do grafo.
                    for(a = n->getAresta(); a!= nullptr; a = a->getProx()) {
                        int j = encontraIndice(idNos, a->getNoAdj()); // Encontra índice do vetor 'idNos' correspondente ao id do nó adjacente a aresta em questão.

                        if(verifica[i][j] != true) { // Checa se a aresta já se encontra em 'conjArestas'.
                            conjArestas[r] = *a; // Adiciona aresta a 'conjArestas'.
                            verifica[i][j] = true; // Marca na matriz auxiliar 'verifica' que a aresta entre os nós da linha 'i' e coluna 'j' já foi inserida em 'conjArestas'.
                            verifica[j][i] = true; // Aresta entre os nós da linha 'i' e coluna 'j' equivale a aresta entre os nós da linha 'j' e coluna 'i'.
                            r++; // Passar� para a pr�xima posição do vetor 'conjArestas'.
                        }
                    }
                }

                for(int i = 0; i < grafo->getNumArestas(); i++) { // Preenche 'pesosArestas' com os pesos das arestas do grafo.
                    pesosArestas[i] = conjArestas[i].getPeso();
                }

                // Ordena em ordem crescente o vetor 'pesosArestas' e o vetor 'conjArestas'.
                ordenaVetor(pesosArestas, conjArestas, 0, grafo->getNumArestas() - 1);

                int comp[grafo->getOrdem()]; // Vetor que indicará a quais componentes conexas cada nó do grafo pertence (ao longo do processo).
                for(int i = 0; i < grafo->getOrdem(); i++) { // Inicialmente, temos o número de componentes conexas igual ao número de nós.
                    comp[i] = idNos[i];
                }

                i = 0;

                while(i < grafo->getNumArestas() && cont < grafo->getOrdem() - 1) { // Preenche 'arestasAGM' com as arestas que formarão a árvore geradora mínima do grafo.
                    int a = encontraIndice(idNos, conjArestas[i].getOrigem());
                    int b = encontraIndice(idNos, conjArestas[i].getNoAdj());
                    if(comp[a] != comp[b]) { // Se os nós pertencem a componentes conexas distintas, é possível a adição da aresta a solução (pois não se formará um ciclo).
                    arestasAGM[cont] = conjArestas[i]; // Adiciona a aresta é solução.
                    cont++;
                    if(comp[a] < comp[b]) { // Nós que pertencem a mesma componente ficam com o valor de id do nó de menor id da componente.
                        int t = comp[b];
                        comp[b] = comp[a];
                        for(int f = 0; f < grafo->getOrdem(); f++) {
                            if(comp[f] == t) {
                                comp[f] = comp[a];
                            }
                        }
                    }
                    else {
                        int p = comp[a];
                        comp[a] = comp[b];
                        for(int f = 0; f < grafo->getOrdem(); f++) {
                            if(comp[f] == p) {
                                comp[f] = comp[b];
                            }
                        }
                    }
                    }

                    i++;
                }

                float somaPesos = 0.0;
                for(int c = 0; c < grafo->getOrdem() - 1; c++) { // Soma os pesos das arestas que estão na solução.
                    somaPesos += arestasAGM[c].getPeso();
                }

                return somaPesos;
            }

            return -1.0;
        }
};


#endif //GRAFO_KRUSKAL_H






