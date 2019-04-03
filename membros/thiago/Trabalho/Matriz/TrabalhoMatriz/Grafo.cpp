#include "Grafo.h"

Grafo::Grafo(bool _direcional, int _ponderado)
{
    direcional = _direcional;
    ponderado = _ponderado;
    n = -1;
    m = -1;
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
                addNoEArestaPonderada(a, b, 0);
            }
            if(ponderado == 1)
            {
                //o grafo é ponderado nas arestas
                if (!(iss >> a >> b >> c))
                {
                    cout << "Erro de leitura para o grafo ponderado nas arestas!" << endl;
                    exit(1); // sai do programa se houver algum erro de leitura
                }
                addNoEArestaPonderada(a, b, c);
            }
        }
    }
}