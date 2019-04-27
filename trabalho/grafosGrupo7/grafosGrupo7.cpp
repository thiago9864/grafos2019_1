#include <iostream>
#include <string>
#include "Grafo.h"

/* Linha de comando pra rodar
UNIX (macOS / Linux): clear && g++ -std=c++11 *.cpp -o grafosGrupo7 && ./grafosGrupo7 ../data/input.txt saida.txt 0 0 1
*/

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

    Grafo *p = g->getComplementar();

    p->imprime();

    //teste da busca em profundidade (Thiago)
    ListaArestas *caminho = g->buscaEmProfundidade(10, 25);
    if(caminho != NULL){
        cout << "caminho 10-25 encontrado" << endl;
        Aresta *arrCaminho = caminho->getArrayArestas();
        for(int i=0; i < caminho->getTamanho(); i++)
        {
            cout << "Aresta #" << i << " (" << arrCaminho[i].getNoOrigem() << ", " << arrCaminho[i].getNoAdj() << ") peso: " << arrCaminho[i].getPeso() << endl;
        }
        cout << endl;
    }

    return 0;
}