#ifndef NO_H
#define NO_H
#include <iostream>
#include "Aresta.h"

class No 
{
    public:
        No(); 
        ~No();

        int getID();
        void setID(int _id);

        float getPeso();
        void setPeso(float _peso);

        Aresta* getAdjacente();
        void setAdjacente(Aresta *_adjacente);

        Aresta* getUltimaAdjacente();
        void setUltimaAdjacente(Aresta *_ultimaAdjacente);

        No* getProximo();
        void setProximo(No* _no);

        int getGrauEntrada();
        void setGrauEntrada(int _grauEntrada);
        void addGrauEntrada();
        void removeGrauEntrada();

        int getGrauSaida();
        void setGrauSaida(int _grauSaida);
        void addGrauSaida();
        void removeGrauSaida();

    private:
        int id;
        float peso;
        Aresta *adjacente;
        Aresta *ultimaAdjacente;
        No *proximo;
        int grauEntrada;
        int grauSaida;
};

#endif // NO_H
