#ifndef OBJGRAFO_H
#define OBJGRAFO_H
#include <iostream>

class ObjGrafo
{
    public:
        ObjGrafo();
        ~ObjGrafo();

        int getRotulo();
        void setRotulo(int rot);

        int getPeso();
        void setPeso(int pes);

        ObjGrafo* getAresta();
        void setAresta(ObjGrafo *a);

        ObjGrafo* getNo();
        void setNo(ObjGrafo *n);

    private:
        int rotulo;
        int peso;
        ObjGrafo *aresta;
        ObjGrafo *no;
};

#endif // OBJGRAFO_H
