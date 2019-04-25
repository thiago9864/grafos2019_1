#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "Log.h"
#include "Grafo.h"
#include "DotGenerator.h"

using namespace std;

/**
Prototipo de codigo pra avaliacao

LINHA DE COMANDO PRA RODAR:
clear && g++ main.cpp Grafo.cpp Aresta.cpp No.cpp Log.cpp ListaDeGrafos.cpp DotGenerator.cpp -o main && ./main entrada.txt saida.txt 0 1

VARIACAO
clear && g++ *.cpp -o main && ./main entrada.txt saida.txt 0 1
clear; g++ *.cpp -o main; ./main entrada.txt saida.txt 0 1

COM GRAFO MAIOR
clear && g++ main.cpp Grafo.cpp Aresta.cpp No.cpp Log.cpp ListaDeGrafos.cpp DotGenerator.cpp -o main && ./main ../../instancias/frb59-26-4_clique.txt saida.txt 0 1

Comando descrito para o professor
./main <arq entrada> <arq saida> <direcionado> <ponderado>

Parametros
<arq entrada>  = Nome do arquivo contendo o grafo que vai estar na mesma pasta do executável
<arq saida>    = Nome do arquivo com os logs de saída que vai estar na mesma pasta do executável
<direcionado>  = 0: Grafo não direcionado, 1: Grafo direcionado
<ponderado>    = 0: Grafo não ponderado, 1: Grafo ponderado nas arestas, 2: Grafo ponderado nos vértices, 3: Grafo ponderado nas arestas e vértices
**/

string bool_to_string(bool valor) {
    if(valor){
        return "Sim";
    } else {
        return "Nao";
    }
}

int main(int argc, char *argv[])
{
    //variaveis
    string arquivoEntrada, arquivoSaida;
    bool isDirecionado = false;
    int ponderado = 0;

    time_t t_inicio = std::time(0);
    //cout << t_inicio << endl;

    //verifica a quantidade de parametros recebidos
    if(argc < 5)
    {
        cout << "Numero de parametros insuficiente. use: grafosGrupo7 <arq entrada> <arq saida> <direcionado> <ponderado>" << endl;
        return 0;
    }

    //obtem parametros
    arquivoEntrada = argv[1];
    arquivoSaida = argv[2];

    if(*argv[3] == '1')
    {
        isDirecionado = true;
    }
    ponderado =  (int)*argv[4] - 48;

    //inicializa log
    Log log(arquivoSaida);

    log.title("Trabalho Grafos 2019.1 - Grupo 7");

    log.header("Parametros recebidos");
    log.info("arquivoEntrada: " + arquivoEntrada);
    log.info("arquivoSaida: " + arquivoSaida);
    log.info("isDirecionado: " + bool_to_string(isDirecionado));

    switch (ponderado)
    {
        case 0:
            log.info("ponderado: 0 -> não");
            break;

        case 1:
            log.info("ponderado: 1 -> nas arestas");
            break;

        case 2:
            log.info("ponderado: 2 -> nos vertices");
            break;

        case 3:
            log.info("ponderado: 3 -> nos vertices e nas arestas");
            break;

        default:
            ponderado = 0;
            log.info("ponderado: 0 -> não");
            break;
    }


    //inicializa grafo
    Grafo grafo(isDirecionado, ponderado);
    DotGenerator dg;

    //carrega o arquivo
    grafo.parse(arquivoEntrada);


    //operacoes do grafo
    grafo.adicionaVertice(80, 0);
    grafo.adicionaAresta(81, 0, 82, 0, 2.58);
    grafo.adicionaAresta(12, 0, 82, 0, 5.25);
    grafo.adicionaAresta(80, 0, 81, 0, 154);
    grafo.adicionaAresta(80, 0, 10, 0, -152);

    //tenta uma aresta repetida, mas com peso diferente
    grafo.adicionaAresta(81, 0, 82, 0, -0.55);
    grafo.adicionaAresta(81, 0, 82, 0, -0.55);

    dg.gerar(grafo.getGrafo(), isDirecionado, ponderado, "grafo_antes.gv");
    grafo.sequenciaGrau();

    //grafo.removerAresta(81, 82);
    //grafo.removerAresta(80, 81);

    grafo.removerVertice(81);

    //operacoes de teste
    dg.gerar(grafo.getGrafo(), isDirecionado, ponderado, "grafo_depois.gv");
    grafo.sequenciaGrau();
    grafo.imprimir();


    //busca
    /*
    if(grafo.buscaEmProfundidade(10) != NULL){
        cout << "vertice 10 encontrado" << endl;
    }

    if(grafo.buscaEmProfundidade(12) != NULL){
        cout << "vertice 12 encontrado" << endl;
    }

    if(grafo.buscaEmProfundidade(24) != NULL){
        cout << "vertice 24 encontrado" << endl;
    }

    if(grafo.buscaEmProfundidade(25) != NULL){
        cout << "vertice 25 encontrado" << endl;
    }
    */
    if(grafo.buscaEmProfundidade(82) != NULL){
        cout << "vertice 82 encontrado" << endl;
    }
    /*
    if(grafo.buscaEmProfundidade(13) != NULL){
        cout << "vertice 13 encontrado" << endl;
    }

    if(grafo.buscaEmProfundidade(80) != NULL){
        cout << "vertice 80 encontrado" << endl;
    }

    if(grafo.buscaEmProfundidade(81) != NULL){
        cout << "vertice 81 encontrado" << endl;
    }
    */

    time_t t_fim = std::time(0);
    //cout << t_fim << endl;

    time_t t_dif = t_fim - t_inicio;

    cout << "T-diff: " << t_dif << endl;

    return 0;
}

