#include "Indice.h"

Indice::Indice(int n)
{
    _n = n;
    // aloca o vetor de vetores
    indices = new int[n];
    for(int j = 0; j < n; j++){
        indices[j] = 0;
    }
    tamIndice = 0;
}

Indice::~Indice()
{
    // desaloca os indices
    delete indices;
}


/**
 * Esse metodo insere um id de vertice no indice e retorna a sua posicao
 * parametro: id (id do vertice)
 * encapsulamento: public
 **/
int Indice::insereVerticeNoIndice(int id)
{
    int pos = tamIndice;
    indices[pos] = id;
    tamIndice++;
    return pos;
}

/**
 * Esse metodo retorna a posicao de um indice
 * parametro: id (id a pesquisar)
 * encapsulamento: public
 **/
int Indice::procuraPosicaoNoIndice(int id)
{
    for(int i = 0; i < tamIndice; i++)
    {
        if(indices[i] == id){
            return i;
        }
    }
    return -1;
}

/**
 * Esse metodo retorna o indice de uma posicao
 * parametro: pos (posicao do id no indice)
 * encapsulamento: public
 **/
int Indice::getPos(int pos){
    if(pos >= 0 && pos < tamIndice){
        return indices[pos];
    }
}

/**
 * Esse metodo retorna o numero total de indices
 * encapsulamento: public
 **/
int Indice::getTamIndice(){
    return tamIndice;
}