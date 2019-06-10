#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
//#include "Grafo.h"

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

int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 6) {
        cout << "Argumentos passados invalidos";
        return 0;
    }

    //Grafo *g;

    //verifica o formato do arquivo
    string arquivoEntrada = argv[1];
    std::size_t found = arquivoEntrada.find("stp");
    string formato = "txt";

    if(found != std::string::npos){
        formato = "stp";
    } 

    // Verificando a quantidade de argumentos passados
    /*
    if (argc == 6) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
    } else if (argc == 5) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]), stoi(argv[4]));
    } else if (argc == 4) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]));
    } else {
        g = new Grafo(formato, argv[1], argv[2]);
    }
    */

    //menu da aplicação
    //inicializa log
    string arquivoSaida = argv[2];
    iniciaArquivoSaida(arquivoSaida);

    arqSaida << "**** Trabalho Grafos 2019.1 - Grupo 7 ****" << endl << endl;

    arqSaida << "## Parametros recebidos ##" << endl;
    arqSaida << "arquivoEntrada: " + arquivoEntrada << endl;
    arqSaida << "arquivoSaida: " + arquivoSaida << endl;
    
    if(stoi(argv[3])){
        arqSaida << "isDirecionado: Sim" << endl;
    } else {
        arqSaida << "isDirecionado: Não" << endl;
    }

    if(stoi(argv[5])){
        arqSaida << "isPonderadoVertice: Sim" << endl;
    } else {
        arqSaida << "isPonderadoVertice: Não" << endl;
    }

    if(stoi(argv[4])){
        arqSaida << "isPonderadoAresta: Sim" << endl;
    } else {
        arqSaida << "isPonderadoAresta: Não" << endl;
    }

    arqSaida << endl;

    fechaArquivoDeSaida();
    return 0;
}