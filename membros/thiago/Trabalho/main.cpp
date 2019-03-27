#include <iostream>
#include <string>
#include "FileManager.h"

using namespace std;

/**
Prototipo de codigo pra avaliacao

LINHA DE COMANDO PRA RODAR: 
g++ main.cpp -o main && ./main entrada.txt saida.txt

**/

int main(int argc, char *argv[])
{
    string arquivoEntrada, arquivoSaida;
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

    FileManager fs(arquivoEntrada);
    cout << "Arq Entrada: " << fs.abrir() << endl;
    cout << "Arq Saida: " << arquivoSaida << endl;

    return 0;
}
