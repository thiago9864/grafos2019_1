//
// Created by victor on 23/04/19.
//

#include "OrdenacaoTopologica.h"
/*
int* OrdenacaoTopologica::ordenacao(Grafo* g) {

    this->g = g;
    int ordem = this->g->getOrdem();
    this->semEntrada = new No*[ordem];
    this->ordenados = new int[ordem];
    this->visitados = new int[ordem];
    this->lenSemEntrada = 0;

    if (!g->getDirecional()) return this->ordenados;

    // Inicializando vetores
    for (int i = 0; i < ordem; i++) {
        this->ordenados[i] = -1;
        this->visitados[i] = -1;
        this->semEntrada[i] = nullptr;
    }

    // Encontrando nós sem arestas de entrada
    for (No* n = this->g->getNo(); n != nullptr; n = n->getProx()) {
        if (n->getGrauEntrada() == 0) {
            this->semEntrada[lenSemEntrada] = n;
            this->lenSemEntrada++;
        }
    }

    if (lenSemEntrada == 0) {
        cout << "Grafo contem um ciclo" << endl;
        return ordenados;
    }

    for (int i = 0; i < lenSemEntrada; i++) {
        visita(semEntrada[i], ordem);
    }

    this->ordenados = this->inverteVetor(this->ordenados, ordem);

    return this->ordenados;

}

void OrdenacaoTopologica::visita(No* n, int ordem) {

    int nId = n->getId();
    int lastPosVis = find(this->visitados, -1, ordem);
    int lastPosOrd;

    if (!this->find(this->visitados, nId, ordem)) {     // Verificando se o n já foi visitado
        this->visitados[lastPosVis] = nId;              // Marcando n como visitado

        // Percorrendo todos os nós m que n tem aresta
        for (Aresta* a = n->getAresta(); a != nullptr; a = a->getProx()) {
            No* m = this->g->getNo(a->getNoAdj());
            this->visita(m, ordem);
        }

        lastPosOrd = find(this->ordenados, -1, ordem);
        this->ordenados[lastPosOrd] = n->getId();       // Adicionando n aos ordenados

    }

}

int OrdenacaoTopologica::find(int *vetor, int valor, int tam) {
    for (int i = 0; i < tam; i++) {
        if (vetor[i] == valor) return i;
    }
    return 0;
}

int* OrdenacaoTopologica::inverteVetor(int *vetor, int tam) {
    int* invertido = new int[tam];
    int i = tam-1;
    int j = 0;

    for (i,j; j < tam; j++, i--) {
        invertido[j] = vetor[i];
    }

    return invertido;

}

void OrdenacaoTopologica::imprime() {
    int ordem = this->g->getOrdem();
    for (int i = 0; i < ordem-1; i++) {
        cout << this->ordenados[i] << ", ";
    }
    cout << this->ordenados[ordem-1] << endl;
}
*/