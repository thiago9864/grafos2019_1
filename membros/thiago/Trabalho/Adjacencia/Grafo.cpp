#include "Grafo.h"

Grafo::Grafo(bool _direcional, int _ponderado)
{
    direcional = _direcional;
    ponderado = _ponderado;
    n = -1;
    m = -1;
    listaNos = NULL;
    switch (ponderado)
    {
        case 0:
            ponderadoNos = false;
            ponderadoAresta = false;
            break;

        case 1:
            ponderadoNos = false;
            ponderadoAresta = true;
            break;

        case 2:
            ponderadoNos = true;
            ponderadoAresta = false;
            break;

        case 3:
            ponderadoNos = true;
            ponderadoAresta = true;
            break;

        default:
            ponderadoNos = false;
            ponderadoAresta = false;
            break;
    }
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

        if(n == -1)
        {
            //obtem o numero de vertices (nós) contido na primeira linha do arquivo
            iss >> n;
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

    //verifica se já existem os vertices
    vertice1 = procuraNo(id);
    vertice2 = procuraNo(idAresta);
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
    No *vertice;

    //verifica se já existe o vertice
    vertice = procuraNo(id);

    //cria vertice se não existir
    if(vertice == NULL)
    {
        vertice = new No();
        vertice->setID(id);
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
    }

    Aresta *aresta = new Aresta();
    aresta->setNoAdjacente(idAresta);
    aresta->setPeso(peso);
    aresta->setProximo(NULL);

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
        cout << "no(id: " << vertice->getID() << ", ";

        Aresta *aresta = vertice->getAdjacente();
        while(aresta != NULL)
        {
            cout << "aresta(noAdj:" << aresta->getNoAdjacente() << ", peso:"<< aresta->getPeso() << ") ";
            aresta = aresta->getProximo();
            if(aresta != NULL)
            {
                cout << ", ";
            }
        }

        cout << ")" << endl;
        vertice = vertice->getProximo();
    }

}
