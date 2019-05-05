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

    float getPeso();
    int getId();
    int getGrauEntrada();
    int getGrauSaida();
    Aresta *getAresta();
    Aresta *getAresta(int i);
    No* getProx();

    bool removeAresta(int idNo);
    void diminuiGrauEntrada();
    void diminuiGrauSaida();

private:
    int id;
    float peso;
    No *prox;
    Aresta *adj;
    int grauEntrada;
    int grauSaida;
};


#endif //GRAFOLISTA_NO_H
