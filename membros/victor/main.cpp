//
// Created by victor on 22/03/19.
//

#include <iostream>
#include <string>
#include "Grafo.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 1 || argc > 3) {
        cout << "Argumentos passados invalidos";

        return 0;
    }

    string str(argv[1]); // Passando para string

    Grafo* g = new Grafo(argv[1]);

    g->imprime();

    // To-do: Salvar resultados no argv[2]
    // To-do: Utilizar tag do argv[3]

    return 0;
}
