//
// Created by victor on 08/05/19.
//

#include "SteinerTree.h"

SteinerTree::SteinerTree(Grafo *g, int *terminais, int tam) {
    this->grafoOrigem = g;
    this->arvore = new Grafo(false,true,false); // Grafo não direcional ponderado nas arestas

    this->terminais = terminais;
    this->lenTerminais = tam;

    this->atendidos = new bool[tam];
    for (int i = 0; i < tam; i++)
        this->atendidos[i] = false;

//    this->caminhos = new CaminhoMinimo(this->grafoOrigem);
    this->caminhos = new CaminhoMinimoDijkstra(this->grafoOrigem);

    if (tam > 0)
        this->geraSteinerTree();

}

/// Retorna o nó mais próximo dentre os terminais.
//int SteinerTree::menorCaminho(int origem, int *comparar, int tam) {
//
//    int noMaisProximo = comparar[0];
//    int menorDist = this->caminhos->getDistancia(origem,comparar[0]);
//    int dist;
//
//    if (origem == comparar[0]) {
//        noMaisProximo = comparar[1];
//        menorDist = this->caminhos->getDistancia(origem,comparar[1]);
//    }
//
//    // Comparando com terminais
//    for (int i = 1; i < tam; i++) {
//        if (comparar[i] != origem) {
//            dist = this->caminhos->getDistancia(origem, comparar[i]);
//
//            if (dist < menorDist) {
//                noMaisProximo = comparar[i];
//                menorDist = dist;
//            }
//        }
//    }
//
//    return noMaisProximo;
//
//}

int SteinerTree::menorCaminho(int origem, int *comparar, int tam) {

    int noMaisProximo = comparar[0];
    this->caminhos->calcular(origem, noMaisProximo);
    float menorDist = this->caminhos->getDistanciaMinima();
    float dist;

    if (origem == comparar[0]) {
        noMaisProximo = comparar[1];
        this->caminhos->calcular(origem, noMaisProximo);
        menorDist = this->caminhos->getDistanciaMinima();
    }

    // Comparando com terminais
    for (int i = 1; i < tam; i++) {
        if (comparar[i] != origem) {
            this->caminhos->calcular(origem, comparar[i]);

            dist = this->caminhos->getDistanciaMinima();

            if (dist < menorDist) {
                noMaisProximo = comparar[i];
                menorDist = dist;
            }
        }
    }

    return noMaisProximo;

}

bool SteinerTree::todosAtendidos() {
    for (int i=  0; i < this->lenTerminais; i++)
        if (!this->atendidos[i])
            return false;

    return true;
}

int SteinerTree::primeiroNaoAtendido() {
    for (int i=  0; i < this->lenTerminais; i++)
        if (!this->atendidos[i])
            return i;

    return -1;
}

int SteinerTree::getNaoAtendidos(int* naoAtendidos, int pular) {
    int c = 0;

    for (int i = 0; i < this->lenTerminais; i++) {
//        if (!this->atendidos[i]) {
            if (i != pular) {
            naoAtendidos[c] = this->terminais[i];
            c++;
        }
    }

    if (c < this->lenTerminais) {
        for (int i = c; i < this->lenTerminais; i++)
            naoAtendidos[i] = -1;
    }

    return c;

}

//void SteinerTree::setCaminho(int origem, int destino) {
//
//    Aresta* path = this->caminhos->getCaminho(origem,destino);
//
//    // Adicionando vertices de origem e destino
//    this->arvore->setNo(origem);
//    this->arvore->setNo(destino);
//
//    for (Aresta* a = path; a != nullptr; a = a->getProx()) {
//
//        if (this->arvore->getNo(a->getNoAdj()) == nullptr) { // Se o vertice de steiner não está a arvore irei adiciona-lo
//            this->arvore->setNo(a->getNoAdj());
//        }
//
//        this->arvore->setAresta(a->getNoOrigem(), a->getNoAdj(), a->getPeso()); // Adicionando aresta a arvore
//
//    }
//
//}

void SteinerTree::setCaminho(int origem, int destino) {

    this->caminhos->calcular(origem, destino);
    int* path = this->caminhos->getCaminhoMinimo();
    int tamPath = this->caminhos->getTamCaminho();

    // Adicionando vertices de origem e destino
    this->arvore->setNo(origem);
    this->arvore->setNo(destino);

//    for (int i = 1; i < tamPath; i++) {
//
//        if (this->arvore->getNo(a->getNoAdj()) == nullptr) { // Se o vertice de steiner não está a arvore irei adiciona-lo
//            this->arvore->setNo(a->getNoAdj());
//        }
//
//        this->arvore->setAresta(a->getNoOrigem(), a->getNoAdj(), a->getPeso()); // Adicionando aresta a arvore
//
//    }

}

void SteinerTree::geraSteinerTree() {

    int pos;
    int naoAtendidos[this->lenTerminais];
    int tam;
    int noMaisProximo;

    // Enquanto todos os terminais ainda não forem atendidos
    while(!this->todosAtendidos()) {

        pos = this->primeiroNaoAtendido();          // Posição do primeiro ainda não atendido

        this->atendidos[pos] = true;

        tam = this->getNaoAtendidos(naoAtendidos, pos);  // Atualiza vetor e tamanho dos terminais ainda não atendidos

        noMaisProximo = this->menorCaminho(this->terminais[pos], this->terminais, lenTerminais); // Encontra o vertice de menor caminho

        if (noMaisProximo != -1)
            this->setCaminho(this->terminais[pos], noMaisProximo);  // Adiciona o caminho a arvore

    }

}

Grafo* SteinerTree::getSteinerTree() {
    return this->arvore;
}