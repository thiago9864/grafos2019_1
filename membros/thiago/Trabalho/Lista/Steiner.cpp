/**
    Universidade Federal de Juiz de Fora
    Steiner.cpp
    Propósito: Resolve o problema de Steiner.

    @author Thiago Almeida
    @version 1.0 09/05/19
*/

#include "Steiner.h"

Steiner::Steiner(Grafo *grafo){
    this->grafo = grafo;
    this->caminhoMinimo = new CaminhoMinimoDijkstra(grafo);
};
Steiner::~Steiner(){
    //destrutor
};

float Steiner::obtemMenorDistancia(int origem, int destino)
{
    caminhoMinimo->calcular(origem, destino);
    return caminhoMinimo->getDistanciaMinima();
}

float Steiner::calcular()
{
    int num_terminais = grafo->getNumTerminais();
    int *terminais = grafo->getTerminais();
    int *arvore = new int[grafo->getOrdem()]; 
    int tam_arvore = 0;
    float dist_minima = 0;

    cout << "num_terminais: " << num_terminais << endl;

    for(int t=0; t < (num_terminais-2); t++)
    {
        int idTerminal1 = terminais[t];
        int idTerminal2 = terminais[t+1];

        cout << "checar terminais " << idTerminal1 << " e " << idTerminal2 << endl;

        caminhoMinimo->calcular(idTerminal1, idTerminal2);
        dist_minima += caminhoMinimo->getDistanciaMinima();
        int *caminho = caminhoMinimo->getCaminhoMinimo();

        for(int i=0; i<caminhoMinimo->getTamanhoCaminhoMinimo(); i++){
            if(tam_arvore == 0 || i>0){
                arvore[tam_arvore] = caminho[i];
                tam_arvore++;
            }
        }
    }
    /*
    cout << "arvore obtida: ";

    for(int i=0; i < tam_arvore; i++)
    {
        if(i>0){
            cout << " -> ";
        }
        cout << arvore[i];
    }
    
    cout << endl;
    */
    cout << "arvore obtida com a distancia minima de: " << dist_minima << endl;

    return dist_minima;
}