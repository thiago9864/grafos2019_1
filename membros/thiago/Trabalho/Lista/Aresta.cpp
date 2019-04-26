#include "Aresta.h"

Aresta::Aresta(){}; 
Aresta::~Aresta(){};

int Aresta::getNoAdj()
{
    return noAdjacente;
}
void Aresta::setNoAdj(int _noAdjacente)
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

Aresta* Aresta::getProx()
{
    return proximo;
}
void Aresta::setProx(Aresta* _proximo)
{
    proximo = _proximo;
}