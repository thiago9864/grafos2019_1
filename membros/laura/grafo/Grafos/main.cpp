#include <iostream>
#include <string>
#include "Grafo.h"

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
    cout << endl;

    int indComp[g->getOrdem()];
    int idNos[g->getOrdem()];

    if(g->getDirecional() == false) {
        int numComp = g->componenteConexa(indComp, idNos);
        cout << "Numero de componentes conexas: " << numComp << endl;
        cout << endl;

        for(int i = 0; i < numComp; i++) {
            cout << "Componente " << i + 1 << ": " << endl;
            for(int j = 0; j < g->getOrdem(); j++) {
                if(indComp[j] == i) {
                    cout << idNos[j] << " ";
                }
            }
            cout << endl;
            cout << endl;
        }
    }

    Aresta arestasAGM[g->getOrdem() - 1];

    if(g->getDirecional() == false) {
        if(g->componenteConexa(indComp, idNos) == 1) {
            float pesoTotal = g->kruskal(arestasAGM);
            cout << "Arestas da arvore geradora minima: " << endl;
            for(int i = 0; i < g->getOrdem() - 1; i++) {
                cout << arestasAGM[i].getOrigem() << " ---> " << arestasAGM[i].getNoAdj() << " (" << arestasAGM[i].getPeso() << ") " << endl;

            }
            cout << endl;
            cout << "Soma dos pesos das arestas: " << pesoTotal << endl;
            cout << endl;
        }
    }

    return 0;
}
