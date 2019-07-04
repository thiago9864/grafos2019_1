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
            this->vetor_candidatos = new Aresta*[this->max_num_arestas];
        }
        ~Kruskal(){
            delete vetor_candidatos;
        }

    private:
        Grafo *grafo;
        int max_num_arestas = 0;
        int num_arestas_candidatas = 0;
        Aresta **vetor_candidatos = NULL;

        void addAresta(Aresta *aresta){

            //insere ordenado
            if(num_arestas_candidatas == 0 || vetor_candidatos[num_arestas_candidatas-1]->getPeso() < aresta->getPeso())
            {
                //se o vetor estiver vazio ou o valor щ maior do que o ultimo, insere em o(1)
                vetor_candidatos[num_arestas_candidatas] = aresta;
                num_arestas_candidatas++;
            }
            else if(num_arestas_candidatas == 1)
            {
                //o vetor tem 1 e o valor щ menor que o vetor[0], insere em o(1)
                Aresta *aux = vetor_candidatos[0];
                vetor_candidatos[0] = aresta;
                vetor_candidatos[1] = aux;
                num_arestas_candidatas++;
            }
            else
            {
                //o valor esta no meio do vetor, encontra o primeiro maior que ele
                int i;
                for(i=0; i < num_arestas_candidatas; i++)
                {
                    if(vetor_candidatos[i]->getPeso() > aresta->getPeso())
                    {
                        break;
                    }
                }

                //faz o deslocamento do vetor
                for(int j=num_arestas_candidatas; j > i; j--)
                {
                    vetor_candidatos[j] = vetor_candidatos[j-1];
                }

                //insere ele na posicao, em o(n)
                vetor_candidatos[i] = aresta;

                //conta a inserчуo
                num_arestas_candidatas++;
            }
        }

        bool checaArestaDoVetor(int origem, int destino, int posicao){
            bool ida = vetor_candidatos[posicao]->getOrigem() == origem && vetor_candidatos[posicao]->getNoAdj() == destino;
            bool volta = vetor_candidatos[posicao]->getOrigem() == destino && vetor_candidatos[posicao]->getNoAdj() == origem;
            return (ida && volta)
        }

        bool existeAresta(int origem, int destino)
        {
            if(num_arestas_candidatas == 0)
            {
                return false;
            }
            else
            {
                if(num_arestas_candidatas == 1 && checaArestaDoVetor(origem, destino, 0))
                {
                    return 0;
                }
                else
                {
                    //busca binaria (o vetor está ordenado)
                    int inicio = 0;
                    int fim = num_arestas_candidatas-1;
                    int meio;

                    while (inicio <= fim)
                    {
                        meio = (inicio + fim)/2;
                        if (indice == vetor_candidatos[meio]->getPeso())
                        {
                            return true;
                        }
                        if (indice < vetor_candidatos[meio]->getPeso())
                        {
                            fim = meio-1;
                        }
                        else
                        {
                            inicio = meio+1;
                        }
                    }
                    return false;   // não encontrado
                }
            }


        void auxKruskal(){

            //cria o vetor de candidatos
            Np *p = grafo->getListaNos();
            while(p!=NULL){
                Aresta *a = p->getAresta();
                while(a!=NULL){
                    a=a->getProx();
                    if(existeAresta(a->getOrigem(), a->getNoAdj()) == false){
                        addAresta(Aresta *aresta);
                    }
                }
                p=p->getProx();
            }

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






