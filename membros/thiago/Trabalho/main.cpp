#include <iostream>
#include <string>
#include "LeitorGrafo.h"
#include "Log.h"

using namespace std;

/**
Prototipo de codigo pra avaliacao

LINHA DE COMANDO PRA RODAR: 
clear && g++ main.cpp LeitorGrafo.cpp Log.cpp ObjGrafo.cpp -o main && ./main entrada.txt saida.txt

**/

int main(int argc, char *argv[])
{
    string arquivoEntrada, arquivoSaida;
    Log log;
    //verifica a quantidade de parametros recebidos
    /*
    if(argc < 3){
        cout << "Numero de parametros insuficiente. use Trabalho <arq entrada> <arq saida>" << endl;
        return 0;
    }

    //parametros obrigatorios
    arquivoEntrada = argv[1];
    arquivoSaida = argv[2];
    */

    arquivoEntrada = "entrada.txt";
    arquivoSaida = "saida.txt";

    LeitorGrafo leitorGrafo(arquivoEntrada);


    log.logHeader("Interpreta o grafo e salva na memória");
    leitorGrafo.parse();
    log.logHeader("Imprime o grafo");
    leitorGrafo.imprimir();

    return 0;
}
