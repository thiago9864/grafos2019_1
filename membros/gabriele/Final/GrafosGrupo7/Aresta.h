/**
    Universidade Federal de Juiz de Fora
    Aresta.h
    Propósito: Representar arestas de um grafo.

    @author Thiago Almeida
    @version 1.0 30/03/19
*/

#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>

using namespace std;

class Aresta
{
    public:
        Aresta(){};

        Aresta(int no, int noOrigem, float peso){
            this->noAdjacente = no;
            this->peso = peso;
            this->noOrigem = noOrigem;
            this->proximo = NULL;
        }

        ~Aresta(){};

        int getOrigem(){ return noOrigem; }
        void setOrigem( int _noOrigem){noOrigem = _noOrigem; }

        int getNoAdj(){ return noAdjacente; }
        void setNoAdj(int _noAdjacente){noAdjacente = _noAdjacente;}

        float getPeso(){return peso;}
        void setPeso(float _peso){peso = _peso;}

        Aresta* getProx(){return proximo;}
        void setProx(Aresta* _proximo){proximo = _proximo;}

        string toString(){
            return "Aresta: (" + to_string(noOrigem) + ", " + to_string(noAdjacente) + ") peso: " + to_string(peso);
        }

    private:
        int noOrigem;
        int noAdjacente;
        float peso;
        Aresta *proximo;
};

#endif // ARESTA_H
