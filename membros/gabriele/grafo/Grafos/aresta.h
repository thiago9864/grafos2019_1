#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED


class Aresta{
public:
    Aresta(int id);
    Aresta(int id,float peso);
    ~Aresta();
    void setProx(Aresta *proximo);
    Aresta* getProx();
    float getPeso();
    int getNoId();


private:
    int no_adj;//id do no
    float peso;
    Aresta *prox;
};



#endif // ARESTA_H_INCLUDED
