/**
    Universidade Federal de Juiz de Fora
    CaminhoLargura.h
    Propósito: Calcula o caminho mínimo usando a busca em largura.

    @author Gabriele Cesar
    @version 1.0 12/06/19
*/

#ifndef GRAFO_CAMINHO_LARGURA_H
#define GRAFO_CAMINHO_LARGURA_H

#include <iostream>
#include "Aresta.h"
#include "No.h"
#include "Grafo.h"

class CaminhoLargura {

    public:
        CaminhoLargura(Grafo* grafo){
            this->grafo = grafo;
        }
        ~CaminhoLargura(){}

    private:
        Grafo *grafo;
        No *no;
        No *raiz;//aponta para o primeiro no da lista
        int auxTam;//guarda o tamanho exato do meu vetor aux. Dessa forma, não precisa percorrer o vetor todo.
        No *auxVetorOrdem;// lista dos nós com o id armazenado em aux
        Aresta *listaCaminho;//esta é a lista de nós para chegar até o nó procurado
        Aresta *auxPrimeiro;// guarda a última aresta adj do nó visitada
        No *primeiro;//aponta para o primeiro vertice de aux

    public:

        Aresta* busca(int id){
            //1º passo-> preciso procurar o no que posssui esse id
            no = grafo->getNo(id);
            raiz= grafo->getListaNos();//aponta para o primeiro no da lista
            auxTam=0;//guarda o tamanho exato do meu vetor aux. Dessa forma, não precisa percorrer o vetor todo.
            int aux[grafo->getOrdem()];//lista de id na qual já passei (irá funcionar como uma estrutura de fila)
            auxVetorOrdem=NULL;// lista dos nós com o id armazenado em aux
            listaCaminho=NULL;//esta é a lista de nós para chegar até o nó procurado
            auxPrimeiro=NULL;// guarda a última aresta adj do nó visitada

            if(raiz->getAresta()==NULL){
                cout<<"Não tem aresta no nó raiz, ou seja, o nó não está ligado a nenhum outro nó!";
                return NULL;
            }
            else{
                aux[0]=raiz->getId();
                No *w=NULL;
                auxPrimeiro=raiz->getAresta();
                w=grafo->getNo(auxPrimeiro->getNoAdj());
                Aresta *prox=NULL;// auxiliar para garantir que o cada aresta será armazenada no final da minha listaCaminho
                while(w->getId()!=no->getId() && auxTam!=-1){//percorrer até achar o no procurado ou até a fila ficar vazia.
                    primeiro=grafo->getNo(aux[0]);
                    auxPrimeiro=primeiro->getAresta();
                    w=grafo->getNo(auxPrimeiro->getNoAdj());//pego o id do nó adjacente a aresta
                    for(; w!=NULL && w->getId()!=no->getId(); w=grafo->getNo(auxPrimeiro->getNoAdj())){//w é um nó que procura os vizinhos do meu nó primeiro
                        cout<<"valor id w:"<<w->getId()<<"\n";
                        if(listaCaminho!=NULL){
                            for(prox=listaCaminho;prox->getProx()!=NULL;prox=prox->getProx()){};
                            prox->setProx(new Aresta(w->getId(), primeiro->getId(),primeiro->getAresta()->getPeso()));
                        }
                        else
                        listaCaminho=(new Aresta(w->getId(), primeiro->getId(),primeiro->getAresta()->getPeso()));
                        auxTam++;
                        aux[auxTam]=w->getId();
                        if(auxPrimeiro->getProx()==NULL){//avalia se o próximo vizinho é vazio
                            break;
                        }
                        else
                            auxPrimeiro=auxPrimeiro->getProx();
                    }
                    for(int i=0;i<auxTam;i++){ //depois de armazenar as arestas dos vizinhos do primeiro, atualizo o primeiro para o próximo nó vizinho
                            aux[i]=aux[i+1];
                    }
                    auxTam=auxTam-1; //atualizo o tamanho do meu vetor aux

                }
                for(prox=listaCaminho;prox->getProx()!=NULL;prox=prox->getProx()){};
                prox->setProx(new Aresta(w->getId(),primeiro->getId(),primeiro->getAresta()->getPeso()));
            }
            return listaCaminho;
        }

};


#endif //GRAFO_CAMINHO_LARGURA_H
