/**
    Universidade Federal de Juiz de Fora
    Prim.h
    Propósito: Calcula a arvore geradora mínima com o algoritmo de Prim.

    @author Gabriele Cesar
    @version 1.0 12/05/19
*/


#ifndef GRAFO_PRIM_H
#define GRAFO_PRIM_H

#include <iostream>
#include "Aresta.h"
#include "No.h"
#include "Grafo.h"

class Prim {

    public:
        Prim(Grafo *grafo){
            this->grafo;
        }
        ~Prim(){}

    private:
        Grafo *grafo;

        void ordenar(Aresta **a,int n){
            int i, loc, j, k;
            Aresta *selected=NULL;

            for (i = 1; i < n; ++i)
            {
                j = i - 1;
                selected = a[i];
                // find location where selected sould be inseretd
                loc = binarySearch(a, selected, 0, j);
                // Move all elements after location to create space
                while (j >= loc)
                {
                    a[j+1] = a[j];
                    j--;
                }
                a[j+1] = selected;
            }
        }

        //função para ordenar
        int binarySearch(Aresta **a, Aresta *item, int low, int high)
        {
            if (high <= low){
                return (item->getPeso() > a[low]->getPeso())?  (low + 1): low;
            }


            int mid = (low + high)/2;
            if(item->getPeso() == a[mid]->getPeso())
                return mid+1;

            if(item->getPeso() > a[mid]->getPeso())
                return binarySearch(a, item, mid+1, high);

            return binarySearch(a, item, low, mid-1);
        }

    public:
        
        //**Algoritmo de Prim**//
        //retorna lista de arestas da árvore geradora de custo mínima
        Aresta** gerar(){
            No *noAtual=NULL;
            int aux;
            int tamSolucao=0;//conta o tamanho de primVet
            int cont=0;//conta o tamanho da lista de arestas adjacentes do noAtual
            noAtual=grafo->getListaNos();//n� atual de an�lise
            Aresta **primVet=new Aresta*[grafo->getOrdem()];//vetor de arestas de menor peso
            Aresta *arestaAdj=NULL;//lista de arestas adjacentes aos noAtuais, que s�o atualizados na intera��o
            Aresta **arestaVet=new Aresta*[grafo->getOrdem()];//auxilar para arestaAdj com o objetivo de ordenar
            //1� passo: transformar em um vetor de aresta
            //2� passo: pegar o vetor de arestas adjacentes e ordenar
            //3� passo: marcar o n� visitado
            //4� passo: pegar a primeira posi��o deste vetor
            //5� passo: atualizar o n� atual
            while(noAtual->getMarca()==false&&tamSolucao<grafo->getOrdem()-1){
                arestaAdj=noAtual->getAresta();//recebeu uma lista de arestas adjacentes
                for(Aresta *w=arestaAdj;w!=NULL;w=w->getProx()){
                    if(tamSolucao==0){//primeira vez que for inserir no vetor de arestas adjacentes
                        arestaVet[cont]=new Aresta(w->getNoAdj(),w->getOrigem(),w->getPeso());
                        cont++;
                    }
                    else{//evitar a forma��o de ciclos
                        for(aux=0;aux<cont&&grafo->getNo(arestaVet[aux]->getNoAdj())!=grafo->getNo(w->getNoAdj());aux++);//verificar se o n� adjacente da lista de arestaAdj j� foi inserido como n� adjacente da solu��o primVet
                        if(aux==cont){//percorreu e n�o encontrou no adjacente igual ao da arestaVet
                            arestaVet[cont]=new Aresta(w->getNoAdj(),w->getOrigem(),w->getPeso());
                            cont++;
                        }
                        else{
                            if(arestaVet[aux]->getPeso()>w->getPeso()){//se uma aresta com o n� adjacente a um j� pertencente ao vetor arestaVet tiver peso menor a aresta do vetor arestaVet, fa�o a substitui��o
                                arestaVet[aux]=new Aresta(w->getNoAdj(),w->getOrigem(),w->getPeso());
                            }
                        }
                    }
                }

                this->ordenar(arestaVet,cont);
                if(grafo->getNo(arestaVet[0]->getNoAdj())->getMarca()==true){//se a menor aresta j� foi inserida, verifica a possibilidade de inserir at� achar uma que ainda n�o tenha sido inserida, na lista de arestas de menor peso
                    for(aux=0;aux<tamSolucao && grafo->getNo(arestaVet[aux]->getNoAdj())->getMarca()==true;aux++);
                    primVet[tamSolucao]=arestaVet[aux];
                    tamSolucao++;
                    noAtual->setMarca();
                    noAtual=grafo->getNo(arestaVet[aux]->getNoAdj());
                    for(int i=aux;i<cont-1;i++){
                        arestaVet[i]=arestaVet[i+1];
                    }
                    cont--;
                }
                else{
                    primVet[tamSolucao]=arestaVet[0];
                    tamSolucao++;
                    noAtual->setMarca();
                    noAtual=grafo->getNo(arestaVet[0]->getNoAdj());
                    for(int i=0;i<cont-1;i++){
                        arestaVet[i]=arestaVet[i+1];
                    }
                    cont--;
                }

            }
            return  primVet;
        }

};


#endif //GRAFO_PRIM_H






