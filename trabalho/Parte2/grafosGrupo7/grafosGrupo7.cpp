#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "Log.h"
#include "Utils.h"
#include "Grafo.h"

/* 
Linha de comando pra rodar

MAC/LINUX:  clear && g++ -std=c++11 *.cpp -o grafosGrupo7 && ./grafosGrupo7 ../instancias/pequenas/hc7p.stp ../data/saida_hc7p.txt 0 0 1
WINDOWS:    cls & g++ -std=c++11 *.cpp -o grafosGrupo7 & grafosGrupo7.exe ../instancias/pequenas/hc7p.stp ../data/saida_hc7p.txt 0 0 1
*/

using namespace std;

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

    /* 
    Utils u;
    u.imprime(g);
    u.gerarArquivoGraphViz(g, "../data/grafo.gv");
    */

    //menu da aplicação
    //inicializa log
    string arquivoSaida = argv[2];

    Log::getInstance().iniciaArquivoSaida(arquivoSaida);
    
    Log::getInstance().line("**** Trabalho Grafos 2019.1 - Grupo 7 ****");

    Log::getInstance().line("\n## Membros ##");
    Log::getInstance().line("Laura Polverari");
    Log::getInstance().line("Gabriele Cesar");
    Log::getInstance().line("Thiago Almeida");
    Log::getInstance().line("Victor Aquiles\n");

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

   
    return 0;
}
