/**
    Universidade Federal de Juiz de Fora
    No.h
    Propósito: Classe que representa um vertice.

    @author Thiago Almeida
    @version 1.0 30/03/19 
*/

#ifndef NO_H
#define NO_H
#include <iostream>
#include "Aresta.h"

class No 
{
    public:
    No(){
        this->grauEntrada = 0;
        this->grauSaida = 0;
        this->proximo = NULL;
        this->adjacente = NULL;
        this->ultimaAdjacente = NULL;
        this->marca = false;
        this->marcaTerminal = false;
    }
    No(int id, float peso)
    {
        this->id = id;
        this->peso = peso;
        this->grauSaida = 0;
        this->grauEntrada = 0;
        this->proximo = NULL;
        this->adjacente = NULL;
        this->ultimaAdjacente = NULL;
        this->marca = false;
        this->marcaTerminal = false;
    }
    ~No(){}

    int getId(){ return id; }
    void setId(int id){ this->id = id; }

    float getPeso(){ return peso; }
    void setPeso(float peso){ this->peso = peso; }

    Aresta* getAresta(){ return adjacente; }
    void setAresta(Aresta *adjacente){ this->adjacente = adjacente; }

    Aresta* getUltimaAresta(){ return ultimaAdjacente; }
    void setUltimaAresta(Aresta *ultimaAdjacente){ this->ultimaAdjacente = ultimaAdjacente; }

    No* getProx(){ return proximo;}
    void setProx(No* proximo){ this->proximo = proximo; }

    int getGrauEntrada(){    return grauEntrada; }
    void setGrauEntrada(int grauEntrada){ this->grauEntrada = grauEntrada; }

    int getGrauSaida(){ return grauSaida; }
    void setGrauSaida(int grauSaida){ this->grauSaida = grauSaida; }

    void addGrauEntrada(){ grauEntrada++; }
    void addGrauSaida(){ grauSaida++; }

    void removeGrauEntrada(){
        grauEntrada--;
        if(grauEntrada < 0){
            grauEntrada = 0;
        }
    }
    void removeGrauSaida(){
        grauSaida--;
        if(grauSaida < 0){
            grauSaida = 0;
        }
    }

    //marcadores
    bool getMarca(){ return marca;}
    void setMarca() {marca=true;}
    void desmarca() {marca=false;}

    bool getMarcaTerminal(){ return marcaTerminal;}
    void setMarcaTerminak() {marcaTerminal=true;}

    private:
        int id;
        float peso;
        Aresta *adjacente;
        Aresta *ultimaAdjacente;
        No *proximo;
        int grauEntrada;
        int grauSaida;
        bool marca;
        bool marcaTerminal;
};

#endif // NO_H
