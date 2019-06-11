/**
    Universidade Federal de Juiz de Fora
    Dijkstra.cpp
    Propósito: Calcula o caminho mínimo usando o algoritmo de Dijkstra.

    @author Thiago Almeida
    @version 1.2 09/05/19
*/

#include "Dijkstra.h"

Dijkstra::Dijkstra(No* listaNos)
{
    this->listaNos = listaNos;
    for(No* n = this->listaNos; n != nullptr; n = n->getProx(), this->ordem++);

    //inicia variaveis
    numVisitados = 0;
    distanciaMinima = maxFloat;
    visitados = new int[this->ordem];

    //inicia matriz de pesos
    No* p = this->listaNos;
    matriz = new float*[this->ordem];

    for(int j = 0; j < this->ordem; j++){
        float *aux = new float[3];

        aux[0] = p->getId();//id vertice
        aux[1] = maxFloat;//peso vertice
        aux[2] = 0;//id vertice anterior
        matriz[j] = aux;

        p = p->getProx();
    }
};
Dijkstra::~Dijkstra()
{
    //destrutor
    for(int j = 0; j < this->ordem; j++){
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
void Dijkstra::calcular(int origem, int destino)
{
    stack <int> pilha;

    //define a origem como atual
    // No* atual = grafo->getNo(origem);
    No* atual;
    for(atual = this->listaNos; atual->getId() != origem; atual = atual->getProx());
    updateDistanciaVertice(origem, 0, 0);

    //cout << "------------" << endl;

    //define estado inicial
    for(int i=0; i < this->ordem; i++){

        //cout << "   o vertice " << atual->getId() << " é o atual" << endl;

        //o vertice com menor distancia ainda não foi escolhido
        No* escolhido = NULL;
        float distEscolhido = maxFloat;

        //listo quem nao está na lista de visitados e nem é o atual
        Aresta* adj = atual->getAresta();
        while(adj != NULL)
        {
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

                if(distNoAdj < distEscolhido){
                    //marca o id com menor distancia
                    for(escolhido = this->listaNos; escolhido->getId() != adj->getNoAdj(); escolhido = escolhido->getProx());
                    // escolhido = grafo->getNo(adj->getNoAdj());
                    distEscolhido = distNoAdj;
                    //cout << "       adjacente " << adj->getNoAdj() << " foi marcado como menor distancia" << endl;
                }
            }
            else 
            {
                //cout << "       adjacente está na lista de visitados" << endl;
            }

            adj = adj->getProx();
        }
            
        //inclui o atual na lista de visitados
        setVisitado(atual->getId());

        //cout << "   inclui adjacente " << atual->getId() << " na lista de visitados" << endl;

        if(escolhido != NULL)
        {
            //marca o escolhido como atual
            atual = escolhido;     
            //cout << "   marca adjacente " << atual->getId() << " como atual" << endl; 
        } else {
            //cout << "   terminou o for" << endl;
        }        
    }

    //monta a pilha do caminho
    int d = destino;
    int tamCaminho = 1;

    pilha.push(d);
    while(d != origem)
    {
        int a = getAnterior(d);
        pilha.push(a);
        d = a;
        tamCaminho++;
    }
    
    //monta o caminho e imprime o resultado
    caminhoMinimo = new int[tamCaminho];
    cout << "caminho minimo: ";

    for(int i=0; i < tamCaminho; i++)
    {
        caminhoMinimo[i] = pilha.top();
        if(i>0){
            cout << " -> ";
        }
        cout << caminhoMinimo[i];;
        pilha.pop();
    }
    
    cout << endl;

    distanciaMinima = getDistancia(destino);    
}


/**
 * retorna a distância minima encontrada
 * @return (float) Distância mínima
 */
float Dijkstra::getDistanciaMinima()
{
    return distanciaMinima;
}

/**
 * retorna o caminho mínimo encontrado
 * @return (int*) Vetor ordenado de ids no sentido origem -> destino
 */
int* Dijkstra::getCaminhoMinimo()
{
    return caminhoMinimo;
}

/**
 * Inclui o id do vertice fornecido na lista de visitados
 * @param id Id do vertice
 */
void Dijkstra::setVisitado(int id)
{
    if(numVisitados == 0 || visitados[numVisitados-1] < id)
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
    
}
    

/**
 * Verifica se o vertice dado o id está na lista de visitados
 * @param id Id do vertice
 * @return (boolean) True se estiver, False senão
 */
bool Dijkstra::isVisitado(int id)
{
    if(numVisitados == 0)
    {
        return false;
    } 
    else if(numVisitados == 1)
    {
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
        }
        return false;   // não encontrado
    }
    
}

/**
 * Obtem o indice da matriz dado o id do vertice
 * @param id Id do vertice
 * @return (int) Indice da matriz
 */
int Dijkstra::getIndiceMatriz(int id)
{
    for(int i=0; i<this->ordem; i++)
    {
        if(int(matriz[i][0]) == id)
        {
            return i;
        }
    }
    return -1;
}

/**
 * Obtem o predessesor do vértice
 * @param id Id do vertice
 * @return (int) Id do predessesor
 */
int Dijkstra::getAnterior(int id)
{
    int indice = getIndiceMatriz(id);
    if(indice != -1)
    {
        return int(matriz[indice][2]);
    }
    return 0;
}

/**
 * Obtem a distância dado o vértice
 * @param id Id do vertice
 * @return (float) Distância (peso da aresta)
 */
float Dijkstra::getDistancia(int id)
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
void Dijkstra::updateDistanciaVertice(int id, int idAnt, float distancia)
{
    int indice = getIndiceMatriz(id);
    if(indice != -1)
    {
        matriz[indice][1] = distancia;
        matriz[indice][2] = idAnt;
    }
}