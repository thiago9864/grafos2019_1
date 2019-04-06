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

    if (argc == 6) {
        g = new Grafo(argv[1], argv[2], argv[3], argv[4], argv[5]);
    } else if (argc == 5) {
        g = new Grafo(argv[1], argv[2], argv[3], argv[4]);
    } else if (argc == 4) {
        g = new Grafo(argv[1], argv[2], argv[3]);
    } else {
        g = new Grafo(argv[1], argv[2]);
    }

    g->imprime();

    return 0;
}