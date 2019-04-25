#include "Grafo.h"

Grafo::Grafo(bool _direcional, int _ponderado)
{
    direcional = _direcional;
    ponderado = _ponderado;
    ordem = -1;
    numArestas = 0;
    listaNos = NULL;
}

Grafo::~Grafo()
{
    No *vertice = listaNos;
    while(vertice != NULL)
    {
        //deleta as arestas do vertice
        Aresta *aresta = vertice->getAdjacente();
        while(aresta != NULL)
        {
            Aresta *prox_aresta = aresta->getProximo();
            delete aresta;
            aresta = prox_aresta;
        }

        //deleta o vertice
        No *prox_vertice = vertice->getProximo();
        delete vertice;
        vertice = prox_vertice;
    }
}

/**
 * Esse metodo faz a leitura do arquivo txt
 * parametro: nomeArquivo (recebe o nome do arquivo de entrada)
 * encapsulamento: public
 **/
void Grafo::parse(string nomeArquivo)
{
    ifstream inFile;
    string line;
    int a, b;
    float c;

    //abre arquivo de entrada
    inFile.open(nomeArquivo.c_str());

    //verifica se o arquivo foi aberto
    if (!inFile || !inFile.is_open())
    {
        cout << "Impossivel abrir o arquivo de entrada para leitura" << endl;
        exit(1); // sai do programa se nao conseguir abrir o arquivo
    }

    //le o arquivo linha por linha
    while (getline(inFile, line))
    {
        istringstream iss(line);

        if(ordem == -1)
        {
            //obtem o numero de vertices (nós) contido na primeira linha do arquivo
            iss >> ordem;
        }
        else
        {
            if(ponderado == 0)
            {
                //o grafo não é ponderado
                if (!(iss >> a >> b))
                {
                    cout << "Erro de leitura para o grafo não ponderado!" << endl;
                    exit(1); // sai do programa se houver algum erro de leitura
                }
                if(direcional == 1)
                {
                    //processa como grafo direcional
                    addNoEArestaPonderadaDigrafo(a, 0, b, 0, 0);
                }
                else
                {
                    //processa como grafo simples
                    addNoEArestaPonderada(a, 0, b, 0, 0);
                }

            }
            if(ponderado == 1)
            {
                //o grafo é ponderado nas arestas
                if (!(iss >> a >> b >> c))
                {
                    cout << "Erro de leitura para o grafo ponderado nas arestas!" << endl;
                    exit(1); // sai do programa se houver algum erro de leitura
                }
                if(direcional == 1)
                {
                    //processa como grafo direcional
                    addNoEArestaPonderadaDigrafo(a, 0, b, 0, c);
                }
                else
                {
                    //processa como grafo simples
                    addNoEArestaPonderada(a, 0, b, 0, c);
                }
            }
        }
    }
}

/**
 * ############################## METODOS AUXILIARES ##############################
 **/

No* Grafo::getGrafo()
{
    return listaNos;
}

/**
 * Esse metodo procura o nó dado o id
 * parametro: id (id do vertice)
 * encapsulamento: private
 **/
No* Grafo::procuraNo(int id)
{
    No *p = listaNos;
    while(p != NULL)
    {
        if(p->getID() == id)
        {
            return p;
        }
        p = p->getProximo();
    }
    return NULL;
}

/**
 * Esse metodo procura uma aresta adjacente em um no especificado
 * parametro: idAdjacente (id do no adjacente)
 * parametro: origem (ponteiro para o no origem)
 * encapsulamento: private
 **/
Aresta* Grafo::procuraArestaAdjacente(int idAdjacente, No*& origem)
{
    Aresta *a = origem->getAdjacente();
    while(a != NULL)
    {
        if(a->getNoAdjacente() == idAdjacente)
        {
            return a;
        }
        a = a->getProximo();
    }
    return NULL;
}

/**
 * Pesquisa o grafo pra existencia de aresta, dados os 2 ids dos vertices e o peso
 * parametro: idOrigem (id de origem da aresta)
 * parametro: idDestino (id de destino da aresta)
 * parametro: peso (peso da aresta)
 * encapsulamento: private
 **/
bool Grafo::arestaExiste(int idOrigem, int idDestino){
    No *vertice1 = procuraNo(idOrigem);

    if(vertice1 == NULL){
        cout << "O vertice de origem '" << idOrigem << "' não foi encontrado" << endl;
        return false;
    }

    if(direcional == 1)
    {
        Aresta* ad = procuraArestaAdjacente(idDestino, vertice1);

        if(ad != NULL){
            return true;
        }
    }
    else
    {
        No *vertice2 = procuraNo(idDestino);

        if(vertice2 == NULL){
            cout << "O vertice de destino indicado não foi encontrado" << endl;
            return false;
        }

        Aresta* a12 = procuraArestaAdjacente(idDestino, vertice1);
        Aresta* a21 = procuraArestaAdjacente(idOrigem, vertice2);

        if(a12 != NULL || a21 != NULL){
            return true;
        }
    }

    return false;
}

/**
 * Esse metodo remove um item da lista encadeada de arestas
 * parametro: verticeOrigem (referencia para o ponteiro da aresta de origem)
 * parametro: idDestino (id do vertice destino)
 * encapsulamento: private
 **/
bool Grafo::removeItemListaAresta(No*& verticeOrigem, int idDestino)
{
    Aresta *a = verticeOrigem->getAdjacente();
    Aresta *ant = a;

    while(a != NULL)
    {
        if(a->getNoAdjacente() == idDestino)
        {
            if(a == ant)
            {
                //primeira aresta da lista
                verticeOrigem->setAdjacente(a->getProximo());
                delete a;
            }
            else if(a->getProximo() == NULL)
            {
                //ultima aresta
                verticeOrigem->setUltimaAdjacente(ant);
                ant->setProximo(NULL);
                delete a;
            }
            else
            {
                //aresta do meio
                ant->setProximo(a->getProximo());
                delete a;
            }

            return true;
        }
        ant = a;
        a = a->getProximo();
    }

    return false;
}


/**
 * ############################## METODOS DE ADIÇÃO ##############################
 **/


/**
 * Esse metodo cria um vertice (nó) dado o id dele
 * parametro: id (id do vertice)
 * parametro: listaNos (ponteiro para lista de nós do grafo)
 * parametro: ultimoNo (ponteido para o ultimo nó do grafo)
 * encapsulamento: private
 **/
No* Grafo::criaNo(int id, float peso)
{
    No* vertice = new No();
    vertice->setID(id);
    vertice->setPeso(peso);
    vertice->setProximo(NULL);
    vertice->setAdjacente(NULL);
    vertice->setUltimaAdjacente(NULL);

    if(listaNos == NULL)
    {
        listaNos = vertice;
    }
    else
    {
        ultimoNo->setProximo(vertice);
    }

    //atualiza o ultimo da lista
    ultimoNo = vertice;

    return vertice;
}

/**
 * Esse metodo cria uma aresta dados 2 vertices.
 * parametro: id (id do vertice)
 * parametro: peso (valor float do peso)
 * parametro: vertice (ponteiro para o vertice onde a aresta vai ser adicionada)
 * encapsulamento: private
 **/
Aresta* Grafo::criaAresta(int id, float peso, No*& vertice)
{
    Aresta *aresta = new Aresta();
    aresta->setNoAdjacente(id);
    aresta->setPeso(peso);
    aresta->setProximo(NULL);

    //adiciona aresta
    if(vertice->getAdjacente() == NULL)
    {
        //adiciona no começo a aresta criada
        vertice->setAdjacente(aresta);
    }
    else
    {
        //adiciona na ultima posicao a aresta criada
        Aresta *a = vertice->getUltimaAdjacente();
        a->setProximo(aresta);
    }

    //atualiza a ultima posicao de adjacencia do vértice
    vertice->setUltimaAdjacente(aresta);

    return aresta;
}

/**
 * Esse metodo adiciona um vertice e uma aresta, ou uma aresta dependendo das condições do grafo salvo.
 * Para ser usado com grafos com arestas simples
 * parametro: id (id do vertice)
 * parametro: idAresta (id do vertice de destino da aresta)
 * parametro: peso (valor float do peso)
 * encapsulamento: private
 **/
void Grafo::addNoEArestaPonderada(int id, float pesoVertice, int idAresta, float pesoVerticeAresta, float pesoAresta)
{
    No *vertice1;
    No *vertice2;

    //checa se tem algum self loop
    if(id == idAresta)
    {
        cout << "Não são permitidos self loops!" << endl;
        exit(1);
    }

    //verifica se já existem os vertices
    vertice1 = procuraNo(id);
    vertice2 = procuraNo(idAresta);

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
 * Esse metodo adiciona um vertice e uma aresta, ou uma aresta dependendo das condições do grafo salvo
 * Para ser usado com arcos direcionais
 * parametro: id (id do vertice)
 * parametro: idAresta (id do vertice de destino da aresta)
 * parametro: peso (valor float do peso)
 * encapsulamento: private
 **/
void Grafo::addNoEArestaPonderadaDigrafo(int id, float pesoVertice, int idAresta, float pesoVerticeAresta, float pesoAresta)
{
    No *verticeSaida;
    No *verticeEntrada;

    //checa se tem algum self loop
    if(id == idAresta)
    {
        cout << "Não são permitidos self loops!" << endl;
        exit(1);
    }

    //verifica se já existe o vertice
    verticeSaida = procuraNo(id);
    verticeEntrada = procuraNo(idAresta);

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
 * ############################## METODOS PUBLICOS ##############################
 **/


/**
 * Esse metodo adiciona um vertice ao grafo dado o id e o peso
 * parametro: id (id do vertice)
 * parametro: peso (valor float do peso)
 * encapsulamento: public
 * retorna: boolean (true = adicionado, false = erro ao adicionar)
 **/
bool Grafo::adicionaVertice(int id, float peso)
{
    if(procuraNo(id) == NULL)
    {
        criaNo(id, peso);
        cout << "O vertice '" << id << "' foi adicionado" << endl;
        return true;
    }
    else
    {
        cout << "O vertice '" << id << "' já existe." << endl;
        return false;
    }

}

/**
 * Esse metodo adiciona uma aresta ao grafo dado o id e o peso da origem e destino
 * parametro: idOrigem (id do vertice origem da aresta)
 * parametro: pesoIdOrigem (valor float do peso do vertice de origem)
 * parametro: idDestino (id do vertice de destino da aresta)
 * parametro: pesoIdDestino (valor float do peso do vertice de destino)
 * parametro: pesoAresta (valor float do peso da aresta)
 * encapsulamento: public
 * retorna: boolean (true = adicionado, false = erro ao adicionar)
 **/
bool Grafo::adicionaAresta(int idOrigem, float pesoIdOrigem, int idDestino, float pesoIdDestino, float pesoAresta)
{
    if(arestaExiste(idOrigem, idDestino))
    {
        cout << "A aresta (" << idOrigem << ", " << idDestino << ") já existe." << endl;
        return false;
    }
    else if(direcional == 1)
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
 * Esse metodo remove um vertice do grafo dado o id
 * parametro: id (id do vertice)
 * encapsulamento: public
 * retorna: boolean (true = removido, false = erro ao remover)
 **/
bool Grafo::removerVertice(int id)
{
    No *verticeRemover = procuraNo(id);
    if(verticeRemover == NULL)
    {
        cout << "O vertice '" << id << "' não foi encontrado" << endl;
        return false;
    }

    //remove as arestas de saida
    Aresta *a = verticeRemover->getAdjacente();
    while(a != NULL)
    {
        removerAresta(id, a->getNoAdjacente());
        a = verticeRemover->getAdjacente();
    }

    //remove as arestas de entrada
    No *v = listaNos;
    while(v != NULL)
    {
        if(v->getID() != id)
        {
            removerAresta(v->getID(), id);
        }
        v = v->getProximo();
    }

    if(verticeRemover->getGrauEntrada() == 0 && verticeRemover->getGrauSaida() == 0)
    {
        //a partir daqui o vertice já está isolado
        v = listaNos;
        No *ant = v;

        while(v != NULL)
        {
            if(v->getID() == id)
            {
                if(v == ant)
                {
                    //primeiro nó da lista
                    listaNos = v->getProximo();
                    delete v;
                }
                else if(v->getProximo() == NULL)
                {
                    //ultimo nó da lista
                    ultimoNo = ant;
                    ant->setProximo(NULL);
                    delete v;
                }
                else
                {
                    //aresta do meio
                    ant->setProximo(v->getProximo());
                    delete v;
                }
                
                //atualiza a ordem do grafo
                ordem--;
                cout << "o vertice '" << id << "' foi removido" << endl;
                return true;
            }
            ant = v;
            v = v->getProximo();
        }
    }

    return false;
}

/**
 * Esse metodo remove uma aresta do grafo dado o id de origem e destino
 * parametro: idOrigem (id do vertice de origem)
 * parametro: idDestino (id do vertice de destino)
 * encapsulamento: public
 * retorna: boolean (true = removida, false = erro ao remover)
 **/
bool Grafo::removerAresta(int idOrigem, int idDestino)
{
    No *vertice1 = procuraNo(idOrigem);
    No *vertice2 = procuraNo(idDestino);
    Aresta *ant;
    Aresta *prox;

    if(vertice1 == NULL){
        cout << "O vertice de origem '" << idOrigem << "' não foi encontrado" << endl;
    }
    if(vertice2 == NULL){
        cout << "O vertice de destino '" << idDestino << "' não foi encontrado" << endl;
    }

    //sair do metodo porque não tem os 2 vertices
    if(vertice1 == NULL || vertice2 == NULL){
        return false;
    }

    if(direcional == 1)
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
Grafo* Grafo::geraGrafoComplementar()
{
    return NULL;
}
No* Grafo::buscaEmLargura(int id)
{
    return NULL;
}
No* Grafo::buscaEmProfundidade(int id)
{
    return NULL;
}
ListaDeGrafos* Grafo::listaComponentesConexas()
{
    return NULL;
}
ListaDeGrafos* Grafo::listaComponentesFortementeConexas()
{
    return NULL;
}
Grafo* Grafo::ordenacaoTopologica()
{
    return NULL;
}


/**
 * Imprime os graus dos nós
 **/
void Grafo::sequenciaGrau()
{
    if(direcional == 1)
    {
        cout << "O grafo é direcionado" << endl;
    }
    No *vertice = listaNos;
    cout << endl << "----- Impressão dos graus dos nós -----" << endl << endl;
    cout << "";
    while(vertice != NULL)
    {
        cout << vertice->getGrauEntrada();
        vertice = vertice->getProximo();
        if(vertice != NULL)
        {
            cout << ", ";
        }
    }
    cout << "" << endl << endl;
}

/**
 * Imprime o grafo de maneira bem simples
 * Esse metodo é só pra testar e não deve ser usado no projeto final
 **/
void Grafo::imprimir()
{

    No *vertice = listaNos;

    cout << endl << "----- Impressão do grafo para testes -----" << endl << endl;

    while(vertice != NULL)
    {
        cout << "v:" << vertice->getID() << " ";

        Aresta *aresta = vertice->getAdjacente();
        while(aresta != NULL)
        {
            cout << "(a:" << aresta->getNoAdjacente() << ", p:"<< aresta->getPeso() << ")";
            aresta = aresta->getProximo();
            if(aresta != NULL)
            {
                cout << ", ";
            }
        }

        cout << endl;
        vertice = vertice->getProximo();
    }

}
