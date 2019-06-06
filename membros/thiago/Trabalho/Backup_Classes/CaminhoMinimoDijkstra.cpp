/**
    Universidade Federal de Juiz de Fora
    CaminhoMinimoDijkstra.cpp
    Propósito: Calcula o caminho mínimo usando o algoritmo de Dijkstra.

    @author Thiago Almeida
    @version 1.2 09/05/19
*/

#include "CaminhoMinimoDijkstra.h"

CaminhoMinimoDijkstra::CaminhoMinimoDijkstra(Grafo *grafo)
{
    this->grafo = grafo;

    //inicia variaveis
    numVisitados = 0;
    distanciaMinima = maxFloat;
    visitados = new int[grafo->getOrdem()];

    //inicia matriz de pesos
    
    matriz = new float*[grafo->getOrdem()];
    numMatriz = 0;

    for(int j = 0; j < grafo->getOrdem(); j++){
        float *aux = new float[3];

        aux[0] = 0;//id vertice
        aux[1] = maxFloat;//peso vertice
        aux[2] = 0;//id vertice anterior
        matriz[j] = aux;
    }

    //carrega os ids dos vertices na matriz de pesos
    No* p = grafo->getGrafo();
    while(p != NULL){
        addVerticeNaMatriz(p->getId());
        p = p->getProx();
    }
};
CaminhoMinimoDijkstra::~CaminhoMinimoDijkstra()
{
    //destrutor
    for(int j = 0; j < grafo->getOrdem(); j++){
        float *aux = matriz[j];
        delete aux;
    }
    delete matriz;
    delete caminhoMinimo;
    delete visitados;
};

/**
 * Calcula a distancia mínima e o caminho entre dois vértices dados os ids de origem e destino
 * @param origem Id do vertice de origem
 * @param destino Id do vertice de destino
 */
void CaminhoMinimoDijkstra::calcular(int origem, int destino)
{
    stack <int> pilha;

    //reseta a matriz em caso de leituras repetidas
    for(int i=0; i < grafo->getOrdem(); i++){
        matriz[i][1] = maxFloat;
        matriz[i][2] = 0;
        visitados[i] = 0;
    }

    //reseta variaveis
    numVisitados = 0;
    distanciaMinima = maxFloat;

    //define a origem como atual
    No* atual = grafo->getNo(origem);
    updateDistanciaVertice(origem, 0, 0);

    if(atual == NULL){
        cout << "Atual é nulo!" << endl;
        return;
    }

    //cout << "------------" << endl;

    //define estado inicial
    for(int i=0; i < grafo->getOrdem(); i++){

        //cout << "   o vertice " << atual->getId() << " é o atual" << endl;

        //listo quem nao está na lista de visitados e nem é o atual
        Aresta* adj = atual->getAresta();
        while(adj != NULL)
        {
            //cout << endl;
            //cout << "       ** verifica vertice adjacente " << adj->getNoAdj() << " **" << endl;
            if(!isVisitado(adj->getNoAdj())){
                //cout << "       adjacente está fora da lista de visitados" << endl;

                //quem foi listado, calcula a distancia e atualiza se for menor que a atual
                float distNoAdj = getDistancia(atual->getId()) + adj->getPeso();
                //cout << "       dist adjacente: " << distNoAdj << " < " << getDistancia(adj->getNoAdj()) << endl;

                if(distNoAdj < getDistancia(adj->getNoAdj())){
                    //cout << "       atualiza distancia do adjacente" << endl;

                    //se atualizou a distancia, coloca o id na coluna de anteriores
                    updateDistanciaVertice(adj->getNoAdj(), atual->getId(), distNoAdj);
                }

                //cout << "       distNoAdj: " << distNoAdj << " < " << distEscolhido << endl;
            }
            else 
            {
                //cout << "       adjacente está na lista de visitados" << endl;
            }

            adj = adj->getProx();
        }
        
        //inclui o atual na lista de visitados
        setVisitado(atual->getId());
        //cout << "   inclui atual " << atual->getId() << " na lista de visitados" << endl;

        //procura o vertice de menor distancia no grafo
        No* escolhido = NULL;
        float distEscolhido = maxFloat;
        int numvis = 0;

        for(int i=0; i < grafo->getOrdem(); i++)
        {
            int id = matriz[i][0];
            float dist = matriz[i][1];
            bool isVis = isVisitado(id);
            if(isVis){
                numvis++;
            }
            //cout << id << " " << dist << " " << isVisitado(id) << endl;
            if(dist < distEscolhido && !isVis)
            {
                escolhido = grafo->getNo(id);
                distEscolhido = dist;
            }
        }
        //cout << "numvis: " << numvis << endl;

        if(numvis >= grafo->getOrdem())
        {
            //cout << "todos já foram visitados" << endl;
            break;
        }

        if(escolhido == NULL)
        {
            cout << "não foi possivel escolher o proximo ativo" << endl;
            exit(1);
        } else 
        {
            atual = escolhido;     
            //cout << "   marca adjacente " << atual->getId() << " como atual" << endl; 
        }

    }

    //monta a pilha do caminho
    int d = destino;
    tamCaminhoMinimo = 1;

    //cout << "fim algoritmo" << endl;
    //cout << "Caminho: " << d;

    pilha.push(d);
    while(d != origem)
    {
        int a = getAnterior(d);

        //cout << a << " ";
        if(a == -1){
            cout << endl << "Algum vertice armazenado na matriz não foi lido corretamente" << endl;
            exit(1);
        }

        pilha.push(a);
        d = a;
        tamCaminhoMinimo++;
    }

    //cout << endl;
    //cout << "passou o while" << endl;

    //monta o caminho e imprime o resultado
    caminhoMinimo = new int[tamCaminhoMinimo];
    //cout << "caminho minimo: ";

    for(int i=0; i < tamCaminhoMinimo; i++)
    {
        caminhoMinimo[i] = pilha.top();
        if(i>0){
           //cout << " -> ";
        }
        //cout << caminhoMinimo[i];;
        pilha.pop();
    }
    
    //cout << endl;

    distanciaMinima = getDistancia(destino);    
}


/**
 * retorna a distância minima encontrada
 * @return (float) Distância mínima
 */
float CaminhoMinimoDijkstra::getDistanciaMinima()
{
    return distanciaMinima;
}

/**
 * retorna o caminho mínimo encontrado
 * @return (int*) Vetor ordenado de ids no sentido origem -> destino
 */
int* CaminhoMinimoDijkstra::getCaminhoMinimo()
{
    return caminhoMinimo;
}


/**
 * retorna o tamanho do caminho mínimo encontrado
 * @return (int) Tamanho
 */
int CaminhoMinimoDijkstra::getTamanhoCaminhoMinimo()
{
    return tamCaminhoMinimo;
}



/**
 * Inclui o id do vertice fornecido na lista de visitados
 * @param id Id do vertice
 */
void CaminhoMinimoDijkstra::setVisitado(int id)
{
    if(isVisitado(id)){
        //ja foi visitado - não faz nada
        cout << id << " ja foi visitado!!!" << endl;
        return;
    }
    else if(numVisitados == 0 || visitados[numVisitados-1] < id)
    {
        //se o vetor estiver vazio, ou o id for maior que o ultimo valor, insere em o(1)
        visitados[numVisitados] = id;
        numVisitados++;
    }
    else if(numVisitados == 1)
    {
        //o vetor tem 1 e o id é menor que o visitados[0], insere em o(1)
        int aux = visitados[0];
        visitados[0] = id;
        visitados[numVisitados] = aux;
        numVisitados++;
    }
    else
    {
        //o id esta no meio do vetor, encontra o primeiro maior que ele
        int i;
        for(i=0; i < numVisitados; i++)
        {
            if(visitados[i] > id)
            {
                break;
            }
        }

        //faz o deslocamento do vetor
        for(int j=numVisitados; j > i; j--)
        {
            visitados[j] = visitados[j-1];
        }

        //insere ele na posicao, em o(n)
        visitados[i] = id;
        
        //conta a inserção
        numVisitados++;
    }

   // cout << id << " foi marcado como visitado" << endl;
    
}


/**
 * Verifica se o vertice dado o id está na lista de visitados
 * @param id Id do vertice
 * @return (boolean) True se estiver, False senão
 */
bool CaminhoMinimoDijkstra::isVisitado(int id)
{
    //cout << " checa visita" << endl;
    if(numVisitados == 0)
    {
        //cout << id << " isVisitado = false" << endl;
        return false;
    } 
    else if(numVisitados == 1)
    {
        //bool b = (visitados[0] == id);
        //cout << id << " isVisitado = " << b << endl;
        return (visitados[0] == id);
    }
    else
    {
        //busca binaria (o vetor está ordenado)
        int inicio = 0;     
        int fim = numVisitados-1;
        int meio;

        while (inicio <= fim)
        {
            meio = (inicio + fim)/2;
            if (id == visitados[meio])
            {
                //cout << id << " isVisitado = true" << endl;
                return true;
            }
            if (id < visitados[meio])
            {
                fim = meio-1;
            }
            else
            {
                inicio = meio+1;
            }
            //cout << "buscando..." << endl;
        }
        //cout << id << " isVisitado = false" << endl;
        return false;   // não encontrado
    }
    
}

/**
 * Obtem o indice da matriz dado o id do vertice
 * @param id Id do vertice
 * @return (int) Indice da matriz
 */
int CaminhoMinimoDijkstra::getIndiceMatriz(int id)
{
    if(numMatriz == 0)
    {
        return -1;
    } 
    else if(numMatriz == 1 && matriz[0][0] == id)
    {
        return 0;
    }
    else
    {
        //busca binaria (a matriz está ordenada)
        int inicio = 0;     
        int fim = numMatriz-1;
        int meio;

        while (inicio <= fim)
        {
            meio = (inicio + fim)/2;
            if (id == matriz[meio][0])
            {
                return meio;
            }
            if (id < matriz[meio][0])
            {
                fim = meio-1;
            }
            else
            {
                inicio = meio+1;
            }
        }
        return -1;   // não encontrado
    }
    
}

/**
 * Obtem o predessesor do vértice
 * @param id Id do vertice
 * @return (int) Id do predessesor
 */
int CaminhoMinimoDijkstra::getAnterior(int id)
{
    int indice = getIndiceMatriz(id);
    if(indice != -1)
    {
        return int(matriz[indice][2]);
    }
    return -1;
}

/**
 * Obtem a distância dado o vértice
 * @param id Id do vertice
 * @return (float) Distância (peso da aresta)
 */
float CaminhoMinimoDijkstra::getDistancia(int id)
{
    int indice = getIndiceMatriz(id);
    if(indice != -1)
    {
        return matriz[indice][1];
    }
    return 0;
}

/**
 * Atualiza a distancia do vértice dado o id fornecido
 * @param id Id do vertice
 * @param idAnt Id do predessesor
 * @param distancia Distância (peso da aresta)
 */
void CaminhoMinimoDijkstra::updateDistanciaVertice(int id, int idAnt, float distancia)
{
    int indice = getIndiceMatriz(id);
    if(indice != -1)
    {
        matriz[indice][1] = distancia;
        matriz[indice][2] = idAnt;
    }
}

void CaminhoMinimoDijkstra::addVerticeNaMatriz(int id)
{
    if(numMatriz == 0 || matriz[numMatriz-1][0] < id)
    {
        //se a matriz estiver vazia, ou o id for maior que o ultimo valor, insere em o(1)
        matriz[numMatriz][0] = id;
        numMatriz++;
    }
    else if(numMatriz == 1)
    {
        //o vetor tem 1 e o id é menor que o visitados[0], insere em o(1)
        int aux = matriz[0][0];
        matriz[0][0] = id;
        matriz[numMatriz][0] = aux;
        numMatriz++;
    }
    else
    {
        //o id esta no meio da matriz, encontra o primeiro maior que ele
        int i;
        for(i=0; i < numMatriz; i++)
        {
            if(matriz[i][0] > id)
            {
                break;
            }
        }

        //faz o deslocamento da matriz
        for(int j=numMatriz; j > i; j--)
        {
            matriz[j][0] = matriz[j-1][0];
        }

        //insere ele na posicao, em o(n)
        matriz[i][0] = id;
        
        //conta a inserção
        numMatriz++;
    }
}