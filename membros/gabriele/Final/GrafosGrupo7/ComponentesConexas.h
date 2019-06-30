/**
    Universidade Federal de Juiz de Fora
    ComponentesConexas.h
    Propósito: Calcula o número de componentes conexas no grafo dado.

    @author Laura Polverari
    @version 1.0 12/06/19
*/

#ifndef GRAFO_COMPONENTES_CONEXAS_H
#define GRAFO_COMPONENTES_CONEXAS_H

#include <iostream>
#include "Aresta.h"
#include "No.h"
#include "Grafo.h"

class ComponentesConexas {

    public:
        ComponentesConexas(Grafo* grafo){
            this->grafo = grafo;
        }
        ~ComponentesConexas(){}

    private:
        Grafo *grafo;

        // Função auxiliar recursiva que executa uma busca em profundidade para encontrar as componentes conexas do grafo.
        void buscaProfCompConexa(int *indComp, int i, int numComp, int *idNos)
        {

            indComp[i] = numComp;
            No *n = grafo->getNo(idNos[i]);


            for(Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) {
                i = encontraIndice(idNos, a->getNoAdj());
                if(indComp[i] == -1) {
                    buscaProfCompConexa(indComp, i, numComp, idNos);
                }
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

    public:

        void vetorIdNos(int* idNos) // Função auxiliar que preenche o vetor com os ids dos nós da lista.
        {
            No *n;
            int i;
            for(n = grafo->getListaNos(), i = 0; n != nullptr; n = n->getProx(), i++) {
                idNos[i] = n->getId();
            }

        }
    
        // Função que retorna o número de componentes conexas presentes no grafo.
        // Também possibilita a identificação de qual vértice pertence a qual componente a partir do vetor indComp, que será modificado
        // durante a execução.
        int componenteConexa(int* indComp, int* idNos)
        {
            vetorIdNos(idNos);
            if(grafo->isDirecionado() == false) {
                int numComp = 0;
                for(int i = 0; i < grafo->getOrdem(); i++) {
                    indComp[i] = -1;
                }
                for(int i = 0; i < grafo->getOrdem(); i++) {
                    if(indComp[i] == -1) {
                        buscaProfCompConexa(indComp, i, numComp++, idNos);
                    }
                }

                return numComp;
            }

            return -1;
        }

};


#endif //GRAFO_COMPONENTES_CONEXAS_H
