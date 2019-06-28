/**
    Universidade Federal de Juiz de Fora
    CaminhoProfundidade.h
    Propósito: Calcula o caminho mínimo usando a busca em profundidade.

    @author Thiago Almeida
    @version 1.0 12/06/19
*/

#ifndef GRAFO_CAMINHO_PROFUNDIDADE_H
#define GRAFO_CAMINHO_PROFUNDIDADE_H

#include <iostream>
#include <stack>
#include "No.h"
#include "VetorOrdenado.h"

class CaminhoProfundidade {

    public:
        CaminhoProfundidade(Grafo *grafo){
            this->grafo = grafo;
        }
        ~CaminhoProfundidade();

    private:
        Grafo *grafo;
        stack <Aresta> pilha;
        bool continuar = true;
        No *atual;
        VetorOrdenado<int> *visitados;

    public:

        Aresta* busca(int idOrigem, int idDestino)
        {
            continuar = true;
            atual = grafo->getNo(idOrigem);
            Aresta *listaRetorno = NULL;

            visitados = new VetorOrdenado<int>(grafo->getOrdem(), 2);

            if(atual == NULL){
                cout << "O vertice de origem é nulo" << endl;
                return NULL;
            }

            //preenche visitados com os vertices disponiveis e coloca status 0 em todos
            No *p = grafo->getListaNos();
            while(p != NULL)
            {
                visitados->addIndex(p->getId(), 0);

                //proximo vertice
                p = p->getProx();
            }

            while(continuar)
            {
                if(atual->getId() == idDestino)
                {
                    //o vertice destino foi encontrado. Desemplilha e retorna o caminho
                    int tam = pilha.size();
                    int count = tam-1;

                    //transfere as arestas da pilha pra um vetor
                    Aresta* caminho = new Aresta[tam];
                    while(!pilha.empty())
                    {
                        caminho[count] = pilha.top();
                        pilha.pop();
                        count--;
                    }

                    //cria uma lista encadeada de arestas pra retornar
                    Aresta *ultimaAresta = NULL;
                    for(int i=0; i < tam; i++)
                    {
                        Aresta arestaDaPilha = caminho[i];

                        //cria aresta de retorno
                        Aresta *arestaCaminho = new Aresta(arestaDaPilha.getNoAdj(), arestaDaPilha.getOrigem(), arestaDaPilha.getPeso());

                        if(listaRetorno == NULL){
                            listaRetorno = arestaCaminho;
                        } else {
                            ultimaAresta->setProx(arestaCaminho);
                        }

                        ultimaAresta = arestaCaminho;
                    }
                    //delete caminho;
                    delete visitados;
                    return listaRetorno;
                }

                //marca o atual como visitado (1)
                visitados->set(atual->getId(), 1, 1);

                //percorre as arestas até encontrar um vertice não visitado (0)
                Aresta *aresta = atual->getAresta();
                bool achouVerticeNaoVisitado = false;
                while(aresta != NULL)
                {
                    //procura status do nó
                    int status = visitados->getByIndice(aresta->getNoAdj(), 1);
                    
                    if(status == 0 || status == -1)//0 se tem indice e -1 se nem indice tem
                    {
                        //achou vertice vizinho não visitado, muda pra ele
                        atual = grafo->getNo(aresta->getNoAdj());
                        achouVerticeNaoVisitado = true;

                        //registra na pilha por cópia
                        pilha.push(*aresta);
                        break;
                    }
                    aresta = aresta->getProx();
                }
                if(!achouVerticeNaoVisitado)
                {
                    //nao achou nenhum não visitado, marca como completo (2)
                    visitados->set(atual->getId(), 1, 2);

                    //percorre as arestas até encontrar uma já visitada (1) pra voltar
                    Aresta *aresta = atual->getAresta();
                    bool achouVerticeVisitado = false;
                    while(aresta != NULL)
                    {
                        int status = visitados->getByIndice(aresta->getNoAdj(), 1);
                        if(status == 1)
                        {
                            //achou vertice visitado, volta pra ele
                            atual = grafo->getNo(aresta->getNoAdj());
                            achouVerticeVisitado = true;
                            //cout << "volta pra " << atual->getId() << endl;
                            cout << pilha.empty() << endl;
                            pilha.pop();
                            break;
                        }
                        aresta = aresta->getProx();
                    }
                    

                    if(!achouVerticeVisitado)
                    {
                        //não encontrou vertice já visitado, todos estão completos (2). Condição de parada
                        //verificar se visitou todos os vertices
                        if(visitados->getTamanho() == grafo->getOrdem())
                        {
                            //visitou todos. acabou o algoritmo
                            continuar = false;
                            cout << "visitou todos e não encontrou" << endl;
                        }
                        else
                        {
                            cout << "O destino está em outra componente conexa!" << endl;
                            //A busca percorreu toda essa componente conexa, tem mais no grafo.
                            //a partir daqui não existe caminho do nó de origem ao de destino. Parar a busca.
                            return NULL;
                        }
                    }
                }
            }

            return NULL;
        }

};


#endif //GRAFO_CAMINHO_PROFUNDIDADE_H
