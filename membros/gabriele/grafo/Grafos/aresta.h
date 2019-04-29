#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED


class Aresta{
public:
    Aresta(int id,int origemId);
    Aresta(int id,int origemId);
    Aresta(int id,int origemId,float peso);
    ~Aresta();
    void setProx(Aresta *proximo);
    Aresta* getProx();
    float getPeso();
    int getNoId();
    int getOrigemId();


private:
    int origemId;//id do no de origem que possui a aresta
    int no_adj;//id do no que está ligado ao no de origem
    float peso;
    Aresta *prox;
};



#endif // ARESTA_H_INCLUDED
