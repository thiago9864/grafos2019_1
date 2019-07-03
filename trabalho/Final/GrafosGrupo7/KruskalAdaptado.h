/**
    Universidade Federal de Juiz de Fora
    Kruskal.h
    Propósito: Calcula a arvore geradora mínima com o algoritmo de Kruskal.

    @author Thiago Almeida
    @version 1.0 12/05/19
*/

#ifndef GRAFO_KRUSKAL_H
#define GRAFO_KRUSKAL_H

#include <iostream>
#include "Aresta.h"
#include "No.h"
#include "Grafo.h"

class Kruskal {

    public:
        Kruskal(Grafo *grafo){
            this->grafo = grafo;
            this->max_num_arestas = grafo->getNumArestas();
            this->vetor_candidatos = new Aresta[this->max_num_arestas];
        }
        ~Kruskal(){
            delete vetor_candidatos;
        }

    private:
        Grafo *grafo;
        int max_num_arestas = 0;
        int num_arestas_candidatas = 0;
        Aresta *vetor_candidatos = NULL;

        Aresta* copiar(T* subv){
            Aresta* vr = new T[max_num_arestas];
            for(int i=0; i<max_num_arestas; i++){
                vr[i] = subv[i];
            }
            return vr;
        }

        void addAresta(Aresta *aresta){

            //insere ordenado
            if(num_arestas_candidatas == 0 || vetor_candidatos[num_arestas_candidatas-1][0].getPeso() < aresta->getPeso())
            {
                //se o vetor estiver vazio ou o valor é maior do que o ultimo, insere em o(1)
                vetor[num_arestas_candidatas][0] = *aresta;
                num_arestas_candidatas++;
            }
            else if(num_arestas_candidatas == 1)
            {
                //o vetor tem 1 e o valor é menor que o vetor[0], insere em o(1)
                Aresta *aux = copiar(vetor[0]);
                vetor[0] = *aresta;
                vetor[1] = aux;
                num_arestas_candidatas++;
            }
            else
            {
                //o valor esta no meio do vetor, encontra o primeiro maior que ele
                int i;
                for(i=0; i < num_arestas_candidatas; i++)
                {
                    if(vetor[i].getPeso() > aresta->getPeso())
                    {
                        break;
                    }
                }

                //faz o deslocamento do vetor
                for(int j=num_arestas_candidatas; j > i; j--)
                {
                    vetor[j] = copiar(vetor[j-1]);
                }

                //insere ele na posicao, em o(n)
                vetor[i] = aresta;

                //conta a inserção
                num_arestas_candidatas++;
            }
        }

        void auxKruskal(){

            //atualiza o vetor de candidatos
            No *p=
        }

    public:

        // Função que retorna o subgrafo correspondente a arvore geradora mínima do grafo.
        Grafo* gerar(float *soma, int *num_componentes)
        {
            *num_componentes = 0;
            *soma = 0;

            Grafo *h = new Grafo(false, true, false);

            return h;
        }
};


#endif //GRAFO_KRUSKAL_H






