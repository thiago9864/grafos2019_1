/**
    Universidade Federal de Juiz de Fora
    Aresta.cpp
    Propósito: Representar arestas de um grafo.

    @author Thiago Almeida
    @version 1.0 30/03/19 
*/

#include "Aresta.h"

Aresta::Aresta(){}; 

Aresta::Aresta(int no, int noOrigem, float peso) 
{
    this->noAdjacente = no;
    this->peso = peso;
    this->noOrigem = noOrigem;
    this->proximo = NULL;
}

Aresta::~Aresta(){};
 
/**
 * retorna o vertice de origem
 * @return Vertice
 */
int Aresta::getNoOrigem()
{
    return noOrigem;
}

/**
 * define o vertice de origem
 */
void Aresta::setNoOrigem(int _noOrigem)
{
    noOrigem = _noOrigem;
}

/**
 * retorna o vertice de destino
 * @return Vertice
 */
int Aresta::getNoAdj()
{
    return noAdjacente;
}

/**
 * define o vertice de destino
 */
void Aresta::setNoAdj(int _noAdjacente)
{
    noAdjacente = _noAdjacente;
}

/**
 * retorna o peso da aresta
 * @return Peso
 */
float Aresta::getPeso()
{
    return peso;
}

/**
 * define o peso da aresta
 */
void Aresta::setPeso(float _peso)
{
    peso = _peso;
}

/**
 * retorna o ponteiro para a proxima aresta
 * @return Ponteiro
 */
Aresta* Aresta::getProx()
{
    return proximo;
}

/**
 * define o ponteiro pra proxima aresta
 */
void Aresta::setProx(Aresta* _proximo)
{
    proximo = _proximo;
}