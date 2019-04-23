#include "Aresta.h"

Aresta::Aresta(){}; 
Aresta::~Aresta(){};

int Aresta::getNoAdjacente()
{
    return noAdjacente;
}
void Aresta::setNoAdjacente(int _noAdjacente)
{
    noAdjacente = _noAdjacente;
}

float Aresta::getPeso()
{
    return peso;
}
void Aresta::setPeso(float _peso)
{
    peso = _peso;
}

Aresta* Aresta::getProximo()
{
    return proximo;
}
void Aresta::setProximo(Aresta* _proximo)
{
    proximo = _proximo;
}