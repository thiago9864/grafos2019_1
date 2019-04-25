#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>

class Aresta 
{
    public:
        Aresta(); 
        ~Aresta();

        int getNoAdjacente();
        void setNoAdjacente(int _noAdjacente);

        float getPeso();
        void setPeso(float _peso);

        Aresta* getProximo();
        void setProximo(Aresta* _proximo);

    private:
        int noAdjacente;
        float peso;
        Aresta *proximo;
};

#endif // ARESTA_H