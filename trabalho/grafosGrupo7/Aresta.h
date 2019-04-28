//
// Created by victor on 01/04/19.
//

#ifndef GRAFOLISTA_ARESTA_H
#define GRAFOLISTA_ARESTA_H


class Aresta {

public:

    Aresta();//thiago
    Aresta(int no);
    Aresta(int no, float peso);
    Aresta(int no, int noOrigem, float peso);//thiago
    ~Aresta();

    int getNoAdj();
    float getPeso();
    Aresta *getProx();
    int getNoOrigem();//thiago

    void setProx(Aresta *aresta);

private:

    int noAdj;
    float peso;
    Aresta* prox;
    int noOrigem;//thiago

};


#endif //GRAFOLISTA_ARESTA_H
