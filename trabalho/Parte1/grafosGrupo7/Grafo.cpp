/**
    Universidade Federal de Juiz de Fora
    Grafo.cpp
    Propósito: Representa o grafo.

    @author Victor Aquiles
    @version 1.0 01/04/19
*/

#include <iostream>
#include "Grafo.h"

using namespace std;


/**
 * Construtor vazio
 */
Grafo::Grafo() {
    this->direcional = false;
    this->ponderadoAresta = false;
    this->ponderadoNo = false;
    this->listaNos = nullptr;
    this->terminais = nullptr;
    this->numTerminais = 0;
}

/**
 * Construtor para os arquivos de entrada e saida
 * @param formato Formato do arquivo (txt ou stp)
 * @param entrada Caminho do arquivo de entrada
 * @param saida Caminho do arquivo de saida
 */
Grafo::Grafo(string formato, string entrada, string saida) {
    this->direcional = false;
    this->ponderadoAresta = false;
    this->ponderadoNo = false;
    this->listaNos = nullptr;
    this->terminais = nullptr;
    this->numTerminais = 0;

    if(formato == "stp"){
        this->leitura_arquivo_stp(entrada);
    } else {
        this->leitura_arquivo(entrada);
    }
}

/**
 * Construtor para os arquivos de entrada e saida e indicação de tipo do grafo
 * @param formato Formato do arquivo (txt ou stp)
 * @param entrada Caminho do arquivo de entrada
 * @param saida Caminho do arquivo de saida
 * @param direcional Indica se o grafo é direcional (1) ou não (0)
 */
Grafo::Grafo(string formato, string entrada, string saida, bool direcional) {
    this->direcional = direcional;
    this->ponderadoNo = false;
    this->ponderadoAresta = false;
    this->listaNos = nullptr;
    this->terminais = nullptr;
    this->numTerminais = 0;

    if(formato == "stp"){
        this->leitura_arquivo_stp(entrada);
    } else {
        this->leitura_arquivo(entrada);
    }

}

/**
 * Construtor para os arquivos de entrada e saida, indicação de tipo do grafo e se é ponderado nas arestas
 * @param formato Formato do arquivo (txt ou stp)
 * @param entrada Caminho do arquivo de entrada
 * @param saida Caminho do arquivo de saida
 * @param direcional Indica se o grafo é direcional (1) ou não (0)
 * @param ponderadoAresta Indica se o grafo é ponderado nas arestas (1) ou não (0)
 */
Grafo::Grafo(string formato, string entrada, string saida, bool direcional, bool ponderadoAresta) {
    this->direcional = direcional;
    this->ponderadoNo = false;
    this->ponderadoAresta = ponderadoAresta;
    this->listaNos = nullptr;
    this->terminais = nullptr;
    this->numTerminais = 0;

    if(formato == "stp"){
        this->leitura_arquivo_stp(entrada);
    } else {
        this->leitura_arquivo(entrada);
    }

}

/**
 * Construtor para os arquivos de entrada e saida, indicação de tipo do grafo e se é ponderado nos nós ou arestas
 * @param formato Formato do arquivo (txt ou stp)
 * @param entrada Caminho do arquivo de entrada
 * @param saida Caminho do arquivo de saida
 * @param direcional Indica se o grafo é direcional (1) ou não (0)
 * @param ponderadoNo Indica se o grafo é ponderado nos nós (1) ou não (0)
 * @param ponderadoAresta Indica se o grafo é ponderado nas arestas (1) ou não (0)
 */
Grafo::Grafo(string formato, string entrada, string saida, bool direcional, bool ponderadoNo, bool ponderadoAresta) {
    this->direcional = direcional;
    this->ponderadoNo = ponderadoNo;
    this->ponderadoAresta = ponderadoAresta;
    this->listaNos = nullptr;
    this->terminais = nullptr;
    this->numTerminais = 0;

    if(formato == "stp"){
        this->leitura_arquivo_stp(entrada);
    } else {
        this->leitura_arquivo(entrada);
    }

}

Grafo::~Grafo() {
    delete this->listaNos;
}


/*========================================================================*/
/*=================== Metodos pedidos na atividade 1 =====================*/
/*========================================================================*/



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

/**
 * Interpreta o conteudo de um arquivo stp em uma lista de adjacências
 * @param arquivo Caminho do arquivo
 */
void Grafo::leitura_arquivo_stp(string arquivo)
{
    ifstream inFile;
    string line;
    string ID;
    int origem, fim;
    float peso = 0;
    int num_terminais = 0;

    //abre arquivo de entrada
    inFile.open(arquivo.c_str());

    //verifica se o arquivo foi aberto
    if (!inFile || !inFile.is_open())
    {
        cout << "Impossivel abrir o arquivo de entrada para leitura" << endl;
        exit(1); // sai do programa se nao conseguir abrir o arquivo
    }

    //le o arquivo linha por linha
    while (getline(inFile, line))
    {
        istringstream iss_ID(line);
        ID = "";

        if ((iss_ID >> ID))
        {
            //cai aqui se não conseguir ler o id pelo stringstream
            size_t found = line.find(" ");
            if(found != std::string::npos){
                ID = line.substr(0, found).c_str();
            }
        }

        if(ID == "E"){

            istringstream iss_ponderado(line);
            iss_ponderado >> ID >> origem >> fim >> peso;

            if (!iss_ponderado.fail())
            {
                //aresta ponderada com peso long int
                this->ponderadoAresta = true;

                // Inserindo nós da aresta, a verificaçao de existencia é feita pelo método
                this->setNo(origem);
                this->setNo(fim);
                this->setAresta(origem, fim, peso);
            }
            else
            {
                cout << "Não foi possivel ler a aresta" << endl;
                cout << "[" << line << "]" << endl;
                //exit(1);
            }

            iss_ponderado.clear();
        }
        if(ID == "Terminals"){

            int n_terminais;
            istringstream iss_terminais(line);
            iss_terminais >> ID >> n_terminais;

            if (!iss_terminais.fail())
            {
                if(terminais == NULL){
                    //cria o vetor de ids dos terminais
                    terminais = new int[n_terminais];
                }
            }
            else
            {
                cout << "Não foi possivel ler a quantidade de terminais" << endl;
                cout << line << endl;
                exit(1);
            }

            iss_terminais.clear();
        }
        if(ID == "T"){

            string a;
            int id_vertice1;

            istringstream iss_terminal(line);
            iss_terminal >> ID >> id_vertice1;

            if (!iss_terminal.fail())
            {
                //adiciona um id de terminal
                terminais[num_terminais] = id_vertice1;
                num_terminais++;
            }
            else
            {
                cout << "Não foi possivel ler o terminal" << endl;
                cout << line << endl;
                exit(1);
            }

            iss_terminal.clear();
        }

    }

    numTerminais = num_terminais;

    cout << "---- fim da leitura -----" << endl;
    cout << ordem << " vertices adicionados" << endl;
    cout << m << " arestas adicionadas" << endl;
    cout << num_terminais << " terminais adicionados" << endl << endl;
}


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

bool Grafo::isDirecionado() {
    return direcional;
}
bool Grafo::isPonderadoAresta() {
    return ponderadoAresta;
}
bool Grafo::isPonderadoNo() {
    return ponderadoNo;
}

No* Grafo::getNo(int id) {
    No *n = nullptr;

    // Percorrendo lista de nós até encontrar o desejado
    for (n = this->listaNos; n != nullptr && n->getId() != id; n = n->getProx());

    return n;
}

No* Grafo::getListaNos() {
    return this->listaNos;
}

Aresta* Grafo::getAresta(int idOrigem, int idFim) {
    No *n = this->getNo(idOrigem); // Encontrando nó de origem

    // Se encontrar nó inicia a busca se não retorna nullptr
    if (n != nullptr) {
        Aresta* a = n->getAresta();

        // Procurando aresta com nó passado, se encontrar o retorna, se não retorna nullptr
        for (; a != nullptr && a->getNoAdj() != idFim; a = a->getProx());

        return a;

    } else {
        return nullptr;
    }

}

int Grafo::getOrdem() {
    return this->ordem;
}
int Grafo::getGrau() {
    return this->grau;
}
int Grafo::getNumArestas() {
    return this->m;
}


bool Grafo::getConexo() {
    int* indComp;
    int* idNos;
    ComponentesConexas *conexas = new ComponentesConexas(this);

    indComp = new int[this->getOrdem()];
    idNos = new int[this->getOrdem()];
    conexas->vetorIdNos(idNos);

    for (int i = 0; i < this->getOrdem(); i++) {
        indComp[i] = 0;
    }

    this->conexo = conexas->componenteConexa(indComp, idNos) == 1;

    return this->conexo;

}


/*========================================================================*/
/*=================== Metodos pedidos na atividade 2 =====================*/
/*========================================================================*/



void Grafo::setAresta(int idOrigem, int idFim) {
    // Verifica se o grafo é ponderado ou não da aresta para colocar um valour default
    if (!this->ponderadoAresta)
        this->setAresta(idOrigem, idFim, -1);
    else
        this->setAresta(idOrigem, idFim, 1);

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
    for (; list != nullptr; list = list->getProx()) {

        if (list->getId() == idOrigem)
            origem = list;

        if (list->getId() == idFim)
            fim = list;

        // Evitando percorrer até o final desnecessáriamente
        if (origem != nullptr && fim != nullptr) break;

    }

    if (origem != nullptr && fim != nullptr) {
        //Aresta *origem_fim = new Aresta(idFim, peso);
        Aresta *origem_fim = new Aresta(idFim, idOrigem, peso);//thiago

        if (origem->setAresta(origem_fim))
            fim->aumentaGrauEntrada();

    } else {
        cout << "No nao encontrado" << endl;
        return;
    }

    // Se o grafo não for direcional o nó de chegada também recebe uma aresta
    if (!this->direcional) {
        //Aresta *fim_origem = new Aresta(idOrigem, peso);
        Aresta *fim_origem = new Aresta(idOrigem, idFim, peso);//thiago

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


void Grafo::setNo(int id) {
    this->setNo(id, -1);
}

void Grafo::setNo(int id, float peso) {

    No* no = new No(id, peso);

    No *list = this->listaNos;

    if (list == nullptr) {
        this->listaNos = no;
        this->ordem = 1; // Inicializa a ordem
        return;
    }

    // Percorrendo lista de nós até encontrar o ultimo
    for (; list->getProx() != nullptr; list = list->getProx()) {
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
    for (; no != nullptr; no = no->getProx()) {
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


Grafo* Grafo::getComplementar() {

    Grafo* complementar = new Grafo();
    complementar->direcional = this->direcional;

    int ids[this->ordem];
    int c = 0;

    for (No* n = this->listaNos; n != nullptr; n = n->getProx(), c++) {
        ids[c] = n->getId();
    }

    for (int i = 0; i < c; i++) {   // Preenchendo nós
        complementar->setNo(ids[i]);
    }

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


// *** FUNCIONALIDADES ***

// *** MATRIZ DE ADJACÊNCIA ***

/// Retorna matriz de adjacência do grafo.
float** Grafo::getMatrizAdj() {
    float** matrizAdj;
    int n = this->ordem;
    int origem;
    int destino;

    // Inicializando matriz
    matrizAdj = new float*[n];
    for (int i = 0; i < n; i++) {
        matrizAdj[i] = new float[n];
        for (int j = 0; j < n; j++) {
            matrizAdj[i][j] = -1;
        }
    }

    // Preenchendo com peso das arestas
    No* no = this->listaNos;
    for(; no != nullptr; no = no->getProx()) {

        origem = this->noIdToPos(no->getId());
        Aresta* a = no->getAresta();

        for (; a != nullptr; a = a->getProx()) {
            destino = this->noIdToPos(a->getNoAdj());
            matrizAdj[origem][destino] = a->getPeso();
        }

    }

    return matrizAdj;

}

/**
 * Posição do nó na matriz de adjacência.
 * @param id Id do nó a ser procurado
 * @return posição do nó na matriz
*/
int Grafo::noIdToPos(int id) {
    int pos = 0;

    for (No* n = this->listaNos; n != nullptr; n = n->getProx()) {
        if (n->getId() == id)
            return pos;
        pos++;
    }
    return -1;
}

/**
 * Id do nó da posição passada na matriz de adjacência.
 * @param pos Posição do nó a ser procurado
 * @return id do nó procurado
*/
int Grafo::noPosToId(int pos) {
    int id;
    int i = 0;

    for (No* n = this->listaNos; n != nullptr; n = n->getProx()) {
        if (i == pos)
            return n->getId();
        i++;
    }
    return -1;
}


Aresta* Grafo::getCaminhoFloyd(int origem, int destino)
{
    Floyd* floyd = new Floyd(this, this->getMatrizAdj());
    return floyd->getCaminhoAresta(origem, destino);
}

float Grafo::getDistanciaFloyd(int origem, int destino)
{
    Floyd* floyd = new Floyd(this, this->getMatrizAdj());
    return floyd->getDistancia(origem,destino);
}

Aresta* Grafo::getCaminhoDijkstra(int origem, int destino)
{
    Dijkstra* dijkstra = new Dijkstra(this);
    return dijkstra->caminhoMinimo(origem, destino);
}


Aresta* Grafo::buscaEmProfundidade(int idOrigem, int idDestino)
{
    CaminhoProfundidade *caminho = new CaminhoProfundidade(this);
    return caminho->busca(idOrigem, idDestino);
}

/**
 * Ordenação topológica do grafo
 * @return vetor com os vertices ordenados
 */
int* Grafo::ordenacaoTopologica()
{

    // Confirmando se o grafo é direcional
    if (!this->direcional) return nullptr;

    OrdenacaoTopologica ord(this); // Inicializa Objeto de ordenação topológica

    int* ordenados = ord.ordenacao(); // Recebe vetor com os nós ordenados

    return ordenados;

}

/**
 * Caminho largura
 * estou retornando uma lista do caminho até chegar ao no desejado
 * @return ponteiro para lista de arestas
 */
Aresta* Grafo::caminho_largura(int id){
    CaminhoLargura *caminho = new CaminhoLargura(this);
    return caminho->busca(id);
}


/**
 * Componentes conexas
 */
int Grafo::componenteConexa(int* indComp, int* idNos)
{
    ComponentesConexas *conexas = new ComponentesConexas(this);
    return conexas->componenteConexa(indComp, idNos);
}


Grafo* Grafo::KruskalAGM(float *soma){
    Kruskal *kruskal = new Kruskal(this);
    return kruskal->gerar(soma);
}

Grafo* Grafo::PrimAGM(){
    Prim *prim = new Prim(this);
    return prim->gerar();
}

/*========================================================================*/
/*=================== Metodos pedidos na atividade 3 =====================*/
/*========================================================================*/


/**
 * Implementação do algoritmo guloso
 */


/*========================================================================*/
/*=================== Metodos pedidos na atividade 4 =====================*/
/*========================================================================*/


/**
 * Implementação do algoritmo guloso randomizado
 */

/**
 * Implementação do algoritmo guloso reativo
 */
