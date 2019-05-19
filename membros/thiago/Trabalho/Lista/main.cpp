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
#include "ListaArestas.h"
#include "Steiner.h"
#include "DotGenerator.h" // auxiliar pra gerar imagens dos grafos, não essencial ao trabalho

using namespace std;

/**
Prototipo de codigo pra avaliacao

pra chegar nas pastas
cd \membros\thiago\Trabalho\Lista

LINHA DE COMANDO PRA RODAR:
clear && g++ -std=c++11 *.cpp -o main && ./main ../data/entrada.txt ../data/saida.txt 0 0 1
cls & g++ -std=c++11 *.cpp -o main & main.exe ../data/entrada.txt ../data/saida.txt 0 0 1

COM GRAFO MAIOR
clear && g++ -std=c++11 *.cpp -o main && ./main ../../instancias/frb59-26-4_clique.txt saida.txt 0 0 1
cls & g++ -std=c++11 *.cpp -o main & main.exe ../../instancias/frb59-26-4_clique.txt ../data/saida.txt 0 0 1

4 COMPONENTES CONEXAS
clear && g++ -std=c++11 *.cpp -o main && ./main ../data/entrada_conexas.txt ../data/saida.txt 0 0 1
cls & g++ -std=c++11 *.cpp -o main & main.exe ../data/entrada_conexas.txt ../data/saida.txt 0 0 1

INSTANCIA STEINER 76 TERMINAIS E 729 VERTICES (Resultado exato: 20720)
clear && g++ -std=c++11 *.cpp -o main && ./main ../data/cc6-3p_R20720.stp ../data/saida.txt 0 0 1
cls & g++ -std=c++11 *.cpp -o main & main.exe ../data/cc6-3p_R20720.stp ../data/saida.txt

INSTANCIA STEINER 50 TERMINAIS E 550 VERTICES (Resultado exato: 5616)
clear && g++ -std=c++11 *.cpp -o main && ./main ../data/bipe2p_R5616.stp ../data/saida.txt 0 0 1
cls & g++ -std=c++11 *.cpp -o main & main.exe ../data/bipe2p_R5616.stp ../data/saida.txt

INSTANCIA STEINER 8 TERMINAIS E 64 VERTICES (Resultado exato: 2338)
clear && g++ -std=c++11 *.cpp -o main && ./main ../data/cc3-4p_R2338.stp ../data/saida.txt 0 0 1
cls & g++ -std=c++11 *.cpp -o main & main.exe ../data/cc3-4p_R2338.stp ../data/saida.txt


CASO DE TESTE - ARESTAS COM MESMO PESO
clear && g++ -std=c++11 *.cpp -o main && ./main ../data/entrada_teste1.stp ../data/saida.txt 0 0 1


Comando descrito para o professor
./main <arq entrada> <arq saida> <direcionado> <ponderadoVertice> <ponderadoAresta>

Parametros
<arq entrada>       = Caminho do arquivo contendo a instancia
<arq saida>         = Caminho do arquivo com os logs de saída
<direcionado>       = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoVertice>  = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoAresta>   = 1: Sim, 0: Não (opcional, Sim por padrão)
**/

/*
int convertCharToInt(char c)
{
    return (int)c - '0';
}
*/

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
    DotGenerator dg;

    //carrega o arquivo
    std::size_t found = arquivoEntrada.find("stp");
    //cout << "found: " << found << endl;
    //cout << "std::string::npos: " << std::string::npos << endl;
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

    //operacoes do grafo
    //grafo.adicionaVertice(180, 0);
    //grafo.adicionaAresta(181, 0, 182, 0, 2.58);
    //grafo.adicionaAresta(112, 0, 182, 0, 5.25);
    //grafo.adicionaAresta(182, 0, 181, 0, 154);
    //grafo.adicionaAresta(180, 0, 110, 0, -152);

    //tenta uma aresta repetida, mas com peso diferente
    //grafo.adicionaAresta(181, 0, 182, 0, -0.55);
    //grafo.adicionaAresta(181, 0, 182, 0, -0.55);

    //dg.gerar(&grafo, isDirecionado, isPonderadoVertice, isPonderadoAresta, "../data/grafo_antes.gv");
    //grafo.sequenciaGrau();

    //grafo.removerAresta(181, 182);
    //grafo.removerAresta(180, 181);

    //grafo.removerVertice(181);

    //operacoes de teste
    dg.gerar(&grafo, isDirecionado, isPonderadoVertice, isPonderadoAresta, "../data/grafo_depois.gv");
    //grafo.sequenciaGrau();
    //grafo.imprimir();

/*
    arqSaida << "**** Caminhamento por Profundidade ****" << endl;

    //busca
    Aresta *caminho;
    
    caminho = grafo.buscaEmProfundidade(1, 3);
    arqSaida << "Procura caminho 1-3." << endl;
    if(caminho != NULL){
        arqSaida << "Encontrado." << endl;
        Aresta *aux = caminho;
        while(aux != NULL){
            arqSaida << "Aresta: (" << aux->getNoOrigem() << ", " << aux->getNoAdj() << ") peso: " << aux->getPeso() << endl;
            aux = aux->getProx();
        }
        arqSaida << endl;
    } else {
        arqSaida << "Não foi encontrado." << endl;
    }

    
    caminho = grafo.buscaEmProfundidade(10, 24);
    arqSaida << "Procura caminho 10-24." << endl;
    if(caminho != NULL){
        arqSaida << "Encontrado." << endl;
        Aresta *aux = caminho;
        while(aux != NULL){
            arqSaida << "Aresta: (" << aux->getNoOrigem() << ", " << aux->getNoAdj() << ") peso: " << aux->getPeso() << endl;
            aux = aux->getProx();
        }
        arqSaida << endl;
    } else {
        arqSaida << "Não foi encontrado." << endl;
    }
    
    caminho = grafo.buscaEmProfundidade(40, 41);
    arqSaida << "Procura caminho 40-41." << endl;
    if(caminho != NULL){
        arqSaida << "Encontrado." << endl;
        Aresta *aux = caminho;
        while(aux != NULL){
            arqSaida << "Aresta: (" << aux->getNoOrigem() << ", " << aux->getNoAdj() << ") peso: " << aux->getPeso() << endl;
            aux = aux->getProx();
        }
        arqSaida << endl;
    } else {
        arqSaida << "Não foi encontrado." << endl;
    }
    
    //tenta achar um caminho que não existe entre duas componentes conexas
    caminho = grafo.buscaEmProfundidade(10, 82);
    arqSaida << "Procura caminho que não existe entre 10-82." << endl;
    if(caminho != NULL){
        arqSaida << "Encontrado." << endl;
        Aresta *aux = caminho;
        while(aux != NULL){
            arqSaida << "Aresta: (" << aux->getNoOrigem() << ", " << aux->getNoAdj() << ") peso: " << aux->getPeso() << endl;
            aux = aux->getProx();
        }
        arqSaida << endl;
    } else {
        arqSaida << "Não foi encontrado." << endl;
    }
    

    arqSaida << endl << "**** Cobertura de vértices ****" << endl;

    No* cobertura = grafo.getCoberturaVertices();

    if(cobertura != NULL){
        No *n = cobertura;
        arqSaida << "Cobertura encontrada:" << endl;
        cout << "Cobertura encontrada:" << endl;
        while(n != NULL){
            cout << n->getId() << " ";
            arqSaida << n->getId() << " ";
            n = n->getProx();
        }
        arqSaida << endl;
        cout << endl;
    } else {
        arqSaida << "Nenhuma cobertura foi retornada." << endl;
    }
*/

    arqSaida << endl << "**** Caminho Mínimo ****" << endl << endl;

    //teste 1 caminho minimo
    Steiner s(&grafo);
    /*
    float distancia = s.obtemMenorDistancia(26, 555);
    arqSaida << "Distancia minima entre 26 e 555: " << distancia << endl;

    distancia = s.obtemMenorDistancia(374, 24);
    arqSaida << "Distancia minima entre 374 e 24: " << distancia << endl;

    distancia = s.obtemMenorDistancia(374, 555);
    arqSaida << "Distancia minima entre 374 e 555: " << distancia << endl;
    */

    s.calcular();

    //time_t t_fim = std::time(0);
    //cout << t_fim << endl;
    //time_t t_dif = t_fim - t_inicio;
    //cout << "T-diff: " << t_dif << endl;
    fechaArquivoDeSaida();

    return 0;
}

