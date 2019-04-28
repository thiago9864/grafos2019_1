/**
    Universidade Federal de Juiz de Fora
    ListaArestas.cpp
    Propósito: Encapsular uma lista de arestas.

    @author Thiago Almeida
    @version 1.0 27/04/19 
*/
#include "ListaArestas.h"

ListaArestas::ListaArestas(){
    lista = NULL;
    ultimoLista = NULL;
    tamanho = 0;
}
ListaArestas::~ListaArestas(){

}
void ListaArestas::addAresta(Aresta* aresta){

    //faz uma copia da aresta
    Aresta *a = new Aresta();
    a->setNoOrigem(aresta->getNoOrigem());
    a->setNoAdj(aresta->getNoAdj());
    a->setPeso(aresta->getPeso());
    a->setProx(NULL);

    //adiciona aresta
    if(lista == NULL)
    {
        //adiciona no começo a aresta criada
        lista = a; 
    }
    else
    {
        //adiciona na ultima posicao a aresta criada
        ultimoLista->setProx(a);
    }
    
    tamanho++;
    ultimoLista = a;
}
void ListaArestas::removeAresta(Aresta* aresta){
    Aresta *a = lista;
    Aresta *ant = a;

    while(a != NULL)
    {
        if(a->getNoAdj() == aresta->getNoAdj() && a->getNoOrigem() == aresta->getNoOrigem())
        {
            if(a == ant)
            {
                //primeira aresta da lista
                lista = a->getProx();
                delete a;
            }
            else if(a->getProx() == NULL)
            {
                //ultima aresta
                ultimoLista = ant;
                ant->setProx(NULL);
                delete a;
            }
            else
            {
                //aresta do meio
                ant->setProx(a->getProx());
                delete a;
            }

            tamanho--;
            break;
        }
        ant = a;
        a = a->getProx();
    }
}

Aresta* ListaArestas::getAresta(int idOrigem, int idDestino){
    Aresta *a = lista;

    while(a != NULL)
    {
        if(a->getNoAdj() == idDestino && a->getNoOrigem() == idOrigem)
        {
            return a;
        }
        a = a->getProx();
    }

    return NULL;
}
int ListaArestas::getTamanho(){
    return tamanho;
}
Aresta* ListaArestas::getArrayArestas(){
    Aresta *arrArestas = new Aresta[tamanho];
    Aresta *a = lista;
    int cont=0;
    while(a != NULL)
    {
        arrArestas[cont++] = *a;
        a = a->getProx();
    }
    return arrArestas;
}