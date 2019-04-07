//
// Created by victor on 04/04/19.
//

#include "Grafo.h"

using namespace std;

Grafo::Grafo(int n_nos) {

    this->inicializa_matrix(n_nos);

}

Grafo::Grafo(string entrada, string saida) {
    this->direcional = false;
    this->ponderadoAresta = false;
    this->ponderadoNo = false;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}

Grafo::Grafo(string entrada, string saida, bool direcional) {
    this->direcional = direcional;
    this->ponderadoNo = false;
    this->ponderadoAresta = false;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}

Grafo::Grafo(string entrada, string saida, bool direcional, bool ponderadoAresta) {
    this->direcional = direcional;
    this->ponderadoNo = false;
    this->ponderadoAresta = ponderadoAresta;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}

Grafo::Grafo(string entrada, string saida, bool direcional, bool ponderadoAresta, bool ponderadoNo) {
    this->direcional = direcional;
    this->ponderadoNo = ponderadoNo;
    this->ponderadoAresta = ponderadoAresta;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}


// *** PUBLIC ***


/**
 * Imprime matriz de adjacência
 */
void Grafo::imprime() {

    int numCasas = 3;
    char fillchar = ' ';
    string espaco = " ";

    cout << "DADOS: " << endl;
    cout << "Grau: " << this->grau << endl;
    cout << "Ordem: " << this->ordem << endl;
    cout << "M: " << this->m << endl;

    cout << "MATRIZ DE ADJACENCIA: " << endl;

    cout << "    ";

    for (int i = 0; i < this->ordem; i++) {
        cout << setfill(fillchar) << setw(numCasas) << this->ids[i] << espaco;
    }

    cout << endl;

    for (int i = 0; i < this->ordem; i++) {
        cout << setfill(fillchar) << setw(numCasas) << this->ids[i] << espaco;

        for (int j = 0; j < this->ordem; j++) {
            cout << setfill(fillchar) << setw(numCasas) << this->matrix[i][j] << espaco;
        }

        cout << endl;

    }

}

/// Imprime matriz de adjacência e salva em arquivo
void Grafo::imprime(string arquivo) {

    ofstream file;
    int numCasas = 3;
    char fillchar = ' ';
    string espaco = " ";

    file.open(arquivo, ios::out);

    if (file.is_open()) {

        file << "DADOS: " << endl;
        file << "Grau: " << this->grau << endl;
        file << "Ordem: " << this->ordem << endl;
        file << "M: " << this->m << endl;

        file << "MATRIZ DE ADJACENCIA: " << endl;

        file << "    ";

        for (int i = 0; i < this->ordem; i++) {
            file << setfill(fillchar) << setw(numCasas) << this->ids[i] << espaco;
        }

        file << endl;

        for (int i = 0; i < this->ordem; i++) {
            file << setfill(fillchar) << setw(numCasas) << this->ids[i] << espaco;

            for (int j = 0; j < this->ordem; j++) {
                file << setfill(fillchar) << setw(numCasas) << this->matrix[i][j] << espaco;
            }

            file << endl;

        }
    } else {
        cout << "Output file does not open." << endl;
    }
}

/// Insere nó no grafo pelo id
void Grafo::setNo(int id) {

    if (this->findId(id) != -1) {
        //cout << "No já preenchido" << endl;
        return;
    }

    // Encontra a ultima posição livre
    int last = this->lastPos(this->ids);

    this->ids[last] = id;

}

/// Insere aresta no grafo pelo id do nó de origem, fim e o peso da aresta
void Grafo::setAresta(int idOrigem, int idFim, float peso) {

    if (idOrigem == idFim) {
        cout << "Nao e permitido self-loop" << endl;
        return;
    }

    int origem_index = this->findId(idOrigem); // Procurando nós
    int fim_index = this->findId(idFim);

    // Caso não encontre os nós
    if (origem_index == -1) {
        this->setNo(idOrigem);
    }
    if (fim_index == -1) {
        this->setNo(idFim);
    }

    this->matrix[origem_index][fim_index] = peso;

    if (!this->direcional) // Se não for direcinal adicionamos uma aresta no sentido contrário
        this->matrix[fim_index][origem_index] = peso;

    // Verificando se pode atualizar grau do Grafo

    int grauOrigem = this->getGrauNoSaida(idOrigem);    // Como ambos graus são atualizados para grafos não direcionais
    int grauFim = this->getGrauNoEntrada(idFim);        // Tanto faz verifivar o grau de saída ou entrada;

    if (grauOrigem > grauFim)
        this->atualizaGrau(grauOrigem);
    else
        this->atualizaGrau(grauFim);

    this->m++; // Atualizando numero de arestas

}

/// Insere aresta no grafo pelo id do nó de origem e fim.
void Grafo::setAresta(int idOrigem, int idFim) {
    this->setAresta(idOrigem, idFim, 1);
}

/// Retorna grau de entrada de um nó passado.
int Grafo::getGrauNoEntrada(int id){

    int no_index = this->findId(id); // Procurando nó
    int grau = 0;

    if (no_index != -1) { // Se nó for encontrado

        for (int i = 0; i < this->ordem; i++) {
            if (this->matrix[i][no_index] != 0)
                grau++;
        }
    } else { // Se não encontrar o nó
        return -1;
    }

    return grau;

}

/// Retorna grau de saída de um nó passado.
int Grafo::getGrauNoSaida(int id){

    int no_index = this->findId(id); // Procurando nó
    int grau = 0;

    if (no_index != -1) { // Se nó for encontrado

        for (int j = 0; j < this->ordem; j++) {
            if (this->matrix[no_index][j] != 0)
                grau++;
        }
    } else { // Se não encontrar o nó
        return -1;
    }

    return grau;

}


// *** PRIVATE ***


/**
 * Inicializa matriz de adjacência e vetor de ids de cada nó
 *
 * @param n_nos: Número de nós do grafo
 */
void Grafo::inicializa_matrix(int n_nos) {

    this->ordem = n_nos;

    // Intanciando matriz de adjacencia
    this->matrix = new float*[ordem];
    for (int i = 0; i < ordem; i++) {
        this->matrix[i] = new float[ordem];

        // Preenchendo com zeros a matriz
        for (int j = 0; j < ordem; j++)
            this->matrix[i][j] = 0;
    }

    //Instanciando vetor de ids dos nós
    this->ids = new int[ordem];

    for (int i; i < ordem; i++) {
        this->ids[i] = 0;
    }

}

/// Lê arquivo para inicializar o grafo com seus valores
void Grafo::leitura_arquivo(string arquivo) {

    ifstream file; // Leitura de arquivo
    int ordem = 0; // Numero de nós
    string line; // Auxilar para leitura de cada linha

    file.open(arquivo, ios::in); // Lendo arquivo de entrada

    if (file.is_open()) {

        getline(file, line); // Lendo a primeira linha com número de nós

        ordem = stoi(line); // Convertendo de string para int

        this->ordem = ordem;

        this->inicializa_matrix(ordem); // Inicializa matriz e vetor de ids

        // Percorrendo cada linha do arquivo e adicionando a variavel dados
        while (getline(file, line)) {

            istringstream str_stream(line);

            int origem, fim;
            float peso;

            // Verifica se é ponderado nas arestas
            if (this->ponderadoAresta) {

                // Lendo valores
                str_stream >> origem >> fim >> peso;

                // TODO implementar pensando que pode ser ponderado no nó

                // Inserindo nós da aresta, a verificaçao de existencia é feita pelo método
                this->setNo(origem);
                this->setNo(fim);
                this->setAresta(origem,fim,peso);

            } else {

                // Lendo valores
                str_stream >> origem >> fim;

                // TODO implementar pensando que pode ser ponderado no nó

                // Inserindo nós da aresta, a verificaçao de existencia é feita pelo método
                this->setNo(origem);
                this->setNo(fim);
                this->setAresta(origem,fim);

            }

        }

        file.close();

    } else {
        cout << "Input file does not open." << endl;
    }
}

/**
 * Encontra posição do nó na matriz com a partir do seu id.
 *
 * @param id: Id do nó a ser encontrado.
 * @return Indice onde o nó está localizado.
 */
int Grafo::findId(int id) {

    for (int i = 0; i < this->ordem; i++) {
        if (this->ids[i] == id)
            return i;
    }

    return -1;

}

/// Retorna ultima posição de um vetor
int Grafo::lastPos(int *v) {
    int i = 0;

    for (i = 0; i < this->ordem; i++) {
        if (v[i] == 0)
            return i;
    }

    return i;
}

/// Atualiza grau do grafo se o grau passado for maior que o atual.
void Grafo::atualizaGrau(int grau) {
    if (grau > this->grau)
        this->grau = grau;
}