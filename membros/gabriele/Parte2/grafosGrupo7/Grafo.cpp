/**
    Universidade Federal de Juiz de Fora
    Grafo.cpp
    Propósito: Classe que representa o grafo e contém metodos de manipulação.

    @author Thiago Almeida
    @version 2.0 27/06/19
*/

#include "Grafo.h"

/**
 * Construtor vazio
 */
Grafo::Grafo() {
    this->direcionado = false;
    this->ponderadoAresta = false;
    this->ponderadoNo = false;
    this->listaNos = NULL;
    this->terminais = NULL;
    this->numTerminais = 0;
    this->ordem = 0;
    this->numArestas = 0;
}

Grafo::Grafo(bool direcionado, bool ponderadoAresta, bool ponderadoNo){
    this->direcionado = direcionado;
    this->ponderadoAresta = ponderadoAresta;
    this->ponderadoNo = ponderadoNo;
    this->listaNos = NULL;
    this->terminais = NULL;
    this->numTerminais = 0;
    this->ordem = 0;
    this->numArestas = 0;
}

/**
 * Construtor para os arquivos de entrada e saida
 * @param formato Formato do arquivo (txt ou stp)
 * @param entrada Caminho do arquivo de entrada
 * @param saida Caminho do arquivo de saida
 */
Grafo::Grafo(string formato, string entrada, string saida) {
    this->direcionado = false;
    this->ponderadoAresta = false;
    this->ponderadoNo = false;
    this->listaNos = NULL;
    this->terminais = NULL;
    this->numTerminais = 0;
    this->ordem = 0;
    this->numArestas = 0;

    if(formato == "stp"){
        this->parseSTP(entrada);
    } else {
        this->parseTXT(entrada);
    }
}

/**
 * Construtor para os arquivos de entrada e saida e indicação de tipo do grafo
 * @param formato Formato do arquivo (txt ou stp)
 * @param entrada Caminho do arquivo de entrada
 * @param saida Caminho do arquivo de saida
 * @param direcionado Indica se o grafo é direcional (1) ou não (0)
 */
Grafo::Grafo(string formato, string entrada, string saida, bool direcionado) {
    this->direcionado = direcionado;
    this->ponderadoNo = false;
    this->ponderadoAresta = false;
    this->listaNos = NULL;
    this->terminais = NULL;
    this->numTerminais = 0;
    this->ordem = 0;
    this->numArestas = 0;

    if(formato == "stp"){
        this->parseSTP(entrada);
    } else {
        this->parseTXT(entrada);
    }

}

/**
 * Construtor para os arquivos de entrada e saida, indicação de tipo do grafo e se é ponderado nas arestas
 * @param formato Formato do arquivo (txt ou stp)
 * @param entrada Caminho do arquivo de entrada
 * @param saida Caminho do arquivo de saida
 * @param direcionado Indica se o grafo é direcional (1) ou não (0)
 * @param ponderadoAresta Indica se o grafo é ponderado nas arestas (1) ou não (0)
 */
Grafo::Grafo(string formato, string entrada, string saida, bool direcionado, bool ponderadoAresta) {
    this->direcionado = direcionado;
    this->ponderadoNo = false;
    this->ponderadoAresta = ponderadoAresta;
    this->listaNos = nullptr;
    this->terminais = nullptr;
    this->numTerminais = 0;
    this->ordem = 0;
    this->numArestas = 0;

    if(formato == "stp"){
        this->parseSTP(entrada);
    } else {
        this->parseTXT(entrada);
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
Grafo::Grafo(string formato, string entrada, string saida, bool direcionado, bool ponderadoNo, bool ponderadoAresta) {
    this->direcionado = direcionado;
    this->ponderadoNo = ponderadoNo;
    this->ponderadoAresta = ponderadoAresta;
    this->listaNos = nullptr;
    this->terminais = nullptr;
    this->numTerminais = 0;
    this->ordem = 0;
    this->numArestas = 0;

    if(formato == "stp"){
        this->parseSTP(entrada);
    } else {
        this->parseTXT(entrada);
    }

}


Grafo::~Grafo()
{
    No *vertice = listaNos;
    while(vertice != NULL)
    {
        //deleta as arestas do vertice
        Aresta *aresta = vertice->getAresta();
        while(aresta != NULL)
        {
            Aresta *prox_aresta = aresta->getProx();
            delete aresta;
            aresta = prox_aresta;
        }

        //deleta o vertice
        No *prox_vertice = vertice->getProx();
        delete vertice;
        vertice = prox_vertice;
    }
}

/**
 * Interpreta o conteudo de um arquivo txt em uma lista de adjacências
 * @param arquivo Caminho do arquivo
 */
void Grafo::parseTXT(string arquivo)
{
    ifstream inFile;
    string line;
    int num_vertices = 0;
    int id_vertice1, id_vertice2;
    float peso_aresta = 0;
    float peso_vertice1 = 0, peso_vertice2 = 0;

    //abre arquivo de entrada
    inFile.open(arquivo.c_str());

    //verifica se o arquivo foi aberto
    if (!inFile || !inFile.is_open())
    {
        cout << "Impossivel abrir o arquivo de entrada para leitura" << endl;
        cout << arquivo << endl;
        exit(1); // sai do programa se nao conseguir abrir o arquivo
    }

    //le o arquivo linha por linha
    while (getline(inFile, line))
    {
        istringstream iss_numVertices(line);
        if(num_vertices == 0){
            //obtem o numero de vertices
            iss_numVertices >> num_vertices;
        } else {

            istringstream iss_ponderado(line);

            if(ponderadoNo){
                iss_ponderado >> id_vertice1 >> peso_vertice1 >> id_vertice2 >> peso_vertice2 >> peso_aresta;
            } else {
                iss_ponderado >> id_vertice1 >> id_vertice2 >> peso_aresta;
            }

            if (!iss_ponderado.fail())
            {
                if(direcionado){
                    if(ponderadoAresta && ponderadoNo){
                        addNoEArestaPonderadaDigrafo(id_vertice1, peso_vertice1, id_vertice2, peso_vertice2, peso_aresta);
                    } else if(ponderadoAresta) {
                        addNoEArestaPonderadaDigrafo(id_vertice1, 1, id_vertice2, 1, peso_aresta);
                    } else if(ponderadoNo) {
                        addNoEArestaPonderadaDigrafo(id_vertice1, peso_vertice1, id_vertice2, peso_vertice2, 1);
                    } else {
                        addNoEArestaPonderadaDigrafo(id_vertice1, 1, id_vertice2, 1, 1);
                    }
                } else {
                    if(ponderadoAresta && ponderadoNo){
                        addNoEArestaPonderada(id_vertice1, peso_vertice1, id_vertice2, peso_vertice2, peso_aresta);
                    } else if(ponderadoAresta) {
                        addNoEArestaPonderada(id_vertice1, 1, id_vertice2, 1, peso_aresta);
                    } else if(ponderadoNo) {
                        addNoEArestaPonderada(id_vertice1, peso_vertice1, id_vertice2, peso_vertice2, 1);
                    } else {
                        addNoEArestaPonderada(id_vertice1, 1, id_vertice2, 1, 1);
                    }
                }


            }
            else
            {
                cout << "Não foi possivel ler a linha" << endl;
                cout << "[" << line << "]" << endl;
                //exit(1);
            }

            iss_ponderado.clear();
        }

    }

    cout << "---- fim da leitura -----" << endl;
    cout << ordem << " vertices adicionados" << endl;
    cout << numArestas << " arestas adicionadas" << endl;
}

/**
 * Interpreta o conteudo de um arquivo stp em uma lista de adjacências
 * @param arquivo Caminho do arquivo
 */
void Grafo::parseSTP(string arquivo)
{
    ifstream inFile;
    string line;
    string ID;
    int id_vertice1, id_vertice2;
    float peso_aresta = 0;
    float peso_vertice1 = 0, peso_vertice2 = 0;
    int num_terminais = 0;

    //abre arquivo de entrada
    inFile.open(arquivo.c_str());

    //verifica se o arquivo foi aberto
    if (!inFile || !inFile.is_open())
    {
        cout << "Impossivel abrir o arquivo de entrada para leitura" << endl;
        cout << arquivo << endl;
        exit(1); // sai do programa se nao conseguir abrir o arquivo
    }

    //le o arquivo linha por linha
    while (getline(inFile, line))
    {
        istringstream iss_ID(line);
        ID = "";

        //cai aqui se não conseguir ler o id pelo stringstream
        size_t found = line.find(" ");
        if(found != std::string::npos){
            ID = line.substr(0, found).c_str();
        }

        if(ID == "E"){

            istringstream iss_ponderado(line);

            if(ponderadoNo){
                iss_ponderado >> ID >> id_vertice1 >> peso_vertice1 >> id_vertice2 >> peso_vertice2 >> peso_aresta;
            } else {
                iss_ponderado >> ID >> id_vertice1 >> id_vertice2 >> peso_aresta;
            }

            if (!iss_ponderado.fail())
            {
                if(direcionado){
                    if(ponderadoAresta && ponderadoNo){
                        addNoEArestaPonderadaDigrafo(id_vertice1, peso_vertice1, id_vertice2, peso_vertice2, peso_aresta);
                    } else if(ponderadoAresta) {
                        addNoEArestaPonderadaDigrafo(id_vertice1, 1, id_vertice2, 1, peso_aresta);
                    } else if(ponderadoNo) {
                        addNoEArestaPonderadaDigrafo(id_vertice1, peso_vertice1, id_vertice2, peso_vertice2, 1);
                    } else {
                        addNoEArestaPonderadaDigrafo(id_vertice1, 1, id_vertice2, 1, 1);
                    }
                } else {
                    if(ponderadoAresta && ponderadoNo){
                        addNoEArestaPonderada(id_vertice1, peso_vertice1, id_vertice2, peso_vertice2, peso_aresta);
                    } else if(ponderadoAresta) {
                        addNoEArestaPonderada(id_vertice1, 1, id_vertice2, 1, peso_aresta);
                    } else if(ponderadoNo) {
                        addNoEArestaPonderada(id_vertice1, peso_vertice1, id_vertice2, peso_vertice2, 1);
                    } else {
                        addNoEArestaPonderada(id_vertice1, 1, id_vertice2, 1, 1);
                    }
                }


            }
            else
            {
                cout << "Não foi possivel ler a linha" << endl;
                cout << "[" << line << "]" << endl;
                //exit(1);
            }

            iss_ponderado.clear();
        }
        if(ID == "Terminals"){


            istringstream iss_terminais(line);
            iss_terminais >> ID >> num_terminais;
            numTerminais = 0;

            if (!iss_terminais.fail())
            {
                if(terminais == NULL){
                    //cria o vetor de ids dos terminais
                    terminais = new int[num_terminais];
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
                if(numTerminais >= num_terminais){
                    cout << "O numero de terminais presentes na instancia e maior do que o informado" << endl;
                    cout << line << endl;
                } else {
                    //adiciona um id de terminal
                    terminais[numTerminais] = id_vertice1;
                    numTerminais++;
                }
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

    cout << "---- fim da leitura -----" << endl;
    cout << ordem << " vertices adicionados" << endl;
    cout << numArestas << " arestas adicionadas" << endl;
    cout << numTerminais << " terminais adicionados" << endl << endl;
}

/**
 * ############################## METODOS AUXILIARES ##############################
 **/

/**
 * Get do ponteiro da lista de vertices
 * @return Ponteiro
 */
No* Grafo::getListaNos()
{
    return listaNos;
}

int Grafo::getOrdem()
{
    return ordem;
}
int Grafo::getNumArestas()
{
    return numArestas;
}

int Grafo::getNumTerminais()
{
    return numTerminais;
}
int* Grafo::getTerminais()
{
    return terminais;
}

bool Grafo::isDirecionado()
{
    return direcionado;
}
bool Grafo::isPonderadoAresta()
{
    return ponderadoAresta;
}
bool Grafo::isPonderadoNo()
{
    return ponderadoNo;
}

/**
 * Procura um vertice especificado
 * @param id Id do vértice
 */
No* Grafo::getNo(int id)
{
    No *p = listaNos;
    while(p != NULL)
    {
        if(p->getId() == id)
        {
            return p;
        }
        p = p->getProx();
    }
    return NULL;
}

/**
 * Procura uma aresta adjacente em um vertice
 * @param idAdjacente Id do vértice adjacente
 * @param origem Referencia de ponteiro para vertice de origem
 * @return Ponteiro para aresta, se encontrado, ou NULL
 */
Aresta* Grafo::procuraArestaAdjacente(int idAdjacente, No*& origem)
{
    Aresta *a = origem->getAresta();
    while(a != NULL)
    {
        if(a->getNoAdj() == idAdjacente)
        {
            return a;
        }
        a = a->getProx();
    }
    return NULL;
}

/**
 * Pesquisa o grafo pra existencia de aresta, dados os 2 ids dos vertices
 * @param idOrigem Id do vértice de origem
 * @param idDestino Id do vértice de destino
 * @return True, se ela existe. False senão
 */
Aresta* Grafo::getAresta(int idOrigem, int idDestino){
    No *vertice1 = getNo(idOrigem);

    if(vertice1 == NULL){
        //cout << "O vertice de origem '" << idOrigem << "' não foi encontrado" << endl;
        return NULL;
    }

    if(direcionado)
    {
        Aresta* ad = procuraArestaAdjacente(idDestino, vertice1);

        if(ad != NULL){
            return ad;
        }
    }
    else
    {
        No *vertice2 = getNo(idDestino);

        if(vertice2 == NULL){
            //cout << "O vertice de destino '" << idOrigem << "' nao foi encontrado" << endl;
            return NULL;
        }

        Aresta* a12 = procuraArestaAdjacente(idDestino, vertice1);
        Aresta* a21 = procuraArestaAdjacente(idOrigem, vertice2);

        if(a12 != NULL && a21 != NULL){
            return a12;
        }
    }

    return NULL;
}

/**
 * Remove um item da lista encadeada de arestas
 * @param verticeOrigem Referencia para o ponteiro da aresta de origem
 * @param iidDestino Id do vertice destino
 * @return True, se a aresta foi removida. False senão
 */
bool Grafo::removeItemListaAresta(No*& verticeOrigem, int idDestino)
{
    Aresta *a = verticeOrigem->getAresta();
    Aresta *ant = a;

    while(a != NULL)
    {
        if(a->getNoAdj() == idDestino)
        {
            if(a == ant)
            {
                //primeira aresta da lista
                verticeOrigem->setAresta(a->getProx());
                delete a;
            }
            else if(a->getProx() == NULL)
            {
                //ultima aresta
                verticeOrigem->setUltimaAresta(ant);
                ant->setProx(NULL);
                delete a;
            }
            else
            {
                //aresta do meio
                ant->setProx(a->getProx());
                delete a;
            }

            return true;
        }
        ant = a;
        a = a->getProx();
    }

    return false;
}

/**
 * ############################## METODOS DE ADIÇÃO ##############################
 **/


/**
 * Cria um vertice dado o id e peso dele
 * @param id Id do vértice
 * @param peso Peso do vértice
 * @return ponteiro para o vértice criado
 */
No* Grafo::criaNo(int id, float peso)
{
    No* vertice = new No();
    vertice->setId(id);
    vertice->setPeso(peso);
    vertice->setProx(NULL);
    vertice->setAresta(NULL);
    vertice->setUltimaAresta(NULL);

    if(listaNos == NULL)
    {
        listaNos = vertice;
    }
    else
    {
        ultimoNo->setProx(vertice);
    }

    //atualiza o ultimo da lista
    ultimoNo = vertice;

    ordem++;

    return vertice;
}

/**
 * Cria uma aresta dado o vertice origem e o id de destino
 * @param id Id do vértice destino
 * @param peso Peso do vértice
 * @param vertice Referência para o ponteiro do vértice de origem
 * @return ponteiro para a aresta criada
 */
Aresta* Grafo::criaAresta(int id, float peso, No*& vertice)
{
    Aresta *aresta = new Aresta();
    aresta->setOrigem(vertice->getId());
    aresta->setNoAdj(id);
    aresta->setPeso(peso);
    aresta->setProx(NULL);

    //adiciona aresta
    if(vertice->getAresta() == NULL)
    {
        //adiciona no começo a aresta criada
        vertice->setAresta(aresta);
    }
    else
    {
        //adiciona na ultima posicao a aresta criada
        Aresta *a = vertice->getUltimaAresta();
        a->setProx(aresta);
    }

    //atualiza a ultima posicao de adjacencia do vértice
    vertice->setUltimaAresta(aresta);

    return aresta;
}

/**
 * Adiciona uma aresta ponderada e seus vértices, se necessário.
 * @param id Id do vértice origem
 * @param pesoVertice Peso do vértice origem
 * @param idAresta Id do vértice destino
 * @param pesoVerticeAresta Peso do vértice destino
 * @param pesoAresta Peso da aresta
 */
void Grafo::addNoEArestaPonderada(int id, float pesoVertice, int idAresta, float pesoVerticeAresta, float pesoAresta)
{
    No *vertice1;
    No *vertice2;

    //checa se tem algum self loop
    if(id == idAresta)
    {
        cout << "Não sao permitidos self loops!" << endl;
        exit(1);
    }

    //verifica se já existem os vertices
    vertice1 = getNo(id);
    vertice2 = getNo(idAresta);

    //cria vertice1 se não existir
    if(vertice1 == NULL)
    {
        vertice1 = criaNo(id, pesoVertice);
    }

    //cria vertice2 se não existir
    if(vertice2 == NULL)
    {
        vertice2 = criaNo(idAresta, pesoVerticeAresta);
    }

    //cria aresta de ida (1->2)
    criaAresta(idAresta, pesoAresta, vertice1);

    //cria aresta de volta (2->1)
    criaAresta(id, pesoAresta, vertice2);

    //atualiza grau dos vertices de ida
    vertice1->addGrauSaida();
    vertice2->addGrauEntrada();

    //atualiza grau dos vertices de volta
    vertice2->addGrauSaida();
    vertice1->addGrauEntrada();

    //as arestas direcionais aqui contribuem como uma num grafo simples
    numArestas++;
}

/**
 * Adiciona um arco ponderado e seus vértices, se necessário.
 * @param id Id do vértice origem
 * @param pesoVertice Peso do vértice origem
 * @param idAresta Id do vértice destino
 * @param pesoVerticeAresta Peso do vértice destino
 * @param pesoAresta Peso da aresta
 */
void Grafo::addNoEArestaPonderadaDigrafo(int id, float pesoVertice, int idAresta, float pesoVerticeAresta, float pesoAresta)
{
    No *verticeSaida;
    No *verticeEntrada;

    //checa se tem algum self loop
    if(id == idAresta)
    {
        cout << "Não sao permitidos self loops!" << endl;
        exit(1);
    }

    //verifica se já existe o vertice
    verticeSaida = getNo(id);
    verticeEntrada = getNo(idAresta);

    //cria vertice se não existir
    if(verticeSaida == NULL)
    {
        verticeSaida = criaNo(id, pesoVertice);
    }

    //cria vertice se não existir
    if(verticeEntrada == NULL)
    {
        verticeEntrada = criaNo(idAresta, pesoVerticeAresta);
    }

    //cria aresta direcional (1->2)
    criaAresta(idAresta, pesoAresta, verticeSaida);

    //atualiza grau dos vertices
    verticeSaida->addGrauSaida();
    verticeEntrada->addGrauEntrada();

    //contabiliza a aresta criada
    numArestas++;
}

/**
 * Posição do nó na matriz de adjacência.
 * @param id Id do nó a ser procurado
 * @return posição do nó na matriz
*/
int Grafo::noIdToPos(int id)
{
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
int Grafo::noPosToId(int pos)
{
    int id;
    int i = 0;

    for (No* n = this->listaNos; n != nullptr; n = n->getProx()) {
        if (i == pos)
            return n->getId();
        i++;
    }
    return -1;
}


/// Retorna matriz de adjacência do grafo.
float** Grafo::getMatrizAdj()
{
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

/*========================================================================*/
/*=================== Metodos pedidos na atividade 2 =====================*/
/*========================================================================*/


/**
 * Adiciona um vertice ao grafo dado o id e o peso
 * @param id Id do vértice destino
 * @param peso Peso do vértice
 * @return True se conseguiu criar o vértice, senão False
 */
bool Grafo::adicionaNo(int id, float peso)
{
    if(getNo(id) == NULL)
    {
        criaNo(id, peso);
        cout << "O vertice '" << id << "' foi adicionado" << endl;
        return true;
    }
    else
    {
        cout << "O vertice '" << id << "' ja existe." << endl;
        return false;
    }

}

/**
 * Adiciona uma aresta (ou arco) ponderada (o) e seus vértices, se necessário.
 * @param id Id do vértice origem
 * @param pesoVertice Peso do vértice origem
 * @param idAresta Id do vértice destino
 * @param pesoVerticeAresta Peso do vértice destino
 * @param pesoAresta Peso da aresta
 * @return True se adicionado, senão False
 */
bool Grafo::adicionaAresta(int idOrigem, float pesoIdOrigem, int idDestino, float pesoIdDestino, float pesoAresta)
{
    if(getAresta(idOrigem, idDestino) != NULL)
    {
        cout << "A aresta (" << idOrigem << ", " << idDestino << ") ja existe." << endl;
        return false;
    }
    else if(direcionado)
    {
        //processa como grafo direcional
        addNoEArestaPonderadaDigrafo(idOrigem, pesoIdOrigem, idDestino, pesoIdDestino, pesoAresta);
        cout << "A aresta (" << idOrigem << ", " << idDestino << ") foi adicionada" << endl;
        return true;
    }
    else
    {
        //processa como grafo simples
        addNoEArestaPonderada(idOrigem, pesoIdOrigem, idDestino, pesoIdDestino, pesoAresta);
        cout << "A aresta (" << idOrigem << ", " << idDestino << ") foi adicionada" << endl;
        return true;
    }
}

/**
 * Remove um vertice do grafo dado o id.
 * @param id Id do vértice origem
 * @return True se removido, senão False
 */
bool Grafo::removeNo(int id)
{
    No *verticeRemover = getNo(id);
    if(verticeRemover == NULL)
    {
        cout << "O vertice '" << id << "' nao foi encontrado" << endl;
        return false;
    }

    //remove as arestas de saida
    Aresta *a = verticeRemover->getAresta();
    while(a != NULL)
    {
        removeAresta(id, a->getNoAdj());
        a = verticeRemover->getAresta();
    }

    //remove as arestas de entrada
    No *v = listaNos;
    while(v != NULL)
    {
        if(v->getId() != id)
        {
            removeAresta(v->getId(), id);
        }
        v = v->getProx();
    }

    if(verticeRemover->getGrauEntrada() == 0 && verticeRemover->getGrauSaida() == 0)
    {
        //a partir daqui o vertice já está isolado
        v = listaNos;
        No *ant = v;

        while(v != NULL)
        {
            if(v->getId() == id)
            {
                if(v == ant)
                {
                    //primeiro nó da lista
                    listaNos = v->getProx();
                    delete v;
                }
                else if(v->getProx() == NULL)
                {
                    //ultimo nó da lista
                    ultimoNo = ant;
                    ant->setProx(NULL);
                    delete v;
                }
                else
                {
                    //aresta do meio
                    ant->setProx(v->getProx());
                    delete v;
                }

                //atualiza a ordem do grafo
                ordem--;
                cout << "o vertice '" << id << "' foi removido" << endl;
                return true;
            }
            ant = v;
            v = v->getProx();
        }
    }
    else
    {
        cout << "o vertice '" << id << "' nao foi isolado completamente" << endl;
    }

    return false;
}

/**
 * Remove uma aresta do grafo dado o id de origem e destino.
 * @param idOrigem Id do vértice origem
 * @param idDestino Id do vértice destino
 * @return True se removido, senão False
 */
bool Grafo::removeAresta(int idOrigem, int idDestino)
{
    No *vertice1 = getNo(idOrigem);
    No *vertice2 = getNo(idDestino);
    Aresta *ant;
    Aresta *prox;

    if(vertice1 == NULL){
        cout << "O vertice de origem '" << idOrigem << "' nao foi encontrado" << endl;
    }
    if(vertice2 == NULL){
        cout << "O vertice de destino '" << idDestino << "' nao foi encontrado" << endl;
    }

    //sair do metodo porque não tem um dos 2 vertices
    if(vertice1 == NULL || vertice2 == NULL){
        return false;
    }

    if(direcionado)
    {
        if(removeItemListaAresta(vertice1, idDestino))
        {
            //ajusta grau
            vertice1->removeGrauSaida();
            vertice2->removeGrauEntrada();
            numArestas--;
            return true;
        }
    }
    else
    {

        bool aresta12 = removeItemListaAresta(vertice1, idDestino);
        bool aresta21 = removeItemListaAresta(vertice2, idOrigem);
        if(aresta12)
        {
            //ajusta grau
            vertice1->removeGrauSaida();
            vertice2->removeGrauEntrada();
        }
        if(aresta21)
        {
            //ajusta grau
            vertice2->removeGrauSaida();
            vertice1->removeGrauEntrada();
        }
        if(aresta12 && aresta21)
        {
            numArestas--;
            return true;
        }
    }

    return false;
}


/**
 * Gera o grafo complementar.
 * @return Grafo complementar do atual, NULL se falhar
 */
Grafo* Grafo::geraGrafoComplementar(){

    Grafo* complementar = new Grafo();
    complementar->direcionado = this->direcionado;

    int ids[this->ordem];
    int c = 0;

    for (No* n = this->listaNos; n != nullptr; n = n->getProx(), c++) {
        ids[c] = n->getId();
    }

    for (int i = 0; i < c; i++) {   // Preenchendo nós
        complementar->adicionaNo(ids[i], 1);
    }

    for (int i = 0; i < c; i++) {
        for (int j = 0; j < c; j++) {

            if (i == j) continue;

            Aresta* a = this->getAresta(ids[i], ids[j]);

            if (a == nullptr) {     // Se não encontrou aresta no original ela irá entrar no complementar
                complementar->adicionaAresta(ids[i], 1, ids[j], 1, a->getPeso());
            }

        }
    }

    return complementar;

}




/*========================================================================*/
/*================== Metodos pedidos na primeira etapa ===================*/
/*========================================================================*/




/**
 * Executa uma busca em largura no grafo.
 * @param id Id do elemento a encontrar
 * @return
 */
Aresta* Grafo::caminhamentoEmLargura(int id)
{
    CaminhoLargura *caminho = new CaminhoLargura(this);
    return caminho->busca(id);
}

/**
 * Executa uma busca em profundidade no grafo pra encontrar o caminho entre 2 vértices.
 * @param idOrigem Id do elemento origem
 * @param idDestino Id do elemento destino
 * @return
 */
Aresta* Grafo::caminhamentoEmProfundidade(int idOrigem, int idDestino)
{
    CaminhoProfundidade *caminho = new CaminhoProfundidade(this);
    return caminho->busca(idOrigem, idDestino);
}

/**
 * Identifica as componentes conexas do grafo
 * @return
 */
int Grafo::listarComponentesConexas(int* indComp, int* idNos)
{
    ComponentesConexas *conexas = new ComponentesConexas(this);
    return conexas->componenteConexa(indComp, idNos);
}

/**
 * Identifica as componentes fortemente conexas do grafo (direcional)
 * @return
 */
int Grafo::listarComponentesFortementeConexas()
{
    return NULL;
}


/**
 * Executa uma ordenação topológica do grafo (direcional)
 * @return
 */
int* Grafo::ordenacaoTopologica()
{
    // Confirmando se o grafo é direcional
    if (!this->direcionado) return nullptr;
    OrdenacaoTopologica ord(this); // Inicializa Objeto de ordenação topológica
    int* ordenados = ord.ordenacao(); // Recebe vetor com os nós ordenados
    return ordenados;
}

Aresta* Grafo::caminhoMinimoDijkstra(int origem, int destino)
{
    Dijkstra* dijkstra = new Dijkstra(this);
    return dijkstra->caminhoMinimo(origem, destino);
}

Aresta* Grafo::getCaminhoMinimoFloyd(int origem, int destino)
{
    Floyd* floyd = new Floyd(this, this->getMatrizAdj());
    return floyd->getCaminhoAresta(origem, destino);
}

float Grafo::getDistanciaFloyd(int origem, int destino)
{
    Floyd* floyd = new Floyd(this, this->getMatrizAdj());
    return floyd->getDistancia(origem,destino);
}

Grafo* Grafo::KruskalAGM(float *soma){
    Kruskal *kruskal = new Kruskal(this);
    return kruskal->gerar(soma);
}

Grafo* Grafo::PrimAGM(float *soma){
    Prim *prim = new Prim(this);
    return prim->gerar(soma);
}


Grafo* Grafo::subgrafoInduzido(No **solucao, int tam)
{
    Aresta **subInduzido = new Aresta*[this->m]; // Vetor que recebe as arestas que farão parte do subgrafo induzido.
    int contAresta = 0;
    Aresta *arestaAdj;
    bool verifica[ordem][ordem]; // Matriz auxiliar que será utilizada para que não haja repetição de arestas adicionadas a 'subInduzido'.
    int idNos[ordem]; // Vetor que será preenchido com os ids dos nós do grafo.
    vetorIdNos(idNos);

    for(int i = 0; i < ordem; i++) {
        for(int j = 0; j < ordem; j++) {
            verifica[i][j] = false;
        }
    }

    for(int i = 0; i < tam; i++) { // Encontra as arestas do grafo que posuem ambas as extremidades em 'solucao' e as adiciona ao vetor 'subInduzido'.
        int a = encontraIndice(idNos, solucao[i]->getId());
        for(arestaAdj = solucao[i]->getAresta(); arestaAdj != nullptr; arestaAdj = arestaAdj->getProx()) {
            int noAd = arestaAdj->getNoAdj();
            int b = encontraIndice(idNos, noAd);

            for(int j = 0; j < tam; j++) {
                if(noAd == solucao[j]->getId()) {
                    if(verifica[a][b] != true) {
                       subInduzido[contAresta] = arestaAdj;
                       contAresta++;
                       verifica[a][b] = true;
                       verifica[b][a] = true;
                       break;
                    }
                }
            }
        }
    }

    Grafo *h = new Grafo(); // Cria-se o grafo que irá receber as arestas de 'subInduzido'.
    h->ponderadoAresta = true;
    h->m = 0;
    h->grau = 0;
    for(int i = 0; i < contAresta; i++) { // Cria em 'h' as arestas com as mesmas características das presentes em 'subInduzido'.
        int origem = subInduzido[i]->getOrigem();
        int fim = subInduzido[i]->getNoAdj();
        float peso = subInduzido[i]->getPeso();

        h->setNo(origem);
        h->setNo(fim);
        h->setAresta(origem, fim, peso);
    }

    for(int i = 0; i < tam; i++) { // Adiciona ao grafo os nós que não foram adicionados anteriormente (possivelmente nós isolados).
        if(h->getNo(solucao[i]->getId()) == nullptr) {
            h->setNo(solucao[i]->getId());
        }
    }

    return h;
}


/**
 * Implementação do algoritmo guloso
 */
ResultadoGuloso Grafo::guloso(){
    time_t inicio = time(0);
    ResultadoGuloso res;

    /////// rodar aqui o guloso ////////

    ////////////////////////////////////

    time_t fim = time(0);
    time_t dif_tempo = fim - inicio;

    res.custo = 2205.5;
    res.tempo = dif_tempo;
    return res;
}

ResultadoGuloso Grafo::gulosoExtra(){
    time_t inicio = time(0);

    /////// rodar aqui o guloso ////////

    ResultadoGuloso res;
    CustomSteiner *cs = new CustomSteiner(this);
    Grafo *h = cs->steiner_antigo();
    float custo = 0;

    if(h != NULL) {
        Utils u;
        u.gerarArquivoGraphViz(h, "../saidas/customsteiner.gv");
        //calcula o custo da arvore
        No*p = h->getListaNos();
        while(p != NULL){
            Aresta *a = p->getAresta();
            while(a != NULL){
                custo += a->getPeso();
                a = a->getProx();
            }
            p = p->getProx();
        }
    } else {
        custo = 0;
    }
    ////////////////////////////////////

    time_t fim = time(0);
    time_t dif_tempo = fim - inicio;

    res.custo = custo / 2;//divido por 2 porque o codigo acima conta 2 vezes a aresta, por ser não direcionado
    res.tempo = dif_tempo;

    return res;
}


/*========================================================================*/
/*================== Metodos pedidos na segunda etapa ====================*/
/*========================================================================*/


/**
 * Implementação do algoritmo guloso randomizado
 */
ResultadoGuloso Grafo::gulosoRandomizado(float alfa, int maxIteracoes){
    time_t inicio = time(0);
    ResultadoGuloso res;

    /////// rodar aqui o guloso randomizado ////////

    ////////////////////////////////////////////////

    time_t fim = time(0);
    time_t dif_tempo = fim - inicio;

    res.custo = 2205.5;
    res.tempo = dif_tempo;
    return res;
}

/**
 * Implementação do algoritmo guloso reativo
 */
ResultadoGuloso Grafo::gulosoRandomizadoReativo(int maxIteracoes){
    time_t inicio = time(0);
    ResultadoGuloso res;

    /////// rodar aqui o guloso randomizado reativo ////////

    ////////////////////////////////////////////////////////

    time_t fim = time(0);
    time_t dif_tempo = fim - inicio;

    res.custo = 2205.5;
    res.tempo = dif_tempo;
    return res;
}

//verifica se o grafo é conexo
bool Grafo::getConexo() {
    int* indComp;
    int* idNos;

    indComp = new int[this->getOrdem()];
    idNos = new int[this->getOrdem()];
    this->vetorIdNos(idNos);

    for (int i = 0; i < this->getOrdem(); i++) {
        indComp[i] = 0;
    }

    this->conexo = this->componenteConexa(indComp,idNos) == 1;

    return this->conexo;

}
