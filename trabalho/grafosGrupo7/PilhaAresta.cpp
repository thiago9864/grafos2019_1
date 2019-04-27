/**
    Universidade Federal de Juiz de Fora
    PilhaAresta.cpp
    Propósito: Classe que representa uma pilha de arestas.

    @author Thiago Almeida
    @version 1.0 27/04/19 
*/

#include <iostream>
#include <cstdlib>
#include "PilhaAresta.h"


using namespace std;

PilhaAresta::PilhaAresta()
{
    topo = NULL;
    tamanho = 0;
}

PilhaAresta::~PilhaAresta()
{
    NoPilhaAresta *p = topo;
    while(p != NULL)
    {
        NoPilhaAresta *t = p->getProx();
        delete p;
        p = t;
    }
}

void PilhaAresta::empilha(Aresta *c)
{
    NoPilhaAresta *novo = new NoPilhaAresta();
    novo->setInfo(c);
    novo->setProx(topo);
    topo = novo;
    tamanho++;
}

Aresta* PilhaAresta::desempilha()
{
    if(!isVazia())
    {
        NoPilhaAresta *p = topo->getProx();
        Aresta *c = topo->getInfo();
        delete topo;
        topo = p;
        tamanho--;
        return c;
    }
    else
    {
        cerr << "Pilha vazia!" << endl;
        //exit(1);
        return NULL;
    }
}

Aresta* PilhaAresta::getTopo()
{
    if(!isVazia())
        return topo->getInfo();
    else
    {
        cerr << "Pilha vazia!" << endl;
        exit(1);
    }
}

bool PilhaAresta::isVazia()
{
    return (topo == NULL);
}

int PilhaAresta::getTamanho()
{
    return tamanho;
}

void PilhaAresta::imprime()
{
    NoPilhaAresta *p = topo;

    cout << "PILHA: ";
    if(topo == NULL) cout << "Vazia!" << endl;
    while(p != NULL)
    {
        cout << p->getInfo() << " ";
        p = p->getProx();
    }
    cout << endl;
}
