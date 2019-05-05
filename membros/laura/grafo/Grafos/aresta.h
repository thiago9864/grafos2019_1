#ifndef GRAFOLISTA_ARESTA_H
#define GRAFOLISTA_ARESTA_H


class Aresta {

public:

    Aresta(int no);
    Aresta(int no, int peso);
    ~Aresta();

    Aresta *getProx();
    int getNoAdj();
    float getPeso();


    void setProx(Aresta *aresta);

private:

    int noAdj;
    float peso;
    Aresta* prox;

};


#endif //GRAFOLISTA_ARESTA_H
