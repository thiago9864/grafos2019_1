#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED
#include"aresta.h"

class No{
public:
    No(int id);
    No(int id, float peso);
    ~No();

    int getGrauEntrada();
    int getGrauSaida();
    Aresta* getAresta();
    int getId();
    float getPeso();
    No* getProx();
    Aresta *getAresta(int i);

    void setPeso(float peso);
    void setId(int num);
    bool setAresta(Aresta *aresta);

    void setProx(No *n);
    void aumentaGrauEntrada();
    void aumentaGrauSaida();

    bool removeAresta(int idNo);
    void diminuiGrauEntrada();
    void diminuiGrauSaida();

    void setMarca();
    bool getMarca();

private:
    bool marca;
    Aresta *aresta_adj;
    No *prox;
    int id;
    float peso;
    int grauEntrada;
    int grauSaida;

};


#endif // NO_H_INCLUDED
