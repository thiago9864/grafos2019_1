//
// Created by victor on 22/03/19.
//

#include "Grafo.h"

// *******  PUBLIC  ********

Grafo::Grafo() {}

/**
     * Constroi grafo a partir do um arquivo passado como parâmetro
     * com a seguinte estrutura em cada linha:
     *
     * Vertice de origem [espaço] Vertice adjacente [espaço] Peso da aresta
     *
     * @param arquivo Caminho do arquivo
     */
Grafo::Grafo(string arquivo) {

    int n_nos;
    vector<vector<string>> dados;

    // Lendo arquivo e obtendo numero de nós
    n_nos = this->leitura_arquivo(&dados, arquivo);

    // Instanciando o grafo inicial
    this->grafo = new ListSuc(n_nos);

    No no_saida;
    No no_chegada;

    vector<string> it;
    for (int i = 0; i < dados.size(); i++) {
        it = dados[i];

        // Valores da linha do arquivo
        no_saida.nome = stoi(it[0]);
        no_chegada.nome = stoi(it[1]);
        no_chegada.valor = stoi(it[2]);

        // Procurando em qual posição irá entrar a aresta
        for (int i = 0; i < n_nos; i++) {

            // Vetor de posição i
            NoVector *vec = &this->grafo->at(i);

            if (vec->empty()) { // Se a lista esta vazia

                // Adiciona a primeira aresta para esse nó
                vec->push_back(no_saida);
                vec->push_back(no_chegada);

                break;

            } else if (vec->begin()->nome == no_saida.nome) {

                // Adiciona uma nova aresta se o nó já estiver no grafo
                vec->push_back(no_chegada);

                break;
            }
        }
    }
}

void Grafo::insert_no(int nome) {
    No node;
    NoVector vec;

    node.nome = nome;

    vec.push_back(node);

    this->grafo->push_back(vec);

}

/**
     * Imprime grafo no formato de lista de incidência:
     *
     * Vertice de origem --> Vertice adjacente (Peso) --> ...
     */
void Grafo::imprime() {
    for (int i = 0; i < this->grafo->size(); i++) {
        NoVector v = this->grafo->at(i);

        cout << v[0].nome << " ---> ";

        for (int j = 1; j < v.size() - 1; j++) {
            cout << v[j].nome << " (" << v[j].valor << ") ---> ";
        }

        if (v.size() > 1) {
            int p = v.size() - 1;
            cout << v[p].nome << " (" << v[p].valor << ")" << endl;
        }

    }
}

// *******  PRIVATE  *********

void Grafo::split(vector<string> *v, string str, char c) {

    string s = "";

    for (char i : str) {
        if (i != c) {
            s += i; // Montando a string
        } else {
            v->push_back(s); // Adicionando no vetor
            s.clear();
        }
    }

    // Adicionando ultima string
    if (!s.empty())
        v->push_back(s);

}

/**
     * Lê arquivo passado como parâmetro e retorna seus dados de arestas e quantidades de nós.
     *
     * @param dados Vetor onde os dados de arestas serão armazenados.
     * @param arquivo Caminho do arquivo onde serão lido os dados.
     * @return Número de nós do grafo.
     */
int Grafo::leitura_arquivo(vector<vector<string>> *dados, string arquivo) {

    ifstream file; // Leitura de arquivo
    int n_nos = 0; // Numero de nós
    string line; // Auxilar para leitura de cada linha

    file.open(arquivo, ios::in); // Lendo arquivo de entrada

    if (file.is_open()) {

        getline(file, line); // Lendo a primeira linha com número de nós

        n_nos = stoi(line); // Convertendo de string para int

        vector<string> split_str; // Auxiliar para split de cada linha

        // Percorrendo cada linha do arquivo e adicionando a variavel dados
        while (getline(file, line)) {

            split(&split_str, line, ' ');

            dados->push_back(split_str);

            split_str.clear();

        }

        file.close();

        return n_nos;

    } else {
        cout << "File does not open." << endl;

        return -1;
    }
}