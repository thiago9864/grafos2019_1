/**
    Universidade Federal de Juiz de Fora
    DotGenerator.cpp
    Propósito: Geração de arquivos no formato DOT a partir de um grafo armazenado em lista de adjacência.

    @author Thiago Almeida
    @version 1.0 22/04/19 
*/

#include "DotGenerator.h"

DotGenerator::DotGenerator(){}
DotGenerator::~DotGenerator(){}


/** Verifica se o stringstream principal ja tem uma determinada aresta
* @param id1 Identificador do vertice de origem
* @param id2 Identificador do vertice de destino
* @param peso Peso da aresta
* @return true, se tiver repetida e false, se não tiver repetidas
*/
bool DotGenerator::checarArestaParaRepetidas(int id1, int id2)
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


/** Verifica se o stringstream principal ja tem uma determinada aresta
* @param *grafo Ponteiro pro primeiro nó do grafo
* @param direcional Inteiro se é direcional ou não
* @param ponderado Inteiro que descreve o tipo de ponderação
*/
void DotGenerator::gerar(Grafo* grafo, bool isDirecionado, bool isPonderadoVertice, bool isPonderadoAresta, string nomeArquivo)
{
    No *vertice = grafo->getGrafo();
    int ind = 0;

    //limpa o stringstream de checagem de nos repetidos
    ss.str(std::string());

    outFile.open(nomeArquivo.c_str());

    //verifica se o arquivo foi aberto
    if (!outFile || !outFile.is_open())
    {
        cout << "Impossivel abrir o arquivo de saida para escrita";
    }

    if(!isDirecionado){
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
            if(isPonderadoVertice){
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

            if(isDirecionado){

                //inicia a linha
                outFile << "    ";

                if(isPonderadoVertice){
                    //inclui os vertices com os pesos
                    outFile << idVertice << "(" << pesoVerticeOrigem << ") " << "->" << idAresta << "(" << pesoVerticeDestino << ") ";
                } else {
                    //inclui os vertices
                    outFile << idVertice << "->" << idAresta;
                }

                if(isPonderadoAresta){
                    //inclui o peso da aresta
                    outFile << " [label=" << pesoAresta << "];" << endl;
                } 

                //adiciona para teste de repeticao
                ss << idVertice << " " << idAresta << " " << endl;
            } else {
                if(!checarArestaParaRepetidas(idVertice, idAresta)){
                    //inicia a linha
                    outFile << "    ";

                    if(isPonderadoVertice){
                        //inclui os vertices com os pesos
                        outFile << idVertice << "(" << pesoVerticeOrigem << ") " << "--" << idAresta << "(" << pesoVerticeDestino << ") ";
                    } else {
                        //inclui os vertices
                        outFile << idVertice << "--" << idAresta;
                    }

                    if(isPonderadoAresta){
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
