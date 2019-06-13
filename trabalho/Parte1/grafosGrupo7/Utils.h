/**
    Universidade Federal de Juiz de Fora
    Utils.h
    Propósito: Concentra métodos uteis pra debug ou visualização.

    @author Thiago Almeida
    @version 1.0 12/06/19
*/

#ifndef GRAFO_UTILS_H
#define GRAFO_UTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "Aresta.h"
#include "No.h"
#include "Grafo.h"

class Utils {

    public:
        Utils(){}
        ~Utils(){}

    private:
        ofstream outFile;
        stringstream ss;

        /** Verifica se o stringstream principal ja tem uma determinada aresta
        * @param id1 Identificador do vertice de origem
        * @param id2 Identificador do vertice de destino
        * @return true, se tiver repetida e false, se não tiver repetidas
        */
        bool checarArestaParaRepetidas(int id1, int id2)
        {
            bool temRepetido = false;
            int idVertice, idAresta;
            stringstream ss2;
            ss2 << ss.str();

            while (ss2 >> idVertice >> idAresta)
            {
                if((idVertice == id1 && idAresta == id2) || (idVertice == id2 && idAresta == id1)){
                    temRepetido = true;
                    break;
                }
            }

            return temRepetido;
        }

    public:
        /**
         * Imprime na tela grafo no formato de lista de adjacência:
         *
         * DADOS:
         * Grau: valor
         * Ordem: valor
         * M: valor
         *
         * LISTA DE ADJACENCIA:
         * Vertice de origem --> Vertice adjacente (Peso) --> ...
         */
        void imprime(Grafo *grafo) {
            cout << "DADOS: " << endl;
            cout << "Grau: " << grafo->getGrau() << endl;
            cout << "Ordem: " << grafo->getOrdem() << endl;
            cout << "M: " << grafo->getNumArestas() << endl;

            cout << "LISTA DE ADJACENCIA: " << endl;
            for (No* n = grafo->getListaNos(); n != nullptr; n = n->getProx()) {

                cout << n->getId() << " ---> ";

                for (Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) {
                    // Se for ponderado nas arestas é imprimido o peso
                    if (grafo->isPonderadoAresta()) {
                        if (a->getProx() != nullptr)
                            cout << a->getNoAdj() << " (" << a->getPeso() << ") ---> ";
                        else
                            cout << a->getNoAdj() << " (" << a->getPeso() << ")";
                    } else {
                        if (a->getProx() != nullptr)
                            cout << a->getNoAdj() << " ---> ";
                        else
                            cout << a->getNoAdj();
                    }
                }

                cout << endl;

            }
        }


        /** Gera o arquivo no formato que o GraphViz lê
        * @param *grafo Ponteiro pro primeiro nó do grafo
        * @param caminhoArquivo caminho e nome para o arquivo no disco
        */
        void gerarArquivoGraphViz(Grafo* grafo, string caminhoArquivo)
        {
            No *vertice = grafo->getListaNos();
            int ind = 0;

            //limpa o stringstream de checagem de nos repetidos
            ss.str(std::string());

            outFile.open(caminhoArquivo.c_str());

            //verifica se o arquivo foi aberto
            if (!outFile || !outFile.is_open())
            {
                cout << "Impossivel abrir o arquivo de saida para escrita";
            }

            if(!grafo->isDirecionado()){
                outFile << "graph {" << endl;
            } else {
                outFile << "digraph {" << endl;
            }


            while(vertice != NULL)
            {
                //pega o vertice
                int idVertice = vertice->getId();
                float pesoVerticeOrigem = vertice->getPeso();

                //varre a lista de adjacencia
                Aresta *aresta = vertice->getAresta();

                //se o vertice não tiver nenhuma aresta, imprime ele sozinho
                if(aresta == NULL){
                    if(grafo->isPonderadoNo()){
                        outFile << "    " << idVertice << "(" << pesoVerticeOrigem << ") " << ";" << endl;
                    } else {
                        outFile << "    " << idVertice << ";" << endl;
                    }
                }

                //varre as arestas
                while(aresta != NULL)
                {
                    int idAresta = aresta->getNoAdj();
                    float pesoAresta = aresta->getPeso();
                    int pesoVerticeDestino = grafo->getNo(idAresta)->getPeso();

                    if(grafo->isDirecionado()){

                        //inicia a linha
                        outFile << "    ";

                        if(grafo->isPonderadoNo()){
                            //inclui os vertices com os pesos
                            outFile << idVertice << "(" << pesoVerticeOrigem << ") " << "->" << idAresta << "(" << pesoVerticeDestino << ") ";
                        } else {
                            //inclui os vertices
                            outFile << idVertice << "->" << idAresta;
                        }

                        if(grafo->isPonderadoAresta()){
                            //inclui o peso da aresta
                            outFile << " [label=" << pesoAresta << "];" << endl;
                        } 

                        //adiciona para teste de repeticao
                        ss << idVertice << " " << idAresta << " " << endl;
                    } else {
                        if(!checarArestaParaRepetidas(idVertice, idAresta)){
                            //inicia a linha
                            outFile << "    ";

                            if(grafo->isPonderadoNo()){
                                //inclui os vertices com os pesos
                                outFile << idVertice << "(" << pesoVerticeOrigem << ") " << "--" << idAresta << "(" << pesoVerticeDestino << ") ";
                            } else {
                                //inclui os vertices
                                outFile << idVertice << "--" << idAresta;
                            }

                            if(grafo->isPonderadoAresta()){
                                //inclui o peso da aresta
                                outFile << " [label=" << pesoAresta << "];" << endl;
                            } 

                            //adiciona para teste de repeticao
                            ss << idVertice << " " << idAresta << endl;
                        }
                    }

                    aresta = aresta->getProx();
                }

                vertice = vertice->getProx();
            }

            outFile << "}";

            outFile.close();
        }

};


#endif //GRAFO_UTILS_H






