#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>

class Aresta 
{
    public:
        Aresta(); 
        ~Aresta();

        int getNoAdj();
        void setNoAdj(int _noAdjacente);

        float getPeso();
        void setPeso(float _peso);

        Aresta* getProx();
        void setProx(Aresta* _proximo);

    private:
        int noAdjacente;
        float peso;
        Aresta *proximo;
};

#endif // ARESTA_H