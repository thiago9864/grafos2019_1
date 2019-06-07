//
// Created by victor on 01/04/19.
//

#include <iostream>
#include "Grafo.h"
#include "VetorOrdenado.h"

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

    this->imprime(saida);
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

    this->imprime(saida);
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

    this->imprime(saida);
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

    this->imprime(saida);
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


/*========================================================================*/
/*=================== Metodos pedidos na atividade 2 =====================*/
/*========================================================================*/


// *** PRIVATE ***


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


// *** GETTERS E SETTERS ***


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

void Grafo::setNo(int id) {
    this->setNo(id, -1);
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

void Grafo::setAresta(int idOrigem, int idFim) {
    // Verifica se o grafo é ponderado ou não da aresta para colocar um valour default
    if (!this->ponderadoAresta)
        this->setAresta(idOrigem, idFim, -1);
    else
        this->setAresta(idOrigem, idFim, 1);

}

No* Grafo::getNo(int id) {
    No *n = nullptr;

    // Percorrendo lista de nós até encontrar o desejado
    for (n = this->listaNos; n != nullptr && n->getId() != id; n = n->getProx());

    return n;
}

No* Grafo::getNo() {
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

/// Retorna matriz de adjacência do grafo.
int** Grafo::getMatrizAdj() {
    int** matrizAdj;
    int n = this->ordem;

    matrizAdj = new int*[n];

    No* no = this->listaNos;
    for (int i = 0; i < n; i++) {
        matrizAdj[i] = new int[n];
        
        Aresta* a = no->getAresta();
        for (int j = 0; j < n; j++) {
            
            matrizAdj[i][j] = a->getPeso();

            a = a->getProx();
        }
        no = no->getProx();
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

// *** REMOÇÃO ***


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


// *** FUNCIONALIDADES ***


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


Aresta* Grafo::buscaEmProfundidade(int idOrigem, int idDestino)
{

    stack <Aresta> pilha;
    bool continuar = true;
    No *atual = getNo(idOrigem);
    Aresta *listaRetorno = NULL;

    VetorOrdenado<int> *visitados = new VetorOrdenado<int>(ordem, 2);

    if(atual == NULL){
        cout << "O vertice de origem é nulo" << endl;
        return NULL;
    }

    //preenche visitados com os vertices disponiveis e coloca status 0 em todos
    No *p = listaNos;
    while(p != NULL)
    {
        visitados->addIndex(p->getId(), 0);

        //proximo vertice
        p = p->getProx();
    }

    while(continuar)
    {
        cout << "1" << endl;
        if(atual->getId() == idDestino)
        {
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
                Aresta *arestaCaminho = new Aresta(arestaDaPilha.getNoAdj(), arestaDaPilha.getNoOrigem(), arestaDaPilha.getPeso());

                if(listaRetorno == NULL){
                    listaRetorno = arestaCaminho;
                } else {
                    ultimaAresta->setProx(arestaCaminho);
                }

                ultimaAresta = arestaCaminho;
            }
            //delete caminho;
            delete visitados;
            return listaRetorno;
        }

        //marca o atual como visitado (1)
        visitados->set(atual->getId(), 1, 1);

        //percorre as arestas até encontrar um vertice não visitado (0)
        Aresta *aresta = atual->getAresta();
        bool achouVerticeNaoVisitado = false;
        while(aresta != NULL)
        {
            cout << "2" << endl;
            //procura status do nó
            int status = visitados->getByIndice(aresta->getNoAdj(), 1);
            
            if(status == 0 || status == -1)//0 se tem indice e -1 se nem indice tem
            {
                //achou vertice vizinho não visitado, muda pra ele
                atual = getNo(aresta->getNoAdj());
                achouVerticeNaoVisitado = true;

                //registra na pilha por cópia
                pilha.push(*aresta);
                break;
            }
            aresta = aresta->getProx();
        }
        if(!achouVerticeNaoVisitado)
        {
            cout << "3" << endl;
            //nao achou nenhum não visitado, marca como completo (2)
            visitados->set(atual->getId(), 1, 2);

            //percorre as arestas até encontrar uma já visitada (1) pra voltar
            Aresta *aresta = atual->getAresta();
            bool achouVerticeVisitado = false;
            while(aresta != NULL)
            {
                cout << "4" << endl;
                int status = visitados->getByIndice(aresta->getNoAdj(), 1);
                cout << "4.1" << endl;
                if(status == 1)
                {
                    //achou vertice visitado, volta pra ele
                    atual = getNo(aresta->getNoAdj());
                    cout << "4.2" << endl;
                    achouVerticeVisitado = true;
                    //cout << "volta pra " << atual->getId() << endl;
                    cout << pilha.empty() << endl;
                    pilha.pop();
                    cout << "4.3" << endl;
                    break;
                }
                cout << "4.4" << endl;
                aresta = aresta->getProx();
                cout << "4.5" << endl;
            }
             

            if(!achouVerticeVisitado)
            {
                cout << "5" << endl;
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
                    cout << "O destino está em outra componente conexa!" << endl;
                    //A busca percorreu toda essa componente conexa, tem mais no grafo.
                    //a partir daqui não existe caminho do nó de origem ao de destino. Parar a busca.
                    return NULL;
                }
            }
        }
    }

    return NULL;
}

/**
 * Ordenação topológica do grafo
 * @author Victor
 * @return vetor com os vertices ordenados
 */
int* Grafo::ordenacaoTopologica() 
{

    // Confirmando se o grafo é direcional
    if (!this->direcional) return nullptr;

    OrdenacaoTopologica ord(this->ordem, this->listaNos); // Inicializa Objeto de ordenação topológica

    int* ordenados = ord.ordenacao();                   // Recebe vetor com os nós ordenados

    return ordenados;

}

/**
 * Caminho largura
 * estou retornando uma lista do caminho at� chegar ao no desejado
 * @author Gabriele
 * @return ponteiro para lista de arestas
 */
Aresta* Grafo::caminho_largura(int id){
    //1º passo-> preciso procurar o no que posssui esse id
    No *no;
    no=getNo(id);
    No *raiz= this->listaNos;//aponta para o primeiro no da lista
    int auxTam=0;//guarda o tamanho exato do meu vetor aux. Dessa forma, não precisa percorrer o vetor todo.
    int aux[ordem];//lista de id na qual já passei (irá funcionar como uma estrutura de fila)
    No *auxVetorOrdem=NULL;// lista dos nós com o id armazenado em aux
    Aresta *listaCaminho=NULL;//esta é a lista de nós para chegar até o nó procurado
    Aresta *auxPrimeiro=NULL;// guarda a última aresta adj do nó visitada
    No *primeiro;//aponta para o primeiro vertice de aux
    if(raiz->getAresta()==NULL){
        cout<<"Não tem aresta no nó raiz, ou seja, o nó não está ligado a nenhum outro nó!";
        return NULL;
    }
    else{
        aux[0]=raiz->getId();
        No *w=NULL;
        auxPrimeiro=raiz->getAresta();
        w=getNo(auxPrimeiro->getNoAdj());
        Aresta *prox=NULL;// auxiliar para garantir que o cada aresta será armazenada no final da minha listaCaminho
        while(w->getId()!=no->getId() && auxTam!=-1){//percorrer até achar o no procurado ou até a fila ficar vazia.
            primeiro=getNo(aux[0]);
            auxPrimeiro=primeiro->getAresta();
            w=getNo(auxPrimeiro->getNoAdj());//pego o id do nó adjacente a aresta
            for(; w!=NULL && w->getId()!=no->getId(); w=getNo(auxPrimeiro->getNoAdj())){//w é um nó que procura os vizinhos do meu nó primeiro
                cout<<"valor id w:"<<w->getId()<<"\n";
                if(listaCaminho!=NULL){
                    for(prox=listaCaminho;prox->getProx()!=NULL;prox=prox->getProx()){};
                    prox->setProx(new Aresta(w->getId(), primeiro->getId(),primeiro->getAresta()->getPeso()));
                }
                else
                   listaCaminho=(new Aresta(w->getId(), primeiro->getId(),primeiro->getAresta()->getPeso()));
                auxTam++;
                aux[auxTam]=w->getId();
                if(auxPrimeiro->getProx()==NULL){//avalia se o próximo vizinho é vazio
                    break;
                }
                else
                    auxPrimeiro=auxPrimeiro->getProx();
            }
            for(int i=0;i<auxTam;i++){ //depois de armazenar as arestas dos vizinhos do primeiro, atualizo o primeiro para o próximo nó vizinho
                    aux[i]=aux[i+1];
            }
            auxTam=auxTam-1; //atualizo o tamanho do meu vetor aux

        }
        for(prox=listaCaminho;prox->getProx()!=NULL;prox=prox->getProx()){};
        prox->setProx(new Aresta(w->getId(),primeiro->getId(),primeiro->getAresta()->getPeso()));
    }
    return listaCaminho;
}
/**
 * Componentes conexas
 * @author Laura
 */
// *** PUBLIC ***
// Função que retorna o número de componentes conexas presentes no grafo.
// Também possibilita a identificação de qual vértice pertence a qual componente a partir do vetor indComp, que será modificado
// durante a execução.
int Grafo::componenteConexa(int* indComp, int* idNos)
{
    vetorIdNos(idNos);
    if(direcional == false) {
        int numComp = 0;
        for(int i = 0; i < ordem; i++) {
            indComp[i] = -1;
        }
        for(int i = 0; i < ordem; i++) {
            if(indComp[i] == -1) {
                buscaProfCompConexa(indComp, i, numComp++, idNos);
            }
        }

        return numComp;
    }

    return -1;
}
// *** PRIVATE ***
// Função auxiliar recursiva que executa uma busca em profundidade para encontrar as componentes conexas do grafo.
void Grafo::buscaProfCompConexa(int *indComp, int i, int numComp, int *idNos)
{

    indComp[i] = numComp;
    No *n = getNo(idNos[i]);


    for(Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) {
        i = encontraIndice(idNos, a->getNoAdj());
        if(indComp[i] == -1) {
            buscaProfCompConexa(indComp, i, numComp, idNos);
        }
    }
}

void Grafo::vetorIdNos(int* idNos) // Função auxiliar que preenche o vetor com os ids dos nós da lista.
{
    No *n;
    int i;
    for(n = listaNos, i = 0; n != nullptr; n = n->getProx(), i++) {
        idNos[i] = n->getId();
    }

}

int Grafo::encontraIndice(int *idNos, int id) // Função auxiliar que encontra a posição "i" de um id em um vetor idNos.
{
    int i;
    for(i = 0; i < ordem; i++) {
        if(idNos[i] == id) {
            break;
        }
    }
    return i;
}


/*========================================================================*/
/*=================== Metodos pedidos na atividade 3 =====================*/
/*========================================================================*/


/**
 * Implementação do algoritmo guloso 
 */
No* Grafo::getCoberturaVertices()
{
    No* pesos = new No[ordem];
    int n_pesos = 0;
    Aresta* arestas = new Aresta[m];
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

        //pega o nó com maior grau
        int grau = 0;
        int indMaiorGrau = -1;

        s_graus = 0;

        for(int i=0; i<n_pesos; i++){
            if(pesos[i].getGrauEntrada() > grau){
                grau = pesos[i].getGrauEntrada();
                indMaiorGrau = i;
                s_graus += grau;
            }
        }

        if(indMaiorGrau != -1){

            int id_escolhido = pesos[indMaiorGrau].getId();

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

            //varre as arestas desse vertice
            while(a != NULL){
                int id_adj = a->getNoAdj();

                //procura no vetor e diminui um grau
                for(int j=0; j<n_pesos;j++){
                    if(pesos[j].getId() == id_adj){
                        pesos[j].diminuiGrauEntrada();
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
/*=================== Metodos pedidos na atividade 4 =====================*/
/*========================================================================*/


/**
 * Implementação do algoritmo guloso reativo
 */



/*========================================================================*/
/*======================== Funcionamento do Grafo ========================*/
/*========================================================================*/



// *** PUBLIC ***

/**
     * Imprime na tela grafo no formato de lista de adjacência:
     *
     * DADOS:
     * Grau: valor
     * Ordem: valor
     * M: valor
     *
     * LISTA DE ADJACENCIA:
     * Vertice de origem --> Vertice adjacente (Peso) --> ...
     */
void Grafo::imprime() {
    cout << "DADOS: " << endl;
    cout << "Grau: " << this->grau << endl;
    cout << "Ordem: " << this->ordem << endl;
    cout << "M: " << this->m << endl;

    cout << "LISTA DE ADJACENCIA: " << endl;
    for (No* n = this->listaNos; n != nullptr; n = n->getProx()) {

        cout << n->getId() << " ---> ";

        for (Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) {
            // Se for ponderado nas arestas é imprimido o peso
            if (ponderadoAresta) {
                if (a->getProx() != nullptr)
                    cout << a->getNoAdj() << " (" << a->getPeso() << ") ---> ";
                else
                    cout << a->getNoAdj() << " (" << a->getPeso() << ")";
            } else {
                if (a->getProx() != nullptr)
                    cout << a->getNoAdj() << " ---> ";
                else
                    cout << a->getNoAdj();
            }
        }

        cout << endl;

    }
}

/**
     * Imprime na tela grafo no formato de lista de adjacência:
     *
     * DADOS:
     * Grau: valor
     * Ordem: valor
     * M: valor
     *
     * LISTA DE ADJACENCIA:
     * Vertice de origem --> Vertice adjacente (Peso) --> ...
     *
     * @param arquivo: Caminho do arquivo onde será gravada a impressão
     */
void Grafo::imprime(string arquivo) {

    ofstream file;

    file.open(arquivo, ios::out);

    if (file.is_open()) {

        file << "DADOS: " << endl;
        file << "Grau: " << this->grau << endl;
        file << "Ordem: " << this->ordem << endl;
        file << "M: " << this->m << endl;

        file << "LISTA DE ADJACENCIA: " << endl;
        for (No *n = this->listaNos; n != nullptr; n = n->getProx()) {

            file << n->getId() << " ---> ";

            for (Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) {
                // Se for ponderado nas arestas é imprimido o peso
                if (ponderadoAresta) {
                    if (a->getProx() != nullptr)
                        file << a->getNoAdj() << " (" << a->getPeso() << ") ---> ";
                    else
                        file << a->getNoAdj() << " (" << a->getPeso() << ")";
                } else {
                    if (a->getProx() != nullptr)
                        file << a->getNoAdj() << " ---> ";
                    else
                        file << a->getNoAdj();
                }
            }

            file << endl;

        }
    } else {
        cout << "Output file does not open." << endl;
    }
}

