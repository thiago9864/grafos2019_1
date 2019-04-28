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
#include "Log.h"
#include "Grafo.h"
#include "DotGenerator.h"

using namespace std;

/**
Prototipo de codigo pra avaliacao

LINHA DE COMANDO PRA RODAR:
clear && g++ *.cpp -o main && ./main entrada.txt saida.txt 0 0 1

COM GRAFO MAIOR
clear && g++ *.cpp -o main && ./main ../../instancias/frb59-26-4_clique.txt saida.txt 0 0 1

Comando descrito para o professor
./main <arq entrada> <arq saida> <direcionado> <ponderadoVertice> <ponderadoAresta>

Parametros
<arq entrada>       = Caminho do arquivo contendo a instancia
<arq saida>         = Caminho do arquivo com os logs de saída
<direcionado>       = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoVertice>  = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoAresta>   = 1: Sim, 0: Não (opcional, Sim por padrão)
**/

int convertCharToInt(char c)
{
    return (int)c - '0';
}


int main(int argc, char *argv[])
{
    //variaveis
    string arquivoEntrada, arquivoSaida;
    bool isDirecionado = false;
    bool isPonderadoVertice = false;
    bool isPonderadoAresta = true;

    time_t t_inicio = std::time(0);
    //cout << t_inicio << endl;

    //verifica a quantidade de parametros recebidos
    if(argc < 3)
    {
        cout << "Numero de parametros insuficiente. use: grafosGrupo7 <arq entrada> <arq saida> <direcionado> <ponderadoVertice> <ponderadoAresta>" << endl;
        return 0;
    }

    //obtem parametros obrigatórios
    arquivoEntrada = argv[1];
    arquivoSaida = argv[2];

    //obtem parametros opcionais, se fornecidos
    string arg3, arg4, arg5;
    if(argc >= 4)
    {
        if(convertCharToInt(*argv[3]) == 1)
        {
            cout << "4" << endl;
            isDirecionado = true;
        }
    }
    if(argc >= 5)
    {
        
        if(convertCharToInt(*argv[4]) == 1)
        {
            cout << "5" << endl;
            isPonderadoVertice = true;
        }
    }
    if(argc >= 6) 
    {
        
        if(convertCharToInt(*argv[5]) == 0)
        {
            cout << "6" << endl;
            isPonderadoAresta = false;
        }
    }
    
    


    //inicializa log
    Log log(arquivoSaida);

    log.title("Trabalho Grafos 2019.1 - Grupo 7");

    log.header("Parametros recebidos");
    log.info("arquivoEntrada: " + arquivoEntrada);
    log.info("arquivoSaida: " + arquivoSaida);
    
    if(isDirecionado){
        log.info("isDirecionado: Sim");
    } else {
        log.info("isDirecionado: Não");
    }

    if(isPonderadoVertice){
        log.info("isPonderadoVertice: Sim");
    } else {
        log.info("isPonderadoVertice: Não");
    }

    if(isPonderadoAresta){
        log.info("isPonderadoAresta: Sim");
    } else {
        log.info("isPonderadoAresta: Não");
    }

    log.info("\n");

    //inicializa grafo
    Grafo grafo(isDirecionado, isPonderadoVertice, isPonderadoAresta);
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

    dg.gerar(&grafo, isDirecionado, isPonderadoVertice, isPonderadoAresta, "grafo_antes.gv");
    grafo.sequenciaGrau();

    //grafo.removerAresta(81, 82);
    //grafo.removerAresta(80, 81);

    grafo.removerVertice(81);

    //operacoes de teste
    dg.gerar(&grafo, isDirecionado, isPonderadoVertice, isPonderadoAresta, "grafo_depois.gv");
    grafo.sequenciaGrau();
    grafo.imprimir();

    log.title("Caminhamento por Profundidade");

    //busca
    ListaArestas *caminho = grafo.buscaEmProfundidade(12, 82);
    if(caminho != NULL){
        log.ssLog << "caminho 12-82 encontrado" << endl;
        Aresta *arrCaminho = caminho->getArrayArestas();
        for(int i=0; i < caminho->getTamanho(); i++)
        {
            log.ssLog << "Aresta #" << i << " (" << arrCaminho[i].getNoOrigem() << ", " << arrCaminho[i].getNoAdj() << ") peso: " << arrCaminho[i].getPeso() << endl;
        }
        log.ssLog << endl;
        log.logSSBuffer();
    }


    caminho = grafo.buscaEmProfundidade(10, 82);
    if(caminho != NULL){
        log.ssLog << "caminho 10-82 encontrado" << endl;
        Aresta *arrCaminho = caminho->getArrayArestas();
        for(int i=0; i < caminho->getTamanho(); i++)
        {
            log.ssLog << "Aresta #" << i << " (" << arrCaminho[i].getNoOrigem() << ", " << arrCaminho[i].getNoAdj() << ") peso: " << arrCaminho[i].getPeso() << endl;
        }
        log.ssLog << endl;
        log.logSSBuffer();
    }

    caminho = grafo.buscaEmProfundidade(25, 82);
    if(caminho != NULL){
        log.ssLog << "caminho 25-82 encontrado" << endl;
        Aresta *arrCaminho = caminho->getArrayArestas();
        for(int i=0; i < caminho->getTamanho(); i++)
        {
            log.ssLog << "Aresta #" << i << " (" << arrCaminho[i].getNoOrigem() << ", " << arrCaminho[i].getNoAdj() << ") peso: " << arrCaminho[i].getPeso() << endl;
        }
        log.ssLog << endl;
        log.logSSBuffer();
    }

    
    

    time_t t_fim = std::time(0);
    //cout << t_fim << endl;

    time_t t_dif = t_fim - t_inicio;

    cout << "T-diff: " << t_dif << endl;

    return 0;
}

