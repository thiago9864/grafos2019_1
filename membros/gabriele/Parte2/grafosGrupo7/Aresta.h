/**
    Universidade Federal de Juiz de Fora
    Aresta.h
    Propósito: Representa uma aresta no grafo.

    @author Victor Aquiles
    @version 1.0 01/04/19
*/

#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>

using namespace std;

class Aresta {

    public:

        Aresta(){}
        Aresta(int no){
            this->noAdj = no;
            this->peso = -1;
            this->prox = nullptr;
        }
        Aresta(int no, float peso){
            this->noAdj = no;
            this->peso = peso;
            this->prox = nullptr;
        }
        Aresta(int no, int noOrigem, float peso){
            this->noAdj = no;
            this->peso = peso;
            this->noOrigem = noOrigem;
            this->prox = nullptr;
        }

        ~Aresta(){
            // Deletando todas as arestas
            //Aresta* p = prox;
            //while(p != NULL){
                //Aresta *a = p->getProx();
                //rever o porque esse delete dá erro com o stack do c++
                //delete p;
                //p = a;
            //}
        }

    private:

        int noAdj;
        float peso;
        Aresta* prox;
        int noOrigem;

    public:

        // *** Getters ***

        float getPeso() { return peso; }

        Aresta* getProx() { return this->prox; }

        int getNoAdj() { return this->noAdj; }

        int getOrigem(){ return noOrigem; }

        void setOrigem(int orig) { noOrigem = orig; }

        // *** Setters ***

        void setProx(Aresta *aresta) { this->prox = aresta; }

};


#endif //ARESTA_H
