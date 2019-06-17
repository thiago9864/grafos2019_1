/**
    Universidade Federal de Juiz de Fora
    Dijkstra.h
    Propósito: Calcula o caminho mínimo usando o algoritmo de Dijkstra.

    @author Thiago Almeida
    @version 1.3 12/06/19
*/

#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <iostream>
#include <stack>
#include "No.h"
#include "VetorOrdenado.h"


class Dijkstra
{
    public:
        Dijkstra(Grafo *grafo){
            this->grafo = grafo;
        }
        ~Dijkstra();

    private:
        Grafo *grafo;
        VetorOrdenado<int> *candidatos;
        VetorOrdenado<float> *pesos;
        stack <int> *pilha;
        float maxFloat = 9999999999999999.9;

        Aresta* getAresta(int idOrigem, int idFim) {
            No *n = grafo->getNo(idOrigem); // Encontrando nó de origem

            // Se encontrar nó inicia a busca se não retorna nullptr
            if (n != nullptr) {
                Aresta* a = n->getAresta();

                // Procurando aresta com nó passado, se encontrar o retorna, se não retorna nullptr
                for (; a != nullptr && a->getNoAdj() != idFim; a = a->getProx());

                return a;

            } else {
                return nullptr;
            }

        }

    public:
    
        Aresta* caminhoMinimo(int origem, int destino)
        {
            candidatos = new VetorOrdenado<int>(grafo->getOrdem(), 1);//armazena ids dos candidatos
            pesos = new VetorOrdenado<float>(grafo->getOrdem(), 3);//armazena os ids, pesos e predecessores
            pilha = new stack<int>();//pilha de solução

            //seleciona o primeiro candidato, que vai ser o vertice de origem
            No *atual = grafo->getNo(origem);

            if(atual == NULL){
                cout << "O vertice de origem é nulo" << endl;
                return NULL;
            }

            //preenche candidatos e inicia pesos
            No *p = grafo->getListaNos();
            while(p != NULL)
            {
                candidatos->addIndex(p->getId(), 0);
                pesos->addIndex(p->getId(), -1);

                //proximo vertice
                p = p->getProx();
            }

            //inicia pesos
            p = grafo->getListaNos();
            while(p != NULL)
            {
                if(p->getId() == origem){
                    pesos->set(p->getId(), 1, 0);
                } else {
                    pesos->set(p->getId(), 1, maxFloat);
                }

                //proximo vertice
                p = p->getProx();
            }

            //loop principal
            while(candidatos->getTamanho() > 0)
            {
                //percorre os nós adjacentes ao vertice atual
                Aresta *a = atual->getAresta();
                float peso_atual = pesos->getByIndice(atual->getId(), 1);

                //cout << "atual: " << atual->getId() << endl;
                //cout << "a nulo? " << (a == NULL) << endl;

                //verifica arestas adjacentes do atual
                while(a != NULL){

                    float peso_aresta = a->getPeso();
                    float peso_adj = pesos->getByIndice(a->getNoAdj(), 1);

                    //verifica se pode atualizar o peso de alguma aresta adjacente
                    if(peso_atual + peso_aresta < peso_adj){
                        //atualiza o peso do no adjacente
                        pesos->set(a->getNoAdj(), 1, peso_atual + peso_aresta);

                        //se o nó foi atualizado, coloca o atual como predescessor dele
                        pesos->set(a->getNoAdj(), 2, atual->getId());

                        //cout << "definiu " << atual->getId() << " como predecessor de " << a->getNoAdj() << endl;
                    }

                    a = a->getProx();
                }

                //cout << "ra" << endl;

                //remove da lista de candidatos
                candidatos->removeById(atual->getId());

                //procura menor peso entre os candidatos
                float menor_peso = maxFloat;
                int pos_menor_peso = -1;

                for(int i=0; i < candidatos->getTamanho(); i++){
                    float peso = pesos->getByIndice(candidatos->getByPos(i, 0), 1);
                    if(peso < menor_peso){
                        menor_peso = peso;
                        pos_menor_peso = i;
                    }
                }

                //cout << pos_menor_peso << endl;

                if(pos_menor_peso == -1){
                    break;
                }

                //marca como atual
                atual = grafo->getNo(candidatos->getByPos(pos_menor_peso, 0));

                //cout << "---" << endl;
            }

            cout << "Vetor de pesos" << endl << endl;
            pesos->imprime();

            if(pesos->getByIndice(destino, 1) == maxFloat){
                cout << "Não tem caminho pra esse destino" << endl;
                return NULL;
            } else {
                //monta a pilha de solução
                int d = destino;
                pilha->push(d);

                while(d != origem)
                {
                    int a = (int)pesos->getByIndice(d, 2);

                    if(a == -1){
                        cout << endl << "Algum vertice armazenado na matriz não foi lido corretamente" << endl;
                        exit(1);
                    }

                    pilha->push(a);
                    d = a;
                }
                //cout << endl;

                //cout << endl << "vai montar a lista encadeada" << endl;
                //cout << "tamanho da pilha: " << pilha->size() << endl;

                //exit(1);

                //monta a lista encadeada de arestas
                int orig = pilha->top();
                pilha->pop();
                Aresta *la = NULL;
                Aresta *ultima = NULL;
                int lim = 0;

                while(!pilha->empty()){
                    int dest = pilha->top();
                    pilha->pop();

                    float peso = getAresta(orig, dest)->getPeso();

                    //cout << orig << " " << dest << " " << peso << endl;

                    Aresta *aux = new Aresta(orig, dest, peso);

                    if(ultima == NULL){
                        la = aux;
                    } else{
                        ultima->setProx(aux);
                    }

                    ultima = aux;
                    orig = dest;
                }

                return la;
            }

            //cout << "fim" << endl;
            delete pilha;
            delete candidatos;
            delete pesos;
        }
};

#endif // DIJKSTRA_H
