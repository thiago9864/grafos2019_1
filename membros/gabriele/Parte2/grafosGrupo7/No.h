/**
    Universidade Federal de Juiz de Fora
    Aresta.h
    Propósito: Representa um nó no grafo.

    @author Victor Aquiles
    @version 1.0 01/04/19
*/


#ifndef NO_H
#define NO_H

#include "Aresta.h"


class No {

    public:

        No(){
            this->marca = false;
            this->marcaTerminal=false;
        };

        No(int id, float peso) {
            this->id = id;
            this->peso = peso;
            this->grauSaida = 0;
            this->grauEntrada = 0;
            this->prox = nullptr;
            this->adj = nullptr;
            this->marca = false;
            this->marcaTerminal=false;
        }

        No(int id) {
            this->id = id;
            this->peso = -1;
            this->grauSaida = 0;
            this->grauEntrada = 0;
            this->prox = nullptr;
            this->adj = nullptr;
            this->marca = false;
            this->marcaTerminal=false;
        }

        ~No() {

            // Deletando todos os nós
            No* ant = this;
            No *n;

            for (No *n = ant->getProx(); n != nullptr; n = n->getProx()) {
                delete ant->adj;
                delete ant;
            }

        }

    private:
        int id;
        float peso;
        Aresta *adj;
        No *prox;
        int grauEntrada;
        int grauSaida;
        bool marca;
        bool marcaTerminal;

    public:

        // *** Getters ***

        bool get_marcaTerminal() {return marcaTerminal;}
        void set_marcaTerminal(){marcaTerminal=true;}

        int getId() { return this->id; }
        void setId(int id){ this->id = id; }

        No* getProx() { return this->prox; }
        float getPeso() { return this->peso; }

        bool getMarca(){ return marca;}
        void setMarca() {marca=true;}
        void desmarca() {marca=false;}

        void aumentaGrauEntrada() { this->grauEntrada++; }
        void aumentaGrauSaida() { this->grauSaida++; }

        void diminuiGrauEntrada() {
            if (this->grauEntrada > 0) {
                this->grauEntrada--;
            }
        }
        void diminuiGrauSaida() {
            if (this->grauSaida > 0) {
                this->grauSaida--;
            }
        }

        int getGrauEntrada() { return this->grauEntrada; }
        int getGrauSaida() { return this->grauSaida; }

        void setGrauEntrada(int grauEntrada)
        {
            if(grauEntrada >= 0){
                this->grauEntrada = grauEntrada;
            }
        }
        void setGrauSaida(int grauSaida)
        {
            if(grauSaida >= 0){
                this->grauSaida = grauSaida;
            }
        }

        Aresta *getAresta() { return this->adj; }
        Aresta *getAresta(int i) {
            Aresta *a = this->adj;
            int c = 0;

            for (; a != nullptr || c < i; a = a->getProx(), c++);

            if (c == i) {
                return a;
            } else {
                return nullptr;
            }
        }

        // *** Setters ***

        void setProx(No *n) { this->prox = n; }

        bool setAresta(Aresta *aresta) {
            Aresta *a = this->adj;

            // Inicialzando arestas
            if (a == nullptr) {
                this->adj = aresta;
                this->aumentaGrauSaida();

                return true;
            }

            // Encontrando a ultima aresta inserida e certificando que não existe essa aresta
            for (; a->getProx() != nullptr && a->getNoAdj() != aresta->getNoAdj(); a = a->getProx());

            // Inserindo aresta ou imprimindo erro se já existe aresta
            if (a->getNoAdj() != aresta->getNoAdj()) {
                a->setProx(aresta);
            } else {
                std::cout << "Aresta ja inserida: " << this->getId() << " ---> " << aresta->getNoAdj() << std::endl;
                return false;
            }

            this->aumentaGrauSaida();

            return true;
        }


        // *** REMOÇÂO ***

        bool removeAresta(int idNo) {

            Aresta *aresta = this->getAresta();
            Aresta *ant = this->getAresta();
            bool encontrou = false;

            // Percorrendo lista de arestas a fim de encontrar aresta desejada
            for (; aresta != nullptr; aresta = aresta->getProx()) {
                if (aresta->getNoAdj() == idNo) {
                    encontrou = true;
                    break;
                }
                ant = aresta;
            }

            // Se o nó foi encontrado é retirado o nó e colocado os seguintes para o nó anterior
            if (encontrou) {
                Aresta *prox = aresta->getProx();

                if (ant == aresta)
                    this->adj = prox;     // Se a aresta for a primeira reiniciamos a sequencia a partir do próximo
                else
                    ant->setProx(prox);   // Senão colocamos o seguinte no anterior

                aresta->setProx(nullptr); // Evita apagar o nó subsequente
                delete aresta;

                this->diminuiGrauSaida();
            }

            return encontrou;

        }
};

#endif //NO_H
