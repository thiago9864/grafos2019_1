#include "DotGenerator.h"

DotGenerator::DotGenerator(){}
DotGenerator::~DotGenerator(){}

/**
 * Esse metodo verifica se o stringstream principal (ss) ja tem uma determinada aresta
 * parametros: id1, id2 (recebe os ids da aresta)
 * encapsulamento: private
 * retorna: true, se tiver repetida e false, se não tiver repetidas
 **/
bool DotGenerator::checarArestaParaRepetidas(int id1, int id2)
{
    bool temRepetido = false;
    int a, b;
    stringstream ss2;
    ss2 << ss.str();

    while (ss2 >> a >> b)
    {
        if((a == id1 && b == id2) || (a == id2 && b == id1)){
            temRepetido = true;
            break;
        }
    }

    return temRepetido;
}

/**
 * Esse metodo cria o arquivo .cv no formato DOT, pra ser aberto no GraphViz ou em outros softwares similares
 * parametro: *grafo (recebe ponteiro pro primeiro nó do grafo)
 * parametro: direcional (recebe inteiro se é direcional ou não)
 * parametro: ponderado (recebe inteiro que descreve o tipo de ponderação)
 * encapsulamento: public
 **/
void DotGenerator::gerar(No* grafo, int direcional, int ponderado)
{
    No *vertice = grafo;
    int ind = 0;
    
    outFile.open("grafoDot.cv");

    //verifica se o arquivo foi aberto
    if (!outFile || !outFile.is_open())
    {
        cout << "Impossivel abrir o arquivo de saida para escrita";
    }

    if(direcional == 0){
        outFile << "graph {" << endl;
    } else {
        outFile << "digraph {" << endl;
    }


    while(vertice != NULL)
    {
        //pega o vertice
        int idVertice = vertice->getID();

        //varre a lista de adjacencia
        Aresta *aresta = vertice->getAdjacente();
        while(aresta != NULL)
        {
            int idAresta = aresta->getNoAdjacente();
            float peso = aresta->getPeso();

            if(direcional == 1){
                if(ponderado == 1 || ponderado == 3){
                    outFile << "    " << idVertice << "->" << idAresta << " [label=" << peso << "];" << endl;
                } else {
                    outFile << "    " << idVertice << "->" << idAresta << ";" << endl;
                }
                ss << idVertice << " " << idAresta << endl;
            } else {
                if(!checarArestaParaRepetidas(idVertice, idAresta)){
                    if(ponderado == 1 || ponderado == 3){
                        outFile << "    " << idVertice << "--" << idAresta << " [label=" << peso << "];" << endl;
                    } else {
                        outFile << "    " << idVertice << "--" << idAresta << ";" << endl;
                    }
                    ss << idVertice << " " << idAresta << endl;
                }
            }

            aresta = aresta->getProximo();
        }
        vertice = vertice->getProximo();
    }

    outFile << "}";

    outFile.close();
}