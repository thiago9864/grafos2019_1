#include "Indice.h"

Indice::Indice(int n)
{
    _n = n;
    // aloca o vetor de vetores
    indices = new int*[n];
    for(int j = 0; j < n; j++){
        int *aux = new int[2];
        aux[0] = 0;
        aux[1] = 0;
        indices[j] = aux;
    }
    tamIndice = 0;
}

Indice::~Indice()
{
    // desaloca os indices
    delete indices;
}


/**
 * Esse metodo insere ou atualiza um id e status e retorna a posicao no indice
 * parametro: id (id do vertice)
 * parametro: status (status do vertice)
 * encapsulamento: public
 **/
int Indice::insereOuAtualizaVertice(int id, int status)
{
    int i = procuraPosicaoNoIndice(id);

    if(i != -1)
    {
        //atualiza status
        //cout << "atualiza indice" << endl;
        indices[i][1] = status;
    } else{
        //cout << "cria indice " << (tamIndice+1) << " de " << _n << endl;
        i = tamIndice;
        indices[i][0] = id;
        indices[i][1] = status;
        tamIndice++;
    }

    return i;
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
        if(indices[i][0] == id){
            return i;
        }
    }
    return -1;
}

/**
 * Esse metodo retorna o status de um vertice
 * parametro: pos (posicao do id no indice)
 * encapsulamento: public
 * retorno: int (numero se encontrar, NULL se não)
 **/
int Indice::getStatus(int id){
    for(int i = 0; i < tamIndice; i++)
    {
        if(indices[i][0] == id){
            return indices[i][1];
        }
    }
    return 0;
}

/**
 * Esse metodo retorna o numero total de indices
 * encapsulamento: public
 * retorno: int (numero)
 **/
int Indice::getTamIndice(){
    return tamIndice;
}


void Indice::imprimeIndice()
{
    cout << "----- Indice ------" << endl;
    for(int i = 0; i < tamIndice; i++)
    {
        cout << "indice " << i << ", (" << indices[i][0] << ", " << indices[i][1] << ")" << endl;
    }
}
