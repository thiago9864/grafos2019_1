//
// Created by victor on 01/04/19.
//

#ifndef GRAFOLISTA_NO_H
#define GRAFOLISTA_NO_H

#include "Aresta.h"


class No {

public:

    No();
    No(int id);
    No(int id, float peso);
    ~No();

    void setProx(No *n);
    bool setAresta(Aresta *aresta);
    void aumentaGrauEntrada();
    void aumentaGrauSaida();

    int getId();
    void setId(int id);
    float getPeso();
    int getGrauEntrada();
    int getGrauSaida();
    void setGrauEntrada(int grauEntrada);
    void setGrauSaida(int grauSaida);
    No* getProx();
    Aresta *getAresta();
    Aresta *getAresta(int i);

    bool removeAresta(int idNo);
    void diminuiGrauEntrada();
    void diminuiGrauSaida();

private:
    int id;
    float peso;
    Aresta *adj;
    No *prox;
    int grauEntrada;
    int grauSaida;
};


#endif //GRAFOLISTA_NO_H
