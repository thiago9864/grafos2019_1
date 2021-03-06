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
//    Aresta **listaPrim;
//    listaPrim= g->prim();
//    for(int i=0;i<=g->getOrdem();i++){
//        cout<<"Grupo de arestas(origem, final):"<<listaPrim[i]->getOrigemId()<<","<<listaPrim[i]->getNoAdj()<<endl;
//    }
    Aresta *largura;
    largura=g->caminho_largura(90);
    for(Aresta* a = largura; a != NULL; a = a->getProx()) {
            cout<<"Origem:"<< a->getOrigemId()<<" ";
            cout<<"Fim:"<<a->getNoAdj()<<"\n";
    }





    return 0;
}
