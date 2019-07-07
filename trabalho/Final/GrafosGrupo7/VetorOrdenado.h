/**
    Universidade Federal de Juiz de Fora
    VetorOrdenado.h
    Propósito: Classe que representa um vetor de duas dimensões ordenado.

    @author Thiago Almeida
    @version 1.0 29/05/19
*/

#ifndef VETORORDENADO_H
#define VETORORDENADO_H
#include <iostream>
#include <iomanip>

using namespace std;


template <class T>
class VetorOrdenado
{
    private:
        T **vetor;
        int numeroColunas;
        int numeroLinhas;
        int num_elementos;

        int procuraIndice(T indice)
        {
            if(num_elementos == 0)
            {
                return -1;
            }
            else
            {
                if(num_elementos == 1 && vetor[0][0] == indice)
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
                        if (indice == vetor[meio][0])
                        {
                            return meio;
                        }
                        if (indice < vetor[meio][0])
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

        }
        bool validaLinha(int linha){
            if(linha > 0 && linha < numeroLinhas){
                return true;
            } else {
                return false;
            }
        }

    public:
        VetorOrdenado(int numeroColunas, int numeroLinhas){

            if(numeroLinhas <= 1){
                numeroLinhas = 2;
            }

            this->numeroColunas = numeroColunas;
            this->numeroLinhas = numeroLinhas;

            //cria matriz
            vetor = new T*[numeroColunas];
            for(int i=0; i < numeroColunas; i++){
                vetor[i] = new T[numeroLinhas];
            }
            num_elementos = 0;
        }
        ~VetorOrdenado(){
            for(int i=0; i < numeroColunas; i++){
                vetor[i] = NULL;
            }
            delete vetor;
        }

        /**
         * Obtem a quantidade de valores armazenados
         * @return quantidade
         */
        int getTamanho(){
            return num_elementos;
        }

        /**
         * Obtem a capacidade maxima do vetor em colunas
         * @return capacidade
         */
        int getCapacidade(){
            return numeroColunas;
        }

        /**
         * Adiciona um indice e preenche as outras colunas com um valor padrao
         * @param indice Indice armazenado na coluna 0
         * @param padrao Valor padrao
         */
        void addIndex(T indice, T padrao){
            if(num_elementos < numeroColunas){
                //insere ordenado
                if(num_elementos == 0 || vetor[num_elementos-1][0] < indice)
                {
                    //se o vetor estiver vazio ou o valor é maior do que o ultimo, insere em o(1)
                    vetor[num_elementos][0] = indice;
                    for(int j=1; j<numeroLinhas; j++){
                        vetor[num_elementos][j] = padrao;
                    }
                    num_elementos++;
                }
                else if(num_elementos == 1)
                {
                    //o vetor tem 1 e o valor é menor que o vetor[0], insere em o(1)
                    //T *aux = copiar(vetor[0]);

                    //cout << "teste " << *aux << endl;

                    for(int k=0; k<numeroLinhas; k++){
                        vetor[1][k] = vetor[0][k];
                    }

                    vetor[0][0] = indice;
                    for(int j=1; j<numeroLinhas; j++){
                        vetor[0][j] = padrao;
                    }

                    //vetor[1] = aux;



                    num_elementos++;
                }
                else
                {
                    //o valor esta no meio do vetor, encontra o primeiro maior que ele
                    int i;
                    for(i=0; i < num_elementos; i++)
                    {
                        if(vetor[i][0] > indice)
                        {
                            break;
                        }
                    }

                    //faz o deslocamento do vetor
                    for(int j=num_elementos; j > i; j--)
                    {
                        //vetor[j] = copiar(vetor[j-1]);
                        for(int k=0; k<numeroLinhas; k++){
                            vetor[j][k] = vetor[j-1][k];
                        }

                    }

                    //insere ele na posicao, em o(n)
                    vetor[i][0] = indice;
                    for(int j=1; j<numeroLinhas; j++){
                        vetor[i][j] = padrao;
                    }

                    //conta a inserção
                    num_elementos++;
                }
            }
        }

        /**
         * Obtem a posicao do vetor dado o id
         * @param indice Indice armazenado na coluna 0
         */
        int getIdPos(T indice){
            return procuraIndice(indice);
        }

        /**
         * Define um valor na posicao de indice dado, na linha dada
         * @param indice Indice armazenado na coluna 0
         * @param linha Posicao da linha
         * @param valor Valor a ser armazenado
         */
        void set(T indice, int linha, T valor){
            if(validaLinha(linha)){
                int i = procuraIndice(indice);
                if(i != -1){
                    vetor[i][linha] = valor;
                } else {
                    cout << "VetorOrdenado: Indice não encontrado" << endl;
                }
            } else {
                cout << "VetorOrdenado: Numero da linha invalido" << endl;
            }
        }

        /**
         * Define um valor na posicao de indice dado, na linha dada
         * @param indice Indice armazenado na coluna 0
         * @param linha Posicao da linha
         * @param valor Valor a ser armazenado
         */
        void setByPos(int pos_indice, int linha, T valor){
            if(validaLinha(linha)){
                int i = pos_indice;
                if(i != -1){
                    vetor[i][linha] = valor;
                } else {
                    cout << "VetorOrdenado: Indice não existe" << endl;
                }
            } else {
                cout << "VetorOrdenado: Numero da linha invalido" << endl;
            }
        }

        /**
         * Obtem um valor dado o indice e a linha
         * @param indice Indice armazenado na coluna 0
         * @param linha Posicao da linha
         * @return Valor armazenado
         */
        T getByIndice(int indice, int linha){
            if(validaLinha(linha)){
                int i = procuraIndice(indice);
                if(i != -1){
                    return vetor[i][linha];
                } else {
                    cout << "VetorOrdenado: Indice não encontrado" << endl;
                    return -1;
                }
            } else {
                cout << "VetorOrdenado: Numero da linha invalido" << endl;
                return -1;
            }
        }

        /**
         * Obtem um valor dada as coordenadas da coluna e linha
         * @param coluna Posicao da coluna
         * @param linha Posicao da linha
         * @return Valor armazenado
         */
        T getByPos(int coluna, int linha){
            if(coluna >= 0 && coluna < numeroColunas && linha>=0 && linha < numeroLinhas){
                return vetor[coluna][linha];
            }
            return -1;
        }

        /**
         * Remove uma coluna pelo indice armazenado na coluna 0
         * @param indice Id da colula
         * @return Coluna excluida
         */
        T* removeById(T indice){

            if(num_elementos > 0){

                int i = procuraIndice(indice);

                if(i != -1){
                    num_elementos--;
                    T *elementoRemovido = vetor[i];

                    //remove se não for o ultimo
                    if(i < num_elementos){
                        for(int j = i; j < num_elementos; j++){
                            vetor[j] = vetor[j+1];
                        }
                    }

                    return elementoRemovido;
                } else {
                    cout << "VetorOrdenado: Indice não encontrado" << endl;
                    return NULL;
                }

            } else {
                cout << "VetorOrdenado: O vetor está vazio" << endl;
                return NULL;
            }

        }

        void imprime(){
            for(int i=0; i < numeroColunas; i++){
                //cout << "(";
                for(int j=0; j < numeroLinhas; j++){
                    if(j>0){
                        cout <<  "";
                    }
                    cout << left << setw(6) << vetor[i][j];
                }
                cout << endl;
            }
        }
};

#endif // VETORORDENADO_H
