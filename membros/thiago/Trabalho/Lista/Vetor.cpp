/**
    Universidade Federal de Juiz de Fora
    Vetor.cpp
    Propósito: Classe que representa um vetor que pode ser ordenado.

    @author Thiago Almeida
    @version 1.0 26/05/19 

    ///// Modo de usar /////

    Tem que usar uma struct com essa classe

    struct StructName {
        int id; //esse campo é obrigatório
        //a partir daqui entra qualquer campo de qualquer tipo
    };

    Vetor<StructName> nome_vetor(<tamanho>, <true pra ordenado, false pra normal>);
*/

#include "Vetor.h"
template <class T>
Vetor<T>::Vetor(int capacidade, bool ordenado)
{
    this->capacidade = capacidade;
    this->ordenado = ordenado;
    vetor = new T[capacidade];
    num_elementos = 0;
}

template <class T>
Vetor<T>::~Vetor()
{
    delete vetor;
}

template <class T>
void Vetor<T>::add(T valor)
{

    if(num_elementos < tamanho)
    {
        if(ordenado)
        {
            //insere ordenado
            if(num_elementos == 0 || vetor[num_elementos-1] < valor)
            {
                //se o vetor estiver vazio ou o valor é maior do que o ultimo, insere em o(1)
                vetor[num_elementos] = valor;
                num_elementos++;
            }
            else if(num_elementos == 1)
            {
                //o vetor tem 1 e o valor é menor que o vetor[0], insere em o(1)
                int aux = vetor[0];
                vetor[0] = valor;
                vetor[1] = aux;
                num_elementos++;
            }
            else
            {
                //o valor esta no meio do vetor, encontra o primeiro maior que ele
                int i;
                for(i=0; i < num_elementos; i++)
                {
                    if(vetor[i].id > valor.id)
                    {
                        break;
                    }
                }

                //faz o deslocamento do vetor
                for(int j=num_elementos; j > i; j--)
                {
                    vetor[j] = vetor[j-1];
                }

                //insere ele na posicao, em o(n)
                vetor[i] = valor;
                
                //conta a inserção
                num_elementos++;
            }
        } 
        else 
        {
            //insere no fim
            vetor[num_elementos] = valor;
        }
    }

}

template <class T>
void Vetor<T>::set(int indice, T valor){
    if(num_elementos > 0 && indice >= 0 && indice < tamanho){
        vetor[indice] = valor;
    }
}

template <class T>
T Vetor<T>::getByIndice(int indice){
    if(num_elementos > 0 && index >= 0 && index < tamanho){
        return vetor[num_elementos]
    }
    return NULL;
}

template <class T>
T Vetor<T>::getById(int id){
    int indice = procuraIndice(id);
    if(indice != -1){
        return vetor[indice];
    }
    return NULL;
}

template <class T>
int Vetor<T>::tamanho(){
    return num_elementos;
}

template <class T>
T Vetor<T>::procuraObjetoPorId(int id)
{
    return get(procuraIndice(id));
}

template <class T>
int Vetor<T>::procuraIndice(int id)
{
    if(num_elementos == 0)
    {
        return -1;
    }
    else if (ordenado)
    {
        if(num_elementos == 1 && vetor[0].id == id)
        {
            return 0;
        }
        else
        {
            //busca binaria (o vetor está ordenado)
            int inicio = 0;     
            int fim = num_elementos-1;
            int meio;

            while (inicio <= fim)
            {
                meio = (inicio + fim)/2;
                if (id == vetor[meio].id)
                {
                    return meio;
                }
                if (id < vetor[meio].id)
                {
                    fim = meio-1;
                }
                else
                {
                    inicio = meio+1;
                }
            }
            return -1;   // não encontrado
        }
    } 
    else 
    {
        for(int i=0; i<num_elementos; i++){
            if(vetor[i].id == id){
                return i;
            }
        }
        return -1;   // não encontrado
    }
}

template <class T>
bool Vetor<T>::contem(T valor){
    return (procurar(valor) != -1);
}

template <class T>
bool Vetor<T>::vazio(){
    return (num_elementos == 0);
}

template <class T>
T Vetor<T>::remover(int indice){

    T objRemover = NULL;

    if(num_elementos > 0 && index >= 0 && index < tamanho){

        //remove o ultimo
        T objRemover = get(indice);
        
        if(indice == num_elementos-1)
        {
            num_elementos--;
        }
        else
        {
            //remove se não for o ultimo
            num_elementos--;
            for(int i = indice; i < num_elementos; i++){
                valor[i] = valor[i+1];
            }
        }

    }

    return objRemover;
}