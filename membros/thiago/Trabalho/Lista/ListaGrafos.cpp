/**
    Universidade Federal de Juiz de Fora
    ListaGrafos.cpp
    Propósito: Encapsular uma lista de grafos.

    @author Thiago Almeida
    @version 1.0 27/04/19 
*/

#include "ListaGrafos.h"

ListaGrafos::ListaGrafos(int tam){
    tamanho = tam;
    lista = new Grafo[tamanho];
    max = 0;
}
ListaGrafos::~ListaGrafos(){

}
void ListaGrafos::addGrafo(Grafo grafo){

    //adiciona Grafo
    lista[max++] = grafo;
}

int ListaGrafos::getTamanho(){
    return tamanho;
}
Grafo* ListaGrafos::getGrafos(){
    return lista;
}