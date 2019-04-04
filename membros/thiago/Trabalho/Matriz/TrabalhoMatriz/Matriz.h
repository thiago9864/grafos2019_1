#ifndef MATRIZ_H
#define MATRIZ_H


class Matriz
{
    public:
        Matriz(int n);
        ~Matriz();

    private:
        float **matriz;
        int _n;
};

#endif // MATRIZ_H
