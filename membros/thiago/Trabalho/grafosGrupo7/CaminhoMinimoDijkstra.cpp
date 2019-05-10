/**
    Universidade Federal de Juiz de Fora
    CaminhoMinimoDijkstra.h
    Propósito: Calcula o caminho mínimo usando o algoritmo de Dijkstra.

    @author Thiago Almeida
    @version 1.0 09/05/19
*/

#include "CaminhoMinimoDijkstra.h"

CaminhoMinimoDijkstra::CaminhoMinimoDijkstra(Grafo *grafo)
{
    this->grafo = grafo;
    visitados = new int[grafo->getOrdem()];
    indice = new int[grafo->getOrdem()];
    distancias = new float[grafo->getOrdem()];
    numVisitados = 0;

    No* p = grafo->getPonteiroGrafo();
    cout << "vertices adicionados: ";
    for(int i=0; i<grafo->getOrdem(); i++)
    {
        visitados[i] = 0;
        indice[i] = p->getId();
        distancias[i] = 999;
        cout << indice[i] << " ";
        p = p->getProx();
    }
    cout << endl;
};
CaminhoMinimoDijkstra::~CaminhoMinimoDijkstra()
{
    //destrutor
};

float CaminhoMinimoDijkstra::getDistancia(int id)
{
    for(int i=0; i<grafo->getOrdem(); i++)
    {
        if(indice[i] == id)
        {
            return distancias[i];
        }
    }
    return -1;
}
void CaminhoMinimoDijkstra::updateDistancia(int id, float distancia)
{
    for(int i=0; i<grafo->getOrdem(); i++)
    {
        if(indice[i] == id)
        {
            distancias[i] = distancia;
            break;
        }
    }
}

bool CaminhoMinimoDijkstra::isVisitado(int id)
{
    cout << "visitados: ";
    bool visitado = false;
    for(int i=0; i<numVisitados; i++)
    {
        cout << visitados[i] << " ";
        if(visitados[i] == id)
        {
            visitado = true;
        }
    }
    cout << endl;
    return visitado;
}

float CaminhoMinimoDijkstra::calcular(int origem, int destino)
{
    No* atual = NULL;
    float distanciaAcumulada = 0;
    int idAtual = origem;

    //coloca na lista de visitados o nó de destino
    visitados[0] = origem;
    updateDistancia(origem, 0);
    numVisitados = 1;

    cout << "marca '" << origem << "' como origem" << endl;
    cout << "marca '" << destino << "' como destino" << endl;

    while(numVisitados <= grafo->getOrdem())
    {
        if(idAtual == destino){
            cout << "chegou no destino" << endl;
            break;
        }
        cout << "----------------------" << endl;
        //procura vertices adjacentes
        atual = grafo->getNo(idAtual);
        Aresta* adj = atual->getAresta();
        float aux = adj->getPeso() + distanciaAcumulada;
        int idNoEscolhido = adj->getNoAdj();

        cout << "atual esta no vertice '" << atual->getId() << "'" << endl;

        while(adj != NULL)
        {
            float distNo = getDistancia(adj->getNoAdj());
            float newDist = adj->getPeso() + distanciaAcumulada;

            //cout << "adj no vertice: '" << adj->getNoAdj() << "'" << endl;
            cout << "***" << endl;
            if(!isVisitado(adj->getNoAdj()))
            {
                cout << "o vertice '" << adj->getNoAdj() << "' ainda nao foi visitado, olhando" << endl;
                cout << "a distancia da origem ate esse vertice e: '" << newDist << "'" << endl;
                cout << "a distancia armazenada no indice e: '" << distNo << "'" << endl;


                if(newDist < distNo)
                {
                    updateDistancia(adj->getNoAdj(), newDist);
                    distNo = newDist;
                    cout << "atualizou distancia" << endl;
                }
                cout << "distNo: " << distNo << ", aux: " << aux << endl;
                if(distNo < aux)
                {
                    aux = distNo;
                    idNoEscolhido = adj->getNoAdj();
                    cout << "mudou o escolhido pra '" << idNoEscolhido << "'" << endl;
                }
            }

            adj = adj->getProx();
        }
        //cout << "terminou com as arestas" << endl;
        //muda pro no escolhido
        idAtual = idNoEscolhido;
        distanciaAcumulada = aux;
        visitados[numVisitados] = idAtual;
        numVisitados++;
        cout << "---> no '" << idAtual << "' escolhido" << endl;
        cout << "---> distanciaAcumulada: '" << distanciaAcumulada << "'" << endl;
       // break;
    }

    isVisitado(0);

    return distanciaAcumulada;
}
