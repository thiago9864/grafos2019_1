#ifndef GRAFOLISTA_ARESTA_H
#define GRAFOLISTA_ARESTA_H


class Aresta {

public:

    Aresta();
    Aresta(int noOrigem, int noFim);
    Aresta(int noOrigem, int noFim, float peso);
   // ~Aresta();

    Aresta *getProx();
    int getNoAdj();
    float getPeso();

    int getOrigem();

    void setProx(Aresta *aresta);

private:

    int noAdj;
    float peso;
    Aresta* prox;

    int origem; // Outra 'ponta' da aresta (além de 'noAdj').

};


#endif //GRAFOLISTA_ARESTA_H
