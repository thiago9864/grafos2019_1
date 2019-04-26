#include "DotGenerator.h"

DotGenerator::DotGenerator(){}
DotGenerator::~DotGenerator(){}

/**
 * Esse metodo verifica se o stringstream principal (ss) ja tem uma determinada aresta
 * parametros: id1, id2 (recebe os ids da aresta)
 * encapsulamento: private
 * retorna: true, se tiver repetida e false, se não tiver repetidas
 **/
bool DotGenerator::checarArestaParaRepetidas(int id1, int id2, float peso)
{
    bool temRepetido = false;
    int idVertice, idAresta;
    float pesoAresta;
    stringstream ss2;
    ss2 << ss.str();

    while (ss2 >> idVertice >> idAresta >> pesoAresta)
    {
        if((idVertice == id1 && idAresta == id2) || (idVertice == id2 && idAresta == id1 && peso == pesoAresta)){
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
void DotGenerator::gerar(No* grafo, int direcional, int ponderado, string nomeArquivo)
{
    No *vertice = grafo;
    int ind = 0;

    //limpa o stringstream de checagem de nos repetidos
    ss.str(std::string());

    outFile.open(nomeArquivo.c_str());

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
        int idVertice = vertice->getId();

        //varre a lista de adjacencia
        Aresta *aresta = vertice->getAresta();

        //se o vertice não tiver nenhuma aresta, imprime ele sozinho
        if(aresta == NULL){
            outFile << "    " << idVertice << ";" << endl;
        }

        //varre as arestas
        while(aresta != NULL)
        {
            int idAresta = aresta->getNoAdj();
            float pesoAresta = aresta->getPeso();

            if(direcional == 1){
                if(ponderado == 1 || ponderado == 3){
                    outFile << "    " << idVertice << "->" << idAresta << " [label=" << pesoAresta << "];" << endl;
                } else {
                    outFile << "    " << idVertice << "->" << idAresta << ";" << endl;
                }

                //adiciona para teste de repeticao
                ss << idVertice << " " << idAresta << " " << pesoAresta << endl;
            } else {
                if(!checarArestaParaRepetidas(idVertice, idAresta, pesoAresta)){
                    if(ponderado == 1 || ponderado == 3){
                        outFile << "    " << idVertice << "--" << idAresta << " [label=" << pesoAresta << "];" << endl;
                    } else {
                        outFile << "    " << idVertice << "--" << idAresta << ";" << endl;
                    }

                    //adiciona para teste de repeticao
                    ss << idVertice << " " << idAresta << " " << pesoAresta << endl;
                }
            }

            aresta = aresta->getProx();
        }

        vertice = vertice->getProx();
    }

    outFile << "}";

    outFile.close();
}
