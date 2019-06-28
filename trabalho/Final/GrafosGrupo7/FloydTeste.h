/**
    Universidade Federal de Juiz de Fora
    Dijkstra.h
    Propósito: Calcula o caminho mínimo usando o algoritmo de Dijkstra.

    @author Thiago Almeida
    @version 1.3 12/06/19
*/

#ifndef FLOYD_H
#define FLOYD_H
#include <iostream>
#include <stack>
#include "No.h"
#include "Grafo.h"

class FloydTeste
{
    public:
        FloydTeste(Grafo *grafo){
            this->grafo = grafo;
            dimensoes_matriz = grafo->getOrdem() + 1;//esse +1 é a coluna dos ids

            //inicializa a matriz
            matriz = new float*[dimensoes_matriz];
            for(int i=0; i<dimensoes_matriz; i++){
                float *aux = new float[dimensoes_matriz];
                for(int j=0; j<dimensoes_matriz; j++){
                    if(i==j){
                        //coloca zero na diagonal principal
                        aux[j] = 0;
                    } else {
                        //coloca maxFloat
                        aux[j] = maxFloat;
                    }
                }
                matriz[i] = aux;
            }

            //esse ponto não será usado
            matriz[0][0] = maxFloat;
            
            No *p;
            int count = 1;
            /* Esse aqui é pra produção
            p = grafo->getListaNos();
        
            while(p != NULL){
                int id = p->getId();
                //preenche ids na coluna 0 e linha 0 - isso é a identificacao
                matriz[0][count] = id;
                matriz[count][0] = id;
                p = p->getProx();
                count++;
            }
            */

            /* Esse aqui é pra testar a instancia da lista de exercicios 3 */
            for(int j=1; j<dimensoes_matriz; j++){
                matriz[0][j] = j;
                matriz[j][0] = j;
            }

            //preenche os pesos pra matriz A0
            p = grafo->getListaNos();
            while(p != NULL){
                int origem = p->getId();
                Aresta *a = p->getAresta();
                while(a != NULL){
                    int destino = a->getNoAdj();
                    float peso = a->getPeso();
                    atualizar(origem, destino, peso);
                    a = a->getProx();
                }

                p = p->getProx();
            }

            imprimeMatriz(0);


            processaAlgoritmo();

        }
        ~FloydTeste(){
            delete matriz;
        }

    private:
        Grafo *grafo;
        float **matriz;
        int dimensoes_matriz;
        float maxFloat = 99999999999999.9;

        int getCoordenadaColuna(int id){
            for(int a = 1; a < dimensoes_matriz; a++){
                if(matriz[0][a] == id){
                    return a;
                }
            }
            return -1;
        }
        int getCoordenadaLinha(int id){
            for(int a = 1; a < dimensoes_matriz; a++){
                if(matriz[a][0] == id){
                    return a;
                }
            }
            return -1;
        }

        void atualizar(int origem, int destino, float valor){
            int i = getCoordenadaLinha(origem);
            int j = getCoordenadaColuna(destino);
            if(i != -1 && j != -1){
                matriz[i][j] = valor;
            } else {
                cout << "Floyd->atualizar: Indice inválido" << endl;
            }        
        }

        void processaAlgoritmo(){
            
            for(int k = 1; k < dimensoes_matriz; k++){
                for(int i = 1; i < dimensoes_matriz; i++){
                    for(int j = 1; j < dimensoes_matriz; j++){
                        if(i != j && i != k && j != k){
                            //só troca quem não for da diagonal principal nem de alguma das linhas/colunas selecionadas
                            float v = matriz[k][j] + matriz[i][k];
                            if(v < matriz[i][j]){
                                //atualiza se a soma dos correspondentes das linhas e colunas forem menores
                                //que o valor armazenado na interseção
                                matriz[i][j] = v;
                            }                            
                        }
                    }
                }
                imprimeMatriz(k);
            }
        }

         /**
         * Esse metodo imprime essa matriz
         * parametro: indices (ponteiro para a instancia da classe Indice)
         * encapsulamento: public
         **/
        void imprimeMatriz(int id){
            int numCasas = 3;
            char fillchar = ' ';
            string espacador = " ";
            cout << "Matriz A" << id << endl;
            for(int i = 0; i < dimensoes_matriz; i++){
                for(int j = 0; j < dimensoes_matriz; j++){
                    if(matriz[i][j] > 999999){
                        cout << setfill(fillchar) << setw(numCasas) << "." << espacador;
                    } else {
                        cout << setfill(fillchar) << setw(numCasas) << matriz[i][j] << espacador;
                    }                    
                }
                cout << endl;
            }
        }

    public:
    
        Aresta* caminhoMinimo(int origem, int destino)
        {
            return NULL;
        }
};

#endif // FLOYD_H