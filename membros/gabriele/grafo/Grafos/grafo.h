#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

class Grafo{
public:
    Grafo(int tam);
    ~Grafo();

private:
    No *lista_no;//lista de n�s no grafo
    int tam;//tamanho do grafo informado pelo usu�rio
    bool direcionado;
    int ordem;
    bool pondNo;
    bool pondAresta;
};

#endif // GRAFO_H_INCLUDED
