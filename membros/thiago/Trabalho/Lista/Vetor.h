/**
    Universidade Federal de Juiz de Fora
    Vetor.h
    Propósito: Classe que representa um vetor que pode ser ordenado.

    @author Thiago Almeida
    @version 1.0 26/05/19 
*/

#ifndef VETOR_H
#define VETOR_H
#include <iostream>

using namespace std;


template <class T> class Vetor
{
    public:
        Vetor(int tamanho, bool ordenado);
        ~Vetor();
        
        void add(T valor);
        void set(int id, T valor);
        T getByIndice(int indice);
        T getById(int id);
        int tamanho();
        T procuraObjetoPorId(int id);
        int procuraIndice(int id);
        bool contem(T valor);
        bool vazio();
        T remover(int indice);

    private:
        T *vetor;
        int capacidade;
        int num_elementos;
        bool ordenado;
};

#endif // VETOR_H
