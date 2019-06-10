/**
    Universidade Federal de Juiz de Fora
    main.cpp
    Propósito: Arquivo principal do trabalho.

    @author Thiago Almeida
    @version 1.0 30/03/19 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "Grafo.h"
#include "Steiner.h"

using namespace std;

/**
Atividade 3 - Algoritmo guloso

INSTANCIA STEINER 8 TERMINAIS E 64 VERTICES (Resultado exato: 2338)
clear && g++ -std=c++11 *.cpp -o main && ./main ../data/cc3-4p_R2338.stp ../data/saida.txt
cls & g++ -std=c++11 *.cpp -o main & main.exe ../data/cc3-4p_R2338.stp ../data/saida.txt


Comando descrito
./main <arq entrada> <arq saida> <direcionado> <ponderadoVertice> <ponderadoAresta>

Parametros
<arq entrada>       = Caminho do arquivo contendo a instancia
<arq saida>         = Caminho do arquivo com os logs de saída
<direcionado>       = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoVertice>  = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoAresta>   = 1: Sim, 0: Não (opcional, Sim por padrão)
**/


/*===============================================*/
/********* Controle do arquivo de Saida **********/
/*===============================================*/


ofstream arqSaida;

/**
 * Abre o arquivo de saída para escrita.
 * @param nomeArqSaida caminho do arquivo de saida
 */
void iniciaArquivoSaida(string caminhoArqSaida)
{
    //abre arquivo para saida
    arqSaida.open(caminhoArqSaida.c_str());

    //verifica se o arquivo foi aberto
    if (!arqSaida || !arqSaida.is_open())
    {
        cout << "Impossivel abrir o arquivo de saida para escrita";
        exit(1); // sai do programa se nao conseguir abrir o arquivo
    }
}

/**
 * Fecha o arquivo de saída para escrita.
 */
void fechaArquivoDeSaida(){
    if(arqSaida.is_open()){
        arqSaida.close();
    }    
}



/*===============================================*/
/******** Programa principal do trabalho *********/
/*===============================================*/



int main(int argc, char *argv[])
{
    //variaveis
    string arquivoEntrada, arquivoSaida;
    bool isDirecionado = false;
    bool isPonderadoVertice = false;
    bool isPonderadoAresta = true;

    //time_t t_inicio = std::time(0);
    //cout << t_inicio << endl;

    //verifica a quantidade de parametros recebidos
    if(argc < 3)
    {
        cout << "Número de parametros insuficiente. use: main <arq entrada> <arq saida> no mínimo." << endl;
        cout << "Ou use parametros opcionais nessa ordem após os obrigatórios: <direcionado> <ponderadoVertice> <ponderadoAresta>" << endl;
        return 0;
    }

    //obtem parametros obrigatórios
    arquivoEntrada = argv[1];
    arquivoSaida = argv[2];

    //obtem parametros opcionais, se fornecidos
    string arg3, arg4, arg5;
    if(argc >= 4)
    {
        if(stoi(argv[3]) == 1)
        {
            //cout << "4" << endl;
            isDirecionado = true;
        }
    }
    if(argc >= 5)
    {
        
        if(stoi(argv[4]) == 1)
        {
            //cout << "5" << endl;
            isPonderadoVertice = true;
        }
    }
    if(argc >= 6) 
    {
        
        if(stoi(argv[5]) == 0)
        {
            //cout << "6" << endl;
            isPonderadoAresta = false;
        }
    }

    //inicializa log
    iniciaArquivoSaida(arquivoSaida);

    arqSaida << "**** Trabalho Grafos 2019.1 - Grupo 7 ****" << endl << endl;

    arqSaida << "## Parametros recebidos ##" << endl;
    arqSaida << "arquivoEntrada: " + arquivoEntrada << endl;
    arqSaida << "arquivoSaida: " + arquivoSaida << endl;
    
    if(isDirecionado){
        arqSaida << "isDirecionado: Sim" << endl;
    } else {
        arqSaida << "isDirecionado: Não" << endl;
    }

    if(isPonderadoVertice){
        arqSaida << "isPonderadoVertice: Sim" << endl;
    } else {
        arqSaida << "isPonderadoVertice: Não" << endl;
    }

    if(isPonderadoAresta){
        arqSaida << "isPonderadoAresta: Sim" << endl;
    } else {
        arqSaida << "isPonderadoAresta: Não" << endl;
    }

    arqSaida << endl;

    //inicializa grafo
    Grafo grafo(isDirecionado, isPonderadoVertice, isPonderadoAresta);

    //carrega o arquivo
    std::size_t found = arquivoEntrada.find("stp");

    cout << (found == std::string::npos) << endl;
    if(found != std::string::npos){
        arqSaida << "Arquivo STP: Sim" << endl;
        cout << "Arquivo STP: Sim" << endl;
        grafo.parseSTP(arquivoEntrada);
    } else {
        arqSaida << "Arquivo STP: Não" << endl;
        cout << "Arquivo STP: Não" << endl;
        grafo.parseTXT(arquivoEntrada);
    }
    
    cout << "Terminou a leitura" << endl;


    arqSaida << endl << "**** Calcula Steiner ****" << endl << endl;

    Steiner s(&grafo);
    s.calcular();

    fechaArquivoDeSaida();

    return 0;
}

