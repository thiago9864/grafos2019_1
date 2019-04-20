//
// Created by victor on 01/04/19.
//

#ifndef GRAFOLISTA_NO_H
#define GRAFOLISTA_NO_H

#include "Aresta.h"


class No {

public:

    No(int id);
    No(int id, float peso);
    ~No();

    void setProx(No *n);
    bool setAresta(Aresta *aresta);
    void aumentaGrauEntrada();
    void aumentaGrauSaida();

    int getId();
    float getPeso();
    int getGrauEntrada();
    int getGrauSaida();
    No* getProx();
    Aresta *getAresta();
    Aresta *getAresta(int i);

    void removeAresta(int idNo);
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
