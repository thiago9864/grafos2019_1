//
// Created by victor on 08/05/19.
//

#include "SteinerTree.h"

/**
 * Inicializa objeto de construção de árvores de Steiner.
 *
 * @param g Grafo simples, não direcionado e conexo que servirá de base.
 * @param terminais Vértices base para construção da árvore.
 * @param tam Quantidade de vértices terminais.
 */
SteinerTree::SteinerTree(Grafo *g, int *terminais, int tam) {

    this->grafoOrigem = g;
    this->arvore = new Grafo(false,true,false); // Grafo não direcional ponderado nas arestas

    this->terminais = terminais;    // Inicializando Terminais
    this->lenTerminais = tam;

    this->atendidos = new bool[tam];    // Inicializando vetor de nós terminais já atendidos
    for (int i = 0; i < tam; i++)
        this->atendidos[i] = false;

    this->caminhos = new CaminhoMinimo(this->grafoOrigem);  // Objeto com dados dos caminhos de todos os vertices
//    this->caminhos = new CaminhoMinimoDijkstra(this->grafoOrigem);

    if (tam > 0)
        this->geraSteinerTree();    // Gerando árvore de Steiner

}

/**
 * Encontra o vértice terminal mais próximo do passado como parâmetro.
 *
 * @param origem Vértice a ser comparado com os terminais.
 * @return Vértice mais próximo do passado como parâmetro
 */
int SteinerTree::menorCaminho(int origem) {

    int noMaisProximo = -1;
    int menorDist = 999999999;
    int dist;

    // Comparando com terminais
    for (int i = 0; i < this->lenTerminais; i++) {
        if (this->terminais[i] != origem) {         // Evita que o próprio nó seja comparado

            dist = this->caminhos->getDistancia(origem, this->terminais[i]);    // Obtendo distancia entre vertices

            if (dist < menorDist) {
                noMaisProximo = this->terminais[i];
                menorDist = dist;
            }
        }
    }

    return noMaisProximo;

}

/// Indica se todos os terminais foram ou não atendidos.
bool SteinerTree::todosAtendidos() {
    for (int i=  0; i < this->lenTerminais; i++)
        if (!this->atendidos[i])
            return false;

    return true;
}

/// Retorna a posição do primeiro nó terminal que ainda não foi atendido.
int SteinerTree::primeiroNaoAtendido() {
    for (int i=  0; i < this->lenTerminais; i++)
        if (!this->atendidos[i])
            return i;

    return -1;
}

/**
 * Insere caminho mais curto entre dois vertices na árvore de Steiner.
 *
 * @param origem Vértice de origem.
 * @param destino Vértice de destino.
 */
void SteinerTree::setCaminho(int origem, int destino) {

    Aresta* path = this->caminhos->getCaminho(origem,destino);      // Obtem caminho mais curto entre vertices

    // Adicionando vertices de origem e destino a arvore
    this->arvore->setNo(origem);
    this->arvore->setNo(destino);

    // Percorrendo arestas do caminho
    for (Aresta* a = path; a != nullptr; a = a->getProx()) {

        if (this->arvore->getNo(a->getNoAdj()) == nullptr) { // Se o vertice de steiner não está a arvore irei adiciona-lo
            this->arvore->setNo(a->getNoAdj());
        }

        this->arvore->setAresta(a->getNoOrigem(), a->getNoAdj(), a->getPeso()); // Adicionando aresta a arvore

    }

}

/// Gera a árvore de Steiner seguindo um algoritmo guloso.
void SteinerTree::geraSteinerTree() {

    int pos;
    int noMaisProximo;

    // Enquanto todos os terminais ainda não forem atendidos
    while(!this->todosAtendidos()) {

        pos = this->primeiroNaoAtendido();          // Posição do primeiro ainda não atendido

        noMaisProximo = this->menorCaminho(this->terminais[pos]);//, this->terminais, lenTerminais); // Encontra o vertice de menor caminho

        if (noMaisProximo != -1) {

            this->atendidos[pos] = true;    // Vertice já foi atendido

            this->setCaminho(this->terminais[pos], noMaisProximo);  // Adiciona o caminho à árvore

            // Marcando nó mais próximo como atendido também
            for (int i = 0; i < this->lenTerminais; i++) {
                if (this->terminais[i] == noMaisProximo) {
                    this->atendidos[i] = true;
                    break;
                }
            }

        }

    }

}


/// Retorna Árvore de Steiner.
Grafo* SteinerTree::getSteinerTree() {
    return this->arvore;
}