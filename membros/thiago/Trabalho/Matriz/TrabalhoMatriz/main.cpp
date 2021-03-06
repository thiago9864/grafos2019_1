#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Log.h"
#include "Grafo.h"

using namespace std;

/**

LINHA DE COMANDO PRA RODAR:
clear && g++ main.cpp Grafo.cpp MatrizPesos.cpp Indice.cpp Log.cpp -o main && ./main entrada.txt saida.txt 0 1

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

    //verifica a quantidade de parametros recebidos

    if(argc < 5)
    {
        cout << "Numero de parametros insuficiente. use: main <arq entrada> <arq saida> <direcionado> <ponderado>" << endl;
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

    log.title("\n\nAtividade 1 - Matriz de Adjacencia - Grupo 7");

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

    grafo.parse(arquivoEntrada);

    grafo.imprimir();



    return 0;
}
