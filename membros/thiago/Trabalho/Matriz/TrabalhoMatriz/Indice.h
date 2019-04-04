#ifndef INDICE_H
#define INDICE_H


class Indice
{
    public:
        Indice(int n);
        ~Indice();

    private:
        int **indices;
        int _n;
        void insereVerticeNoIndice(int id);
        void procuraPosicaoNoIndice(int id);
};

#endif // INDICE_H
