#include "No.h"

No::No(){
    grauEntrada = 0;
    grauSaida = 0;
}
No::~No(){}

int No::getID()
{
    return id;
}
void No::setID(int _id)
{
    id = _id;
}

float No::getPeso()
{
    return peso;
}
void No::setPeso(float _peso)
{
    peso = _peso;
}

Aresta* No::getAdjacente()
{
    return adjacente;
}
void No::setAdjacente(Aresta *_adjacente)
{
    adjacente = _adjacente;
}

Aresta* No::getUltimaAdjacente()
{
    return ultimaAdjacente;
}
void No::setUltimaAdjacente(Aresta *_ultimaAdjacente)
{
    ultimaAdjacente = _ultimaAdjacente;
}

No* No::getProximo()
{
    return proximo;
}
void No::setProximo(No* _proximo)
{
    proximo = _proximo;
}

int No::getGrauEntrada()
{
    return grauEntrada;
}
void No::setGrauEntrada(int _grauEntrada)
{
    grauEntrada = _grauEntrada;
}

int No::getGrauSaida()
{
    return grauSaida;
}
void No::setGrauSaida(int _grauSaida)
{
    grauSaida = _grauSaida;
}

void No::addGrauEntrada(){
    grauEntrada++;
}
void No::addGrauSaida(){
    grauSaida++;
}

void No::removeGrauEntrada(){
    grauEntrada--;
    if(grauEntrada < 0){
        grauEntrada = 0;
    }
}
void No::removeGrauSaida(){
    grauSaida--;
    if(grauSaida < 0){
        grauSaida = 0;
    }
}