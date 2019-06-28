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

    float pesoTotal;
    Grafo *arvoreAGM = g->kruskal(&pesoTotal);
    cout << "Arvore geradora minima: " << endl;
    cout << endl;
    arvoreAGM->imprime();
    cout << endl;
    cout << "Soma dos pesos das arestas da arvore geradora minima: " << pesoTotal << endl;
    cout << endl;

    Grafo *ind;
    No **solucao = new No*[3];
    No *n;
    for(n = g->getNo(); n != nullptr; n = n->getProx()) {
        if(n->getId() == 10) {
            solucao[0] = n;
            break;
        }
    }
    for(n = g->getNo(); n != nullptr; n = n->getProx()) {
        if(n->getId() == 13) {
            solucao[1] = n;
            break;
        }
    }
    for(n = g->getNo(); n != nullptr; n = n->getProx()) {
        if(n->getId() == 12) {
            solucao[2] = n;
            break;
        }
    }
    ind = g->subgrafoInduzido(solucao, 3);
    cout << "Subgrafo induzido: " << endl;
    cout << endl;
    ind->imprime();
    cout << endl;

    return 0;
}
