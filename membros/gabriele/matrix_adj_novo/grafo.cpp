#include <iostream>
#include"grafo.h"

using namespace std;

void Grafo::leitura_arquivo(string arquivo) {

    ifstream file; // Leitura de arquivo
    int ordem = 0; // Numero de n�s
    string line; // Auxilar para leitura de cada linha

    file.open(arquivo, ios::in); // Lendo arquivo de entrada

    if (file.is_open()) {

        getline(file, line); // Lendo a primeira linha com n�mero de n�s

        ordem = stoi(line); // Convertendo de string para int

        this->ordem = ordem;

        // Percorrendo cada linha do arquivo e adicionando a variavel dados
        while (getline(file, line)) {

            istringstream str_stream(line);

            int origem, fim;
            float peso;

            // Verifica se � ponderado nas arestas
            if (this->ponderadoAresta) {

                // Lendo valores
                str_stream >> origem >> fim >> peso;

                // TODO implementar pensando que pode ser ponderado no n�

                // Inserindo n�s da aresta, a verifica�ao de existencia � feita pelo m�todo
                this->setNo(origem);
                this->setNo(fim);
                this->setAresta(origem,fim,peso);

            } else {

                // Lendo valores
                str_stream >> origem >> fim;

                // TODO implementar pensando que pode ser ponderado no n�

                // Inserindo n�s da aresta, a verifica�ao de existencia � feita pelo m�todo
                this->setNo(origem);
                this->setNo(fim);
                this->setAresta(origem,fim);

            }

        }

        file.close();

    } else {
        cout << "File does not open." << endl;
    }
}

