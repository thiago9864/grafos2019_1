//
// Created by victor on 01/04/19.
//

#include <iostream>
#include "Grafo.h"

using namespace std;


Grafo::Grafo() {
    this->direcional = false;
    this->ponderadoAresta = false;
    this->ponderadoNo = false;
    this->listaNos = nullptr;
}

Grafo::Grafo(bool direcional, bool ponderadoAresta, bool ponderadoNo) {
    this->direcional = direcional;
    this->ponderadoAresta = ponderadoAresta;
    this->ponderadoNo = ponderadoNo;
    this->listaNos = nullptr;
}

Grafo::Grafo(string entrada, string saida) {
    this->direcional = false;
    this->ponderadoAresta = false;
    this->ponderadoNo = false;
    this->listaNos = nullptr;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}

Grafo::Grafo(string entrada, string saida, bool direcional) {
    this->direcional = direcional;
    this->ponderadoNo = false;
    this->ponderadoAresta = false;
    this->listaNos = nullptr;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}

Grafo::Grafo(string entrada, string saida, bool direcional, bool ponderadoAresta) {
    this->direcional = direcional;
    this->ponderadoNo = false;
    this->ponderadoAresta = ponderadoAresta;
    this->listaNos = nullptr;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}

Grafo::Grafo(string entrada, string saida, bool direcional, bool ponderadoNo, bool ponderadoAresta) {
    this->direcional = direcional;
    this->ponderadoNo = ponderadoNo;
    this->ponderadoAresta = ponderadoAresta;
    this->listaNos = nullptr;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}

Grafo::~Grafo() {
    delete this->listaNos;
}


// *** PUBLIC ***

/**
     * Imprime na tela grafo no formato de lista de adjacência:
     *
     * DADOS:
     * Grau: valor
     * Ordem: valor
     * M: valor
     *
     * LISTA DE ADJACENCIA:
     * Vertice de origem --> Vertice adjacente (Peso) --> ...
     */
void Grafo::imprime() {
    cout << "DADOS: " << endl;
    cout << "Grau: " << this->grau << endl;
    cout << "Ordem: " << this->ordem << endl;
    cout << "M: " << this->m << endl;

    cout << "LISTA DE ADJACENCIA: " << endl;
    for (No* n = this->listaNos; n != nullptr; n = n->getProx()) {

        cout << n->getId() << " ---> ";

        for (Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) {
            // Se for ponderado nas arestas é imprimido o peso
            if (ponderadoAresta) {
                if (a->getProx() != nullptr)
                    cout << a->getNoAdj() << " (" << a->getPeso() << ") ---> ";
                else
                    cout << a->getNoAdj() << " (" << a->getPeso() << ")";
            } else {
                if (a->getProx() != nullptr)
                    cout << a->getNoAdj() << " ---> ";
                else
                    cout << a->getNoAdj();
            }
        }

        cout << endl;

    }
}

/**
     * Imprime na tela grafo no formato de lista de adjacência:
     *
     * DADOS:
     * Grau: valor
     * Ordem: valor
     * M: valor
     *
     * LISTA DE ADJACENCIA:
     * Vertice de origem --> Vertice adjacente (Peso) --> ...
     *
     * @param arquivo: Caminho do arquivo onde será gravada a impressão
     */
void Grafo::imprime(string arquivo) {

    ofstream file;

    file.open(arquivo, ios::out);

    if (file.is_open()) {

        file << "DADOS: " << endl;
        file << "Grau: " << this->grau << endl;
        file << "Ordem: " << this->ordem << endl;
        file << "M: " << this->m << endl;

        file << "LISTA DE ADJACENCIA: " << endl;
        for (No *n = this->listaNos; n != nullptr; n = n->getProx()) {

            file << n->getId() << " ---> ";

            for (Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) {
                // Se for ponderado nas arestas é imprimido o peso
                if (ponderadoAresta) {
                    if (a->getProx() != nullptr)
                        file << a->getNoAdj() << " (" << a->getPeso() << ") ---> ";
                    else
                        file << a->getNoAdj() << " (" << a->getPeso() << ")";
                } else {
                    if (a->getProx() != nullptr)
                        file << a->getNoAdj() << " ---> ";
                    else
                        file << a->getNoAdj();
                }
            }

            file << endl;

        }
    } else {
        cout << "Output file does not open." << endl;
    }
}

int Grafo::getNoPos(int id) {
    int c = 0;
    for (No* n = this->listaNos; n->getId() != id; n = n->getProx(), c++);
    return c;
}

// *** GETTERS E SETTERS ***


void Grafo::setNo(int id, float peso) {

    No* no = new No(id, peso);

    No *list = this->listaNos;

    if (list == nullptr) {
        this->listaNos = no;
        this->ordem = 1; // Inicializa a ordem
        return;
    }

    // Percorrendo lista de nós até encontrar o ultimo
    for (list; list->getProx() != nullptr; list = list->getProx()) {
        if (list->getId() == no->getId()) {
            //cout << "No com mesmo id ja inserido" << endl;
            return;
        }
    }

    // Certificando se o nó já não foi inserido
    if (list->getId() != no->getId()) {
        list->setProx(no);
        this->ordem++; // Aumentando a ordem
    }

}

void Grafo::setNo(int id) {
    this->setNo(id, -1);
}

void Grafo::setAresta(int idOrigem, int idFim, float peso) {
    No * list = this->listaNos;
    No * origem = nullptr;
    No * fim = nullptr;

    // Evitando self loops
    if (idOrigem == idFim) {
        cout << "Nao e permitido self-loop" << endl;
        return;
    }

    // Percorrendo lista de nós até encontrar os nós que irão receber a aresta
    for (list; list != nullptr; list = list->getProx()) {

        if (list->getId() == idOrigem)
            origem = list;

        if (list->getId() == idFim)
            fim = list;

        // Evitando percorrer até o final desnecessáriamente
        if (origem != nullptr && fim != nullptr) break;

    }

    if (origem != nullptr && fim != nullptr) {
        Aresta *origem_fim = new Aresta(idFim, peso);

        if (origem->setAresta(origem_fim))
            fim->aumentaGrauEntrada();

    } else {
        cout << "No nao encontrado" << endl;
        return;
    }

    // Se o grafo não for direcional o nó de chegada também recebe uma aresta
    if (!this->direcional) {
        Aresta *fim_origem = new Aresta(idOrigem, peso);

        if (fim->setAresta(fim_origem))
            origem->aumentaGrauEntrada();

        // Atualizando o grau do grafo

        // Como ambos graus são atualizados para grafos não direcionais
        // Tanto faz verifivar o grau de saída ou entrada;
        int grauOrigem = origem->getGrauEntrada();
        int grauFim = fim->getGrauEntrada();

        if (grauOrigem > grauFim)
            this->atualizaGrau(grauOrigem);
        else
            this->atualizaGrau(grauFim);

    }

    // Atualizando grau do grafo

    int grauOrigem = origem->getGrauSaida();
    int grauFim = fim->getGrauEntrada();

    if (grauOrigem > grauFim)
        this->atualizaGrau(grauOrigem);
    else
        this->atualizaGrau(grauFim);

    this->m++;

}

void Grafo::setAresta(int idOrigem, int idFim) {
    // Verifica se o grafo é ponderado ou não da aresta para colocar um valour default
    if (!this->ponderadoAresta)
        this->setAresta(idOrigem, idFim, -1);
    else
        this->setAresta(idOrigem, idFim, 1);

}


No* Grafo::getNo(int id) {
    No *n = nullptr;

    // Percorrendo lista de nós até encontrar o desejado
    for (n = this->listaNos; n != nullptr && n->getId() != id; n = n->getProx());

    return n;
}

No* Grafo::getNo() {
    return this->listaNos;
}

Aresta* Grafo::getAresta(int idOrigem, int idFim) {
    No *n = this->getNo(idOrigem); // Encontrando nó de origem

    // Se encontrar nó inicia a busca se não retorna nullptr
    if (n != nullptr) {
        Aresta* a = n->getAresta();

        // Procurando aresta com nó passado, se encontrar o retorna, se não retorna nullptr
        for (a; a != nullptr && a->getNoAdj() != idFim; a = a->getProx());

        return a;

    } else {
        return nullptr;
    }

}

int Grafo::getOrdem() {return this->ordem; }

bool Grafo::getDirecional() { return this->direcional; }

int Grafo::getM() { return this->m; }

Grafo* Grafo::getComplementar() {

    Grafo* complementar = new Grafo();
    complementar->direcional = this->direcional; // Terá a mesma orientação do grafo original

    int ids[this->ordem];   // vetor com ids dos nós
    int c = 0;

    for (No* n = this->listaNos; n != nullptr; n = n->getProx(), c++) {
        ids[c] = n->getId();
    }

    for (int i = 0; i < c; i++) {   // Preenchendo nós
        complementar->setNo(ids[i]);
    }

    // Preenchendo todas as arestas complementares
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < c; j++) {

            if (i == j) continue;

            Aresta* a = this->getAresta(ids[i], ids[j]);

            if (a == nullptr) {     // Se não encontrou aresta no original ela irá entrar no complementar
                complementar->setAresta(ids[i], ids[j]);
            }

        }
    }

    return complementar;

}

int* Grafo::ordenacaoTopologica() {

    // Confirmando se o grafo é direcional
    if (!this->direcional) return nullptr;

    OrdenacaoTopologica ord(this->ordem, this->listaNos); // Inicializa Objeto de ordenação topológica

    int* ordenados = ord.ordenacao();                   // Recebe vetor com os nós ordenados

    return ordenados;

}

// *** REMOÇÃO ***

void Grafo::removeAresta(int idOrigem, int idFim) {
    No *origem = this->getNo(idOrigem);  // Encontrando nó de inicio da aresta
    No *fim = this->getNo(idFim);        // Caso seja necessário manipular o nó de destino

    bool removeu = false;

    if (origem != nullptr && fim != nullptr) {

        removeu = origem->removeAresta(idFim); // Removendo aresta do nó de origem
        if (removeu)
            fim->diminuiGrauEntrada();   // Diminuindo grau de entrada do fim

        // Se o grafo não for direcional removemos também a aresta que indica a "volta"
        if (!this->direcional) {

            if (fim != nullptr)
                removeu = fim->removeAresta(idOrigem);
                if (removeu)
                    origem->diminuiGrauEntrada();
        }

    }

    this->atualizaGrau();

}

void Grafo::removeNo(int id) {
    No *no = this->listaNos;
    No *ant;

    bool encontrou = false;
    int grauNo;

    // Percorrendo lista de nos a fim de encontrar o no desejado
    for (no; no != nullptr; no = no->getProx()) {
        if (no->getId() == id) {
            encontrou = true;
            break;
        }
        ant = no;
    }

    // Se o nó foi encontrado é retirado o nó e colocado os seguintes para o nó anterior
    if (encontrou) {

        grauNo = no->getGrauSaida();

        No *prox = no->getProx();
        bool removeu = false;

        if (ant == no)
            this->listaNos = prox;     // Se o nó for o primeiro reiniciamos a sequencia a partir do próximo
        else
            ant->setProx(prox);        // Senão colocamos o seguinte no anterior

        no->setProx(nullptr);          // Evita apagar o nó subsequente
        delete no;

        // Inicia remoção de arestas ligadas a tal nó removido
        for (No *n = this->listaNos; n != nullptr; n = n->getProx()) {
            removeu = n->removeAresta(id);

            if (removeu) {
                this->m--;             // Diminuindo número de arestas se foi removido

                if (!this->direcional) // Se não for direcional temos que diminuir o grau de entrada
                    n->diminuiGrauEntrada();
            }
        }

        if (this->direcional)          // Diminuindo arestas que saiam do nó removido (direcional)
            this->m -= grauNo;

        this->atualizaGrau();
        this->ordem--;

    }

}

// *** PRIVATE ***

/// Atualiza grau a partir de um grau passado como parametro
void Grafo::atualizaGrau(int grau) {
    if (grau > this->grau)
        this->grau = grau;
}

/// Atualiza grau percorrendo todos os nós do grafo e procura pelo maior grau
void Grafo::atualizaGrau() {
    int max = this->listaNos->getGrauSaida();

    for (No *no = this->listaNos; no != nullptr; no = no->getProx()) {
        if (max < no->getGrauSaida())
            max = no->getGrauSaida();

        if (max < no->getGrauEntrada())
            max = no->getGrauEntrada();
    }

    this->grau = max;

}

void Grafo::leitura_arquivo(string arquivo) {

    ifstream file; // Leitura de arquivo
    int n_nos = 0; // Numero de nós
    string line; // Auxilar para leitura de cada linha

    file.open(arquivo, ios::in); // Lendo arquivo de entrada

    if (file.is_open()) {

        getline(file, line); // Lendo a primeira linha com número de nós

        n_nos = stoi(line); // Convertendo de string para int

        //this->ordem = n_nos;

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

