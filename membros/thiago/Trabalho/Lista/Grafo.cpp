/**
    Universidade Federal de Juiz de Fora
    Grafo.cpp
    Propósito: Classe que representa o grafo e contém metodos de manipulação.

    @author Thiago Almeida
    @version 1.0 30/03/19 
*/

#include "Grafo.h"

Grafo::Grafo(){}

Grafo::Grafo(bool isDirecionado, bool isPonderadoVertice, bool isPonderadoAresta)
{
    this->isDirecionado = isDirecionado;
    this->isPonderadoVertice = isPonderadoVertice;
    this->isPonderadoAresta = isPonderadoAresta;
    ordem = 0;
    numArestas = 0;
    listaNos = NULL;
    terminais = NULL;
    tamIndice = 0;
    tamMatrizIndice = 0;
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
    int a, b;
    float c, d, e;
    int n = -1;

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
        istringstream iss(line);

        if(n == -1)
        {
            //obtem o numero de vertices (nós) contido na primeira linha do arquivo
            iss >> n;
        }
        else
        {
            if(isPonderadoAresta && isPonderadoVertice)
            {
                //ponderado no vertice e na aresta
                if (!(iss >> a >> c >> b >> d >> e))
                {
                    cout << "Erro de leitura para o grafo ponderado nas arestas e vértices!" << endl;
                    exit(1);
                }
                if(isDirecionado){
                    addNoEArestaPonderadaDigrafo(a, c, b, d, e);
                } else {
                    addNoEArestaPonderada(a, c, b, d, e);
                }
            }
            else if(isPonderadoVertice)
            {
                //é ponderado nos vertices
                if (!(iss >> a >> c >> b >> d))
                {
                    cout << "Erro de leitura para o grafo ponderado nos vértices!" << endl;
                    exit(1);
                }
                if(isDirecionado){
                    addNoEArestaPonderadaDigrafo(a, c, b, d, 0);
                } else {
                    addNoEArestaPonderada(a, c, b, d, 0);
                }
            }
            else if(isPonderadoAresta)
            {
                //é ponderado nas arestas
                if (!(iss >> a >> b >> c))
                {
                    cout << "Erro de leitura para o grafo ponderado nas arestas!" << endl;
                    exit(1);
                }
                if(isDirecionado){
                    addNoEArestaPonderadaDigrafo(a, 0, b, 0, c);
                } else {
                    addNoEArestaPonderada(a, 0, b, 0, c);
                }
            }
            else 
            {
                //não é ponderado
                if (!(iss >> a >> b))
                {
                    cout << "Erro de leitura para o grafo não ponderado!" << endl;
                    exit(1); 
                }
                if(isDirecionado){
                    addNoEArestaPonderadaDigrafo(a, 0, b, 0, 0);
                } else {
                    addNoEArestaPonderada(a, 0, b, 0, 0);
                }
            }
        }
    }
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
            iss_ponderado >> ID >> id_vertice1 >> id_vertice2 >> peso_aresta;

            if (!iss_ponderado.fail())
            {
                //aresta ponderada com peso long int
                isPonderadoAresta = true;
                //cout << "add aresta ponderada int" << endl;
                addNoEArestaPonderada(id_vertice1, 0, id_vertice2, 0, peso_aresta);
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
                cout << num_terminais << endl;
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
    cout << numArestas << " arestas adicionadas" << endl;
    cout << num_terminais << " terminais adicionados" << endl << endl;
}

/**
 * ############################## METODOS AUXILIARES ##############################
 **/

/**
 * Get do ponteiro da lista de vertices
 * @return Ponteiro
 */
No* Grafo::getGrafo()
{
    return listaNos;
}

int Grafo::getOrdem()
{
    return ordem;
}

int Grafo::getNumTerminais(){
    return numTerminais;
}

int* Grafo::getTerminais()
{
    return terminais;
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
        cout << "O vertice de origem '" << idOrigem << "' não foi encontrado" << endl;
        return NULL;
    }

    if(isDirecionado)
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
            cout << "O vertice de destino '" << idOrigem << "' não foi encontrado" << endl;
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
 * Inicia matriz de indices, onde ficam armazenados os ids e status
 */
void Grafo::iniciaIndices()
{
    if(tamIndice > 0 && tamMatrizIndice > 0){
        //se já houver um indice, deleta ele
        for(int i = 0; i < tamMatrizIndice; i++){
            int *aux = indices[i];
            delete aux;            
        }
        delete indices;        
    }
    tamMatrizIndice = ordem;
    indices = new int*[tamMatrizIndice];
    for(int j = 0; j < tamMatrizIndice; j++){
        int *aux = new int[2];//duas linhas. Uma pro id do nó e outra pro status dele
        aux[0] = 0;
        aux[1] = 0;
        indices[j] = aux;
    }
    tamIndice = 0;
}

/**
 * Insere um id e status na matriz de indices
 * @param id Id do vértice
 * @param peso Peso do vértice
 * @return indice na matriz ou -1 se der erro
 */
int Grafo::insereOuAtualizaVerticeNoIndice(int id, int status)
{
    if(tamIndice == 0){
        //não tem nenhum indice
        indices[0][0] = id;
        indices[0][1] = status;
        tamIndice++;
        return 0;
    } else {
        int i = 0;
        for(i = 0; i < tamIndice; i++)
        {
            if(indices[i][0] == id){
                //o indice já existe e será atualizado
                indices[i][1] = status;
                return i;
            }
        }
        //o indice não existe e será criado no fim do vetor
        //cout << "i: " << i << ", " << tamIndice << endl;
        indices[i][0] = id;
        indices[i][1] = status;
        tamIndice++;
        return i;
    }
    return -1;
}

/**
 * Obtem o status do id armazenado na matriz de indices
 * @param id Id do vértice
 * @return status do id, ou -1 se não encontrar
 */
int Grafo::getStatusDoIndice(int id)
{
    for(int i = 0; i < tamIndice; i++)
    {
        if(indices[i][0] == id){
            return indices[i][1];
        }
    }
    return -1;
}

/**
 * Imprime o indice de maneira simples
 **/
void Grafo::imprimeIndice()
{
    cout << "----- Indice ------" << endl;
    for(int i = 0; i < tamIndice; i++)
    {
        cout << "indice " << i << ", (" << indices[i][0] << ", " << indices[i][1] << ")" << endl;
    }
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
    aresta->setNoOrigem(vertice->getId());
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
        cout << "Não são permitidos self loops!" << endl;
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
        cout << "Não são permitidos self loops!" << endl;
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


/*========================================================================*/
/*=================== Metodos pedidos na atividade 2 =====================*/
/*========================================================================*/


/**
 * Adiciona um vertice ao grafo dado o id e o peso
 * @param id Id do vértice destino
 * @param peso Peso do vértice
 * @return True se conseguiu criar o vértice, senão False
 */
bool Grafo::adicionaVertice(int id, float peso)
{
    if(getNo(id) == NULL)
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
        cout << "A aresta (" << idOrigem << ", " << idDestino << ") já existe." << endl;
        return false;
    }
    else if(isDirecionado)
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
bool Grafo::removerVertice(int id)
{
    No *verticeRemover = getNo(id);
    if(verticeRemover == NULL)
    {
        cout << "O vertice '" << id << "' não foi encontrado" << endl;
        return false;
    }

    //remove as arestas de saida
    Aresta *a = verticeRemover->getAresta();
    while(a != NULL)
    {
        removerAresta(id, a->getNoAdj());
        a = verticeRemover->getAresta();
    }

    //remove as arestas de entrada
    No *v = listaNos;
    while(v != NULL)
    {
        if(v->getId() != id)
        {
            removerAresta(v->getId(), id);
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
        cout << "o vertice '" << id << "' não foi isolado completamente" << endl;
    }

    return false;
}

/**
 * Remove uma aresta do grafo dado o id de origem e destino.
 * @param idOrigem Id do vértice origem
 * @param idDestino Id do vértice destino
 * @return True se removido, senão False
 */
bool Grafo::removerAresta(int idOrigem, int idDestino)
{
    No *vertice1 = getNo(idOrigem);
    No *vertice2 = getNo(idDestino);
    Aresta *ant;
    Aresta *prox;

    if(vertice1 == NULL){
        cout << "O vertice de origem '" << idOrigem << "' não foi encontrado" << endl;
    }
    if(vertice2 == NULL){
        cout << "O vertice de destino '" << idDestino << "' não foi encontrado" << endl;
    }

    //sair do metodo porque não tem um dos 2 vertices
    if(vertice1 == NULL || vertice2 == NULL){
        return false;
    }

    if(isDirecionado)
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
Grafo* Grafo::geraGrafoComplementar()
{
    return NULL;
}

/**
 * Executa uma busca em largura no grafo.
 * @param id Id do elemento a encontrar
 * @return 
 */
No* Grafo::buscaEmLargura(int id)
{
    return NULL;
}

/**
 * Executa uma busca em profundidade no grafo pra encontrar o caminho entre 2 vértices.
 * @param idOrigem Id do elemento origem
 * @param idDestino Id do elemento destino
 * @return 
 */
Aresta* Grafo::buscaEmProfundidade(int idOrigem, int idDestino)
{
    cout << "------ encontrar caminho entre '" << idOrigem << "' e '" << idDestino <<  "' -------" << endl;
    iniciaIndices();

    stack <Aresta> pilha;
    bool continuar = true;
    No *atual = getNo(idOrigem);
    int count_limit = 0;
    Aresta *listaRetorno = NULL;

    if(atual == NULL){
        cout << "O vertice de origem é nulo" << endl;
        return NULL;
    }

    while(continuar)
    {
        count_limit++;
        if(count_limit > (ordem * 2)){
            cout << "#### Atingiu o limite #####" << endl;
            return NULL;
        }
        //cout << "------" << endl;

        if(atual->getId() == idDestino)
        {
            cout << "Encontrado! " << endl;

            //o vertice destino foi encontrado. Desemplilha e retorna o caminho
            int tam = pilha.size();
            int count = tam-1;

            //transfere as arestas da pilha pra um vetor
            Aresta* caminho = new Aresta[tam];
            while(!pilha.empty())
            {
                caminho[count] = pilha.top();
                pilha.pop();
                count--;
            }

            //cria uma lista encadeada de arestas pra retornar
            Aresta *ultimaAresta = NULL;
            for(int i=0; i < tam; i++)
            {
                Aresta arestaDaPilha = caminho[i];

                //cria aresta de retorno
                Aresta *arestaCaminho = new Aresta();
                arestaCaminho->setNoOrigem(arestaDaPilha.getNoOrigem());
                arestaCaminho->setNoAdj(arestaDaPilha.getNoAdj());
                arestaCaminho->setPeso(arestaDaPilha.getPeso());
                arestaCaminho->setProx(NULL);

                if(listaRetorno == NULL){
                    listaRetorno = arestaCaminho;
                    ultimaAresta = arestaCaminho;
                } else {
                    ultimaAresta->setProx(arestaCaminho);
                    ultimaAresta = arestaCaminho;
                }
            }
            //delete caminho;
            /*
            //prepara o retorno na classe auxiliar
            //já que não dá pra retornar o vetor e o tamanho ao mesmo tempo
            ListaArestas *listaArestas = new ListaArestas();
            listaArestas->setVetorArestas(caminho);
            listaArestas->setTamanho(tam);
            */
            return listaRetorno;
        }

        //marca o atual como visitado (1)
        insereOuAtualizaVerticeNoIndice(atual->getId(), 1);

        //cout << "visitando " << atual->getId() << endl;

        //percorre as arestas até encontrar um vertice não visitado (0)
        Aresta *aresta = atual->getAresta();
        bool achouVerticeNaoVisitado = false;
        while(aresta != NULL)
        {
            //procura status do nó
            int status = getStatusDoIndice(aresta->getNoAdj());
            //cout << "status: " << status << endl;
            if(status == 0 || status == -1)//0 se tem indice e -1 se nem indice tem
            {
                //achou vertice vizinho não visitado, muda pra ele
                atual = getNo(aresta->getNoAdj());
                achouVerticeNaoVisitado = true;
                //cout << "mudou atual pro vizinho " << atual->getId() << endl;

                //registra na pilha por cópia
                pilha.push(*aresta);
                break;
            }
            aresta = aresta->getProx();
        }
        if(!achouVerticeNaoVisitado)
        {
            //cout << "não encontrou vizinhos visitados" << endl;

            //nao achou nenhum não visitado, marca como completo (2)
            insereOuAtualizaVerticeNoIndice(atual->getId(), 2);

            //cout << "marca " << atual->getId() << " como completo" << endl;

            //percorre as arestas até encontrar uma já visitada (1) pra voltar
            Aresta *aresta = atual->getAresta();
            bool achouVerticeVisitado = false;
            while(aresta != NULL)
            {
                int status = getStatusDoIndice(aresta->getNoAdj());
                if(status == 1)
                {
                    //achou vertice visitado, volta pra ele
                    atual = getNo(aresta->getNoAdj());
                    achouVerticeVisitado = true;
                    //cout << "volta pra " << atual->getId() << endl;
                    pilha.pop();
                    break;
                }
                aresta = aresta->getProx();
            }

            if(!achouVerticeVisitado)
            {
                //cout << "não encontrou vertices visitados" << endl;

                //não encontrou vertice já visitado, todos estão completos (2). Condição de parada
                //verificar se visitou todos os vertices
                if(tamIndice == ordem)
                {
                    //visitou todos. acabou o algoritmo
                    continuar = false;
                    cout << "visitou todos e não encontrou" << endl;
                }
                else
                {
                    //cout << "falta visitar " << (ordem - tamIndice) << " vertices" << endl;
                    //imprimeIndice();
                    cout << "O destino está em outra componente conexa!" << endl;
                    //A busca percorreu toda essa componente conexa, tem mais no grafo.
                    //a partir daqui não existe caminho do nó de origem ao de destino. Parar a busca.
                    return NULL;

                    /*
                    Esse código pode ser util pra busca de componentes conexas
                    No *aux = listaNos;
                    while(aux != NULL && getStatusDoIndice(aux->getId()) > 0)
                    {
                        aux = aux->getProx();
                    }
                    if(aux != NULL)
                    {
                        //parte pra proxima componente conexa
                        atual = aux;
                    } else {
                        cout << "Faltam nós e não foi encontrada nenhum nó..ué?" << endl;
                        return NULL;
                    }
                    */
                }
            }
        }
    }

    //indice.imprimeIndice();
    return NULL;
}

/**
 * Identifica as componentes conexas do grafo
 * @return 
 */
ListaGrafos* Grafo::listaComponentesConexas()
{
    return NULL;
}

/**
 * Identifica as componentes fortemente conexas do grafo
 * @return 
 */
ListaGrafos* Grafo::listaComponentesFortementeConexas()
{
    return NULL;
}

/**
 * Executa uma ordenação topológica do grafo
 * @return 
 */
Grafo* Grafo::ordenacaoTopologica()
{
    return NULL;
}


/*========================================================================*/
/*=================== Metodos pedidos na atividade 3 =====================*/
/*========================================================================*/


No* Grafo::getCoberturaVertices()
{
    No* pesos = new No[ordem];
    int n_pesos = 0;
    Aresta* arestas = new Aresta[numArestas];
    int n_arestas = 0;
    No* retorno = NULL;
    No* ultimoRetorno = NULL;
    int s_graus = 1;

    //passa graus pro vetor auxiliar
    No* p = listaNos;

    while(p != NULL){
        No aux;
        aux.setId(p->getId());
        aux.setGrauEntrada(p->getGrauEntrada());
        pesos[n_pesos] = aux;
        n_pesos++;
        p = p->getProx();
    }

    //loop principal
    while(s_graus > 0){
        //cout << "   *** loop ***" << endl;

        //pega o nó com maior grau
        int grau = 0;
        int indMaiorGrau = -1;

        s_graus = 0;

        for(int i=0; i<n_pesos; i++){
            //cout << "   vertice " << pesos[i].getId() << " com grau: " << pesos[i].getGrauEntrada() << endl;
            if(pesos[i].getGrauEntrada() > grau){
                grau = pesos[i].getGrauEntrada();
                indMaiorGrau = i;
                s_graus += grau;
            }
        }

        if(indMaiorGrau != -1){

            int id_escolhido = pesos[indMaiorGrau].getId();

            //cout << "   escolheu o vertice " << id_escolhido << endl;

            //adiciona na cobertura
            No* no_add = new No(id_escolhido, 0);
            no_add->setProx(NULL);

            if(retorno == NULL){
                retorno = no_add;
            } else {
                ultimoRetorno->setProx(no_add);
            }
            ultimoRetorno = no_add;

            //atualiza grau do escolhido pra zero
            pesos[indMaiorGrau].setGrauEntrada(0);
            No* n = getNo(id_escolhido);
            Aresta* a = n->getAresta();

            //cout << "       atualiza vertice " << id_escolhido << " para zero" << endl;

            //varre as arestas desse vertice
            while(a != NULL){
                int id_adj = a->getNoAdj();

                //procura no vetor e diminui um grau
                for(int j=0; j<n_pesos;j++){
                    if(pesos[j].getId() == id_adj){
                        pesos[j].removeGrauEntrada();
                        //cout << "       atualiza vertice " << id_adj << " em menos um grau" << endl;
                        break;
                    }
                }
                a = a->getProx();
            }

        }
    }

    return retorno;
}


/*========================================================================*/
/*=========================== Metodos extras =============================*/
/*========================================================================*/

/**
 * Imprime os graus dos nós
 **/
void Grafo::sequenciaGrau()
{
    if(isDirecionado)
    {
        cout << "O grafo é direcionado" << endl;
    }
    No *vertice = listaNos;
    cout << endl << "----- Impressão dos graus dos nós -----" << endl << endl;
    cout << "";
    while(vertice != NULL)
    {
        cout << vertice->getGrauEntrada();
        vertice = vertice->getProx();
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
        cout << "v:" << vertice->getId() << " ";

        Aresta *aresta = vertice->getAresta();
        while(aresta != NULL)
        {
            cout << "(a:" << aresta->getNoAdj() << ", p:"<< aresta->getPeso() << ")";
            aresta = aresta->getProx();
            if(aresta != NULL)
            {
                cout << ", ";
            }
        }

        cout << endl;
        vertice = vertice->getProx();
    }

}
