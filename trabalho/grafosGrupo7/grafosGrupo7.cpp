#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "Log.h"

#include "Grafo.h"

/* 
Linha de comando pra rodar

*** txt ***
UNIX (macOS / Linux): clear && g++ -std=c++11 *.cpp -o grafosGrupo7 && ./grafosGrupo7 ../data/entrada2.txt ../data/saida.txt 0 0 1
WINDOWS: cls & g++ -std=c++11 *.cpp -o grafosGrupo7 & grafosGrupo7.exe ../data/entrada2.txt ../data/saida.txt 0 0 1

*** stp ***
UNIX (macOS / Linux): clear && g++ -std=c++11 *.cpp -o grafosGrupo7 && ./grafosGrupo7 ../data/bipe2p.stp ../data/saida.txt 0 0 1
WINDOWS: cls & g++ -std=c++11 *.cpp -o grafosGrupo7 & grafosGrupo7.exe ../data/bipe2p.stp ../data/saida.txt 0 0 1


*** Resultados ***
Instancia  | Custo da arvore
bipe2p.stp | 5616

*/

using namespace std;

/*===============================================*/
/********* Controle do arquivo de Saida **********/
/*===============================================*/




/*
https://stackoverflow.com/questions/10150468/how-to-redirect-cin-and-cout-to-files
*/

int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 6) {
        cout << "Argumentos passados invalidos";
        return 0;
    }

    Grafo *g;

    //verifica o formato do arquivo
    string arquivoEntrada = argv[1];
    std::size_t found = arquivoEntrada.find("stp");
    string formato = "txt";

    if(found != std::string::npos){
        formato = "stp";
    } 


    // Verificando a quantidade de argumentos passados
    
    if (argc == 6) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
    } else if (argc == 5) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]), stoi(argv[4]));
    } else if (argc == 4) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]));
    } else {
        g = new Grafo(formato, argv[1], argv[2]);
    }


    //menu da aplicação
    //inicializa log
    string arquivoSaida = argv[2];

    Log::getInstance().iniciaArquivoSaida(arquivoSaida);
    
    Log::getInstance().line("**** Trabalho Grafos 2019.1 - Grupo 7 ****");

    Log::getInstance().line("## Parametros recebidos ##");
    Log::getInstance().line("arquivoEntrada: " + arquivoEntrada);
    Log::getInstance().line("arquivoSaida: " + arquivoSaida);
    
    if(stoi(argv[3])){
        Log::getInstance().line("isDirecionado: Sim");
    } else {
        Log::getInstance().line("isDirecionado: Não");
    }

    if(stoi(argv[5])){
        Log::getInstance().line("isPonderadoVertice: Sim");
    } else {
        Log::getInstance().line("isPonderadoVertice: Não");
    }

    if(stoi(argv[4])){
        Log::getInstance().line("isPonderadoAresta: Sim");
    } else {
        Log::getInstance().line("isPonderadoAresta: Não");
    }

    Log::getInstance().line("\n");

    string cmd;
    int int_cmd1, int_cmd2;
    Aresta *caminho;

    while(cmd != "0"){
        Log::getInstance().line("## MENU ##\n");

        Log::getInstance().line("Digite o número correspondente a opção desejada");
        Log::getInstance().line("0: Sair do programa");
        Log::getInstance().line("1: Caminhamento em Largura");
        Log::getInstance().line("2: Caminhamento em Profundidade");
        Log::getInstance().line("3: Componentes Fortemente Conexas (para grafo orientado)");
        Log::getInstance().line("4: Ordenação Topológica (para grafo orientado)");
        Log::getInstance().line("5: Dijkstra: Caminho Mínimo (para grafos ou digrafos ponderados ou não)");
        Log::getInstance().line("6: Floyd: Caminho Mínimo (para grafos ou digrafos ponderados ou não)");
        Log::getInstance().line("7: Prim: Árvore Geradora Mínima (para grafos não orientados ponderados ou não)");
        Log::getInstance().line("8: Kruskal: Árvore Geradora Mínima (para grafos não orientados ponderados ou não)");
        cin >> cmd;

        if(cmd == "1"){
            Log::getInstance().line("\n## Caminhamento em Largura ##\n");
            Log::getInstance().line("Digite o id do vértice de destino");

            cin >> int_cmd1;

            caminho = g->caminho_largura(int_cmd1);
            Log::getInstance().line("Procura caminho até "+to_string(int_cmd2)+".");
            if(caminho != NULL){
                Log::getInstance().line("Encontrado.");
                Aresta *aux = caminho;
                while(aux != NULL){
                    Log::getInstance().line("Aresta: (" + to_string(aux->getNoOrigem()) + ", " + to_string(aux->getNoAdj()) + ") peso: " + to_string(aux->getPeso())+")");
                    aux = aux->getProx();
                }
                Log::getInstance().line("\n");
            } else {
                Log::getInstance().line("Não foi encontrado.");
            }
        }

        if(cmd == "2"){
            Log::getInstance().line("\n## Caminhamento em Profundidade ##\n");
            Log::getInstance().line("Digite o id do vértice de origem e destino separados por um espaço");

            cin >> int_cmd1 >> int_cmd2;

            caminho = g->buscaEmProfundidade(int_cmd1, int_cmd2);
            Log::getInstance().line("Procura caminho entre "+to_string(int_cmd1)+"-"+to_string(int_cmd2)+".");
            if(caminho != NULL){
                Log::getInstance().line("Encontrado.");
                Aresta *aux = caminho;
                while(aux != NULL){
                    Log::getInstance().line("Aresta: (" + to_string(aux->getNoOrigem()) + ", " + to_string(aux->getNoAdj()) + ") peso: " + to_string(aux->getPeso())+")");
                    aux = aux->getProx();
                }
                Log::getInstance().line("\n");
            } else {
                Log::getInstance().line("Não foi encontrado.");
            }
        }

        if(cmd == "3"){
            Log::getInstance().line("\n## Componentes Fortemente Conexas (para grafo orientado) ##\n");
        }

        if(cmd == "4"){
            Log::getInstance().line("\n## Ordenação Topológica (para grafo orientado) ##\n");
        }

        if(cmd == "5"){
            Log::getInstance().line("\n## Dijkstra: Caminho Mínimo (para grafos ou digrafos ponderados ou não) ##\n");
            Log::getInstance().line("Digite o id do vértice de origem e destino separados por um espaço");

            cin >> int_cmd1 >> int_cmd2;
            caminho = g->getCaminhoDijkstra(int_cmd1, int_cmd2);
            Log::getInstance().line("Procura caminho entre "+to_string(int_cmd1)+"-"+to_string(int_cmd2)+".");
            float custo = 0;
            if(caminho != NULL){
                Log::getInstance().line("Encontrado.");
                Aresta *aux = caminho;
                while(aux != NULL){
                    Log::getInstance().line("Aresta: (" + to_string(aux->getNoOrigem()) + ", " + to_string(aux->getNoAdj()) + ") peso: " + to_string(aux->getPeso())+")");
                    custo += aux->getPeso();
                    aux = aux->getProx();
                }
                Log::getInstance().line("\n");
                Log::getInstance().line("Custo: " + to_string(custo));
            } else {
                Log::getInstance().line("Não foi encontrado.");
            }
        }

        if(cmd == "6"){
            Log::getInstance().line("\n## Floyd: Caminho Mínimo (para grafos ou digrafos ponderados ou não) ##\n");
        }

        if(cmd == "7"){
            Log::getInstance().line("\n## Prim: Árvore Geradora Mínima (para grafos não orientados ponderados ou não) ##\n");
        }

        if(cmd == "8"){
            Log::getInstance().line("\n## Kruskal: Árvore Geradora Mínima (para grafos não orientados ponderados ou não) ##\n");
        }
    }

    return 0;
}
