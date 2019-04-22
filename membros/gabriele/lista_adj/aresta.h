#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

#include "no.h"
class Aresta{
public:
    Aresta();
    ~Aresta();
    void setProx(Aresta *proximo);
    Aresta* getProx();
    void setPeso(int peso);
    int getPeso();
    int getNoAd();
    void setNoAd(int id);

private:
    int no_adj;//id do no
    float peso;
    Aresta *prox;
};


#endif // ARESTA_H_INCLUDED
