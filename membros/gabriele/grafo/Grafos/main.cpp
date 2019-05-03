#include <iostream>
#include <string>
#include "grafo.h"
#include"aresta.h"
using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 6) {
        cout << "Argumentos passados invalidos";

        return 0;
    }

    Grafo *g;

    // Verificando a quantidade de argumentos passados
    if (argc == 6) {
        g = new Grafo(argv[1], argv[2], stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
    } else if (argc == 5) {
        g = new Grafo(argv[1], argv[2], stoi(argv[3]), stoi(argv[4]));
    } else if (argc == 4) {
        g = new Grafo(argv[1], argv[2], stoi(argv[3]));
    } else {
        g = new Grafo(argv[1], argv[2]);
    }
    g->imprime();
    Aresta *largura;
    cout<<"criou aresta e vai entrar em caminho\n";
    largura=g->caminho_largura(24);
    cout<<"vai entrar no while main\n";
    while(largura!=NULL){
        cout<<"Origem:"<< largura->getOrigemId();
        cout<<"Fim:"<<largura->getNoId();
        cout<<"-----\n";
        if(largura->getNoId()!=24){
            largura=largura->getProx();
        }
        else{
            break;
        }
    }




    return 0;
}
