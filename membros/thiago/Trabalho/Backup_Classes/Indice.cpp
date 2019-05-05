/**
    Universidade Federal de Juiz de Fora
    Indice.cpp
    Propósito: Armazena o indice da busca por profundidade.

    @author Thiago Almeida
    @version 1.0 22/04/19 
*/

#include "Indice.h"

Indice::Indice(int n)
{
    _n = n;
    // aloca o vetor de vetores
    indices = new int*[n];
    for(int j = 0; j < n; j++){
        int *aux = new int[3];
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
 * Insere ou atualiza um id, status e marcador
 * @param id Id do vertice
 * @param status Situação do vértice na busca (0: vazio, 1:visitando, 2: completo)
 * @param marcador Marcador usado pra identificar componentes conexas
 * @return Posicao no indice.
 */
int Indice::insereOuAtualizaVertice(int id, int status, int marcador)
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
 * Dado um id, procura a posição dele no indice
 * @param id Id do vertice
 * @return Posicao no indice.
 */
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
 * Obtem o status de um vértice
 * @param id Id do vértice
 * @return Status desse vértice.
 */
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
 * Obtem o marcador de um vértice
 * @param id Id do vértice
 * @return Marcador desse vértice.
 */
int Indice::getMarcador(int id){
    for(int i = 0; i < tamIndice; i++)
    {
        if(indices[i][0] == id){
            return indices[i][2];
        }
    }
    return 0;
}

/**
 * Esse metodo retorna o numero total de indices
 * @return tamanho do indice
 **/
int Indice::getTamIndice(){
    return tamIndice;
}

/**
 * Imprime o indice de maneira simples
 **/
void Indice::imprimeIndice()
{
    cout << "----- Indice ------" << endl;
    for(int i = 0; i < tamIndice; i++)
    {
        cout << "indice " << i << ", (" << indices[i][0] << ", " << indices[i][1] << ")" << endl;
    }
}
