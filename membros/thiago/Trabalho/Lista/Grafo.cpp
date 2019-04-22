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
                if(direcional == 1){
                    //processa como grafo direcional
                    addNoEArestaPonderadaDigrafo(a, b, 0);
                } else {
                    //processa como grafo simples
                    addNoEArestaPonderada(a, b, 0);
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
                if(direcional == 1){
                    //processa como grafo direcional
                    addNoEArestaPonderadaDigrafo(a, b, c);
                } else {
                    //processa como grafo simples
                    addNoEArestaPonderada(a, b, c);
                }
            }
        }
    }
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
 * Esse metodo cria um vertice (nó) dado o id dele
 * parametro: id (id do vertice)
 * parametro: listaNos (ponteiro para lista de nós do grafo)
 * parametro: ultimoNo (ponteido para o ultimo nó do grafo)
 * encapsulamento: private
 **/
No* Grafo::criaNo(int id, No*& lista, No*& ultimo)
{
    No* vertice = new No();
    vertice->setID(id);
    vertice->setProximo(NULL);
    vertice->setAdjacente(NULL);
    vertice->setUltimaAdjacente(NULL);

    if(lista == NULL)
    {
        lista = vertice;
    }
    else
    {
        ultimo->setProximo(vertice);
    }

    //atualiza o ultimo da lista
    ultimo = vertice;
    
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
void Grafo::addNoEArestaPonderada(int id, int idAresta, float peso)
{
    No *vertice1;
    No *vertice2;

    //checa se tem algum self loop
    if(id == idAresta){
        cout << "Não são permitidos self loops!" << endl;
        exit(1);
    }

    //verifica se já existem os vertices
    vertice1 = procuraNo(id);
    vertice2 = procuraNo(idAresta);

    //cria vertice1 se não existir
    if(vertice1 == NULL)
    {
        vertice1 = criaNo(id, listaNos, ultimoNo);
    }

    //cria vertice2 se não existir
    if(vertice2 == NULL)
    {
        vertice2 = criaNo(idAresta, listaNos, ultimoNo);
    }

    //cria aresta de ida
    Aresta *aresta12 = criaAresta(idAresta, peso, vertice1);

    //cria aresta de volta
    Aresta *aresta21 = criaAresta(id, peso, vertice2);

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
void Grafo::addNoEArestaPonderadaDigrafo(int id, int idAresta, float peso)
{
    No *verticeSaida;
    No *verticeEntrada;

    //checa se tem algum self loop
    if(id == idAresta){
        cout << "Não são permitidos self loops!" << endl;
        exit(1);
    }

    //verifica se já existe o vertice
    verticeSaida = procuraNo(id);
    verticeEntrada = procuraNo(idAresta);

    //cria vertice se não existir
    if(verticeSaida == NULL)
    {
        verticeSaida = criaNo(id, listaNos, ultimoNo);
    }

    //cria vertice se não existir
    if(verticeEntrada == NULL)
    {
        verticeEntrada = criaNo(idAresta, listaNos, ultimoNo);
    }

    Aresta *aresta12 = criaAresta(idAresta, peso, verticeSaida);

    //atualiza grau dos vertices
    verticeSaida->addGrauSaida();
    verticeEntrada->addGrauEntrada();

    //contabiliza a aresta criada
    numArestas++;
}

/**
 * Imprime a sequencia de grau do grafo atual
 **/
void Grafo::sequenciaGrau(){
    if(direcional == 1){
        cout << "O grafo é direcionado" << endl;
    }
    No *vertice = listaNos;
    cout << endl << "----- Impressão da sequencia de grau -----" << endl << endl;
    cout << "<";
    while(vertice != NULL)
    {
        cout << vertice->getGrauEntrada();
        vertice = vertice->getProximo();
        if(vertice != NULL)
        {
            cout << ", ";
        }
    }
    cout << ">" << endl << endl;
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
