/**
    Universidade Federal de Juiz de Fora
    CustomSteiner.h
    Propósito: Representa o algoritmo criado pelo grupo para resolver o problema da Arvore de Steiner.

    @author Laura Polverari, Gabriele Cesar, Thiago Almeida, Victor Aquiles
    @version 1.0 01/04/19
*/


#ifndef CUSTOMSTEINER_H
#define CUSTOMSTEINER_H

#include "No.h"
#include "Grafo.h"

class CustomSteiner {

    public:

        CustomSteiner(Grafo *grafo){
            this->grafo = grafo;
            cout << "Processando Floyd" << endl;
            floyd = new Floyd(grafo, grafo->getMatrizAdj());
        };

        ~CustomSteiner() {

        }

    private:
        Grafo *grafo;
        Floyd* floyd;

        void remover(int *vetor, int *tam, int valor){
            //encontra
            int indice = -1;
            for(int i=0; i<*tam; i++){
                if(vetor[i] == valor){
                    indice = i;
                    break;
                }
            }
            //desloca
            if(indice != -1){
                for(int i=indice+1; i<*tam; i++){
                    vetor[i-1] = vetor[i];
                }
            }
            *tam = *tam - 1;
        }
        void adicionar(int *vetor, int *tam, int valor){
            vetor[*tam] = valor;
            *tam = *tam + 1;
        }

    public:

        Grafo *steiner_antigo(){
            int *S = new int[grafo->getOrdem()];
            S[0] = grafo->getTerminais()[0];
            int n_sol = 1;

            int *C = new int[grafo->getNumTerminais()];
            int n_can = 0;
            for(int j=1; j<grafo->getNumTerminais();j++){
                C[n_can] = grafo->getTerminais()[j];
                n_can++;
            }


            Grafo *h = new Grafo(false, true, false);

            cout << "processando steiner" << endl;

            while(n_can > 0){
                float custo = 99999999999999.9;
                int id_origem_escolhido=-1;
                int id_destino_escolhido=-1;

                for(int i=0; i<n_sol;i++){
                    int id_sol = S[i];

                    for(int j=0; j<n_can;j++){
                        int id_can = C[j];
                        float peso = floyd->getDistancia(id_sol, id_can);

                        //cout << id_sol << " " << id_can << " " << peso << endl;
                        if(peso < custo){
                            custo = peso;
                            id_origem_escolhido = id_sol;
                            id_destino_escolhido = id_can;
                        }
                    }

                }

                if(id_origem_escolhido != -1){
                    Aresta *aux = floyd->getCaminhoAresta(id_origem_escolhido, id_destino_escolhido);
                    while(aux != NULL){
                        //cout << "Add Aresta: (" << aux->getOrigem() << ", " << aux->getNoAdj() << ") " << aux->getPeso() << endl;
                        h->adicionaAresta(aux->getOrigem(), 1, aux->getNoAdj(), 1, aux->getPeso());
                        aux = aux->getProx();
                    }
                    remover(C, &n_can, id_destino_escolhido);
                    adicionar(S, &n_sol, id_destino_escolhido);

                    cout << n_sol << " de " << grafo->getNumTerminais() << endl;

                } else {
                    cout << "CustomSteiner: O grafo nao e conexo!" << endl;
                    return NULL;
                }

            }

            //tentando melhorar o resultado
            No**solucao = new No*[h->getOrdem()];
            No*p = h->getListaNos();
            int count = 0;
            while(p!=NULL){
                solucao[count]=p;
                p = p->getProx();
                count++;
            }
            Grafo *grafoInduzido = grafo->subgrafoInduzido(solucao, h->getOrdem());
            float soma=0;
            h = h->KruskalAGM(&soma);



            return h;

            /*
            isso no mac-mini
            [media tempo], [media custo], [best]      , [erro]
            214.000000   , 81175.000000 , 59797.000000, 0.357510

            isso no notebook
            [timestamp], [media tempo], [media custo], [best], [erro]
            1561834822,143.000000,81175.000000,59797.000000,0.357510

            [timestamp], [media tempo], [media custo], [best], [erro]
            1561835115,144.000000,81175.000000,59797.000000,0.357510
             */

        }

};

#endif //CUSTOMSTEINER_H
