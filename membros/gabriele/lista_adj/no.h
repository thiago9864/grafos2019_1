#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

class No{
public:
    No(){};
    ~No(){};
    int getGrauEntrada(){return grauEntrada};
    int getGrauSaida(){return grauSaida};
    void setAresta_adj(Aresta *aresta_adj){ this.aresta_adj=aresta_adj};
    Aresta *getAresta_adj(){return *aresta_adj};
    void setId(int num){id=num};
    int getId(){return id};
    void setPeso(int peso){this.peso=peso};
    int getPeso(){return peso};
    void conta_grauEntrada();
    void conta_grauSaida();
private:
    Aresta *aresta_adj;
    int id;
    float peso;
    int grauEntrada;
    int grauSaida;

};

#endif // NO_H_INCLUDED
