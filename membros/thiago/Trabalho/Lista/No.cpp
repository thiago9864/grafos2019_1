/**
    Universidade Federal de Juiz de Fora
    No.cpp
    Propósito: Classe que representa um vertice.

    @author Thiago Almeida
    @version 1.0 30/03/19 
*/

#include "No.h"

No::No(){
    grauEntrada = 0;
    grauSaida = 0;
}
No::~No(){}

int No::getId()
{
    return id;
}
void No::setId(int _id)
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

Aresta* No::getAresta()
{
    return adjacente;
}
void No::setAresta(Aresta *_adjacente)
{
    adjacente = _adjacente;
}

Aresta* No::getUltimaAresta()
{
    return ultimaAdjacente;
}
void No::setUltimaAresta(Aresta *_ultimaAdjacente)
{
    ultimaAdjacente = _ultimaAdjacente;
}

No* No::getProx()
{
    return proximo;
}
void No::setProx(No* _proximo)
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