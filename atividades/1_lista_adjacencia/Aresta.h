//
// Created by victor on 01/04/19.
//

#ifndef GRAFOLISTA_ARESTA_H
#define GRAFOLISTA_ARESTA_H


class Aresta {

public:

    Aresta(int no);
    Aresta(int no, int peso);
    ~Aresta();

    int getNoAdj();
    float getPeso();
    Aresta *getProx();

    void setProx(Aresta *aresta);

private:

    int noAdj;
    float peso;
    Aresta* prox;

};


#endif //GRAFOLISTA_ARESTA_H
