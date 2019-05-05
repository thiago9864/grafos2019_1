//
// Created by victor on 01/04/19.
//

#include <iostream>
#include "Grafo.h"

using namespace std;


Grafo::Grafo() {
    this->direcional = false;
    this->ponderadoAresta = false;
    this->ponderadoNo = false;
    this->listaNos = nullptr;
}

Grafo::Grafo(string entrada, string saida) {
    this->direcional = false;
    this->ponderadoAresta = false;
    this->ponderadoNo = false;
    this->listaNos = nullptr;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}

Grafo::Grafo(string entrada, string saida, bool direcional) {
    this->direcional = direcional;
    this->ponderadoNo = false;
    this->ponderadoAresta = false;
    this->listaNos = nullptr;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}

Grafo::Grafo(string entrada, string saida, bool direcional, bool ponderadoAresta) {
    this->direcional = direcional;
    this->ponderadoNo = false;
    this->ponderadoAresta = ponderadoAresta;
    this->listaNos = nullptr;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}

Grafo::Grafo(string entrada, string saida, bool direcional, bool ponderadoNo, bool ponderadoAresta) {
    this->direcional = direcional;
    this->ponderadoNo = ponderadoNo;
    this->ponderadoAresta = ponderadoAresta;
    this->listaNos = nullptr;
    this->leitura_arquivo(entrada);
    this->imprime(saida);
}

Grafo::~Grafo() {
    delete this->listaNos;
}


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



/*========================================================================*/
/*=============== Metodos auxiliares para as atividades ==================*/
/*========================================================================*/



/**
 * Inicia matriz de indices, onde ficam armazenados os ids e status
 * @author Thiago
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
 * @author Thiago
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
        indices[i][0] = id;
        indices[i][1] = status;
        tamIndice++;
        return i;
    }
    return -1;
}

/**
 * Obtem o status do id armazenado na matriz de indices
 * @author Thiago
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


/*========================================================================*/
/*=================== Metodos pedidos na atividade 2 =====================*/
/*========================================================================*/



/**
 * Executa uma busca em profundidade no grafo pra encontrar o caminho entre 2 vértices.
 * @author Thiago
 * @param idOrigem Id do elemento origem
 * @param idDestino Id do elemento destino
 * @return ponteiro para lista de arestas
 */
Aresta* Grafo::buscaEmProfundidade(int idOrigem, int idDestino)
{
    iniciaIndices();

    stack <Aresta> pilha;
    bool continuar = true;
    No *atual = getNo(idOrigem);
    Aresta *listaRetorno = NULL;

    while(continuar)
    {
        if(atual->getId() == idDestino)
        {
            //o vertice destino foi encontrado.
            int tam = pilha.size();
            int count = tam-1;

            //transfere as arestas da pilha pra um vetor na ordem inversa
            //assim a primeira aresta encadeada fica certa com o id de origem
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
            return listaRetorno;
        }

        //marca o atual como visitado (1)
        insereOuAtualizaVerticeNoIndice(atual->getId(), 1);

        //percorre as arestas até encontrar um vertice não visitado (0)
        Aresta *aresta = atual->getAresta();
        bool achouVerticeNaoVisitado = false;
        while(aresta != NULL)
        {
            //procura status do nó
            int status = getStatusDoIndice(aresta->getNoAdj());
            if(status == 0 || status == -1)//0 se tem indice e -1 se nem indice tem
            {
                //achou vertice vizinho não visitado, muda pra ele
                
                atual = getNo(aresta->getNoAdj());
                achouVerticeNaoVisitado = true;

                //registra na pilha por cópia
                Aresta a(aresta->getNoAdj(), aresta->getNoOrigem(), aresta->getPeso());
                pilha.push(a);

                break;
            }
            aresta = aresta->getProx();
        }
        if(!achouVerticeNaoVisitado)
        {
            //nao achou nenhum não visitado, marca como completo (2)
            insereOuAtualizaVerticeNoIndice(atual->getId(), 2);

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
                    pilha.pop();
                    break;
                }
                aresta = aresta->getProx();
            }

            if(!achouVerticeVisitado)
            {
                //não encontrou vertice já visitado, todos estão completos (2). Condição de parada
                //verificar se visitou todos os vertices
                if(tamIndice == ordem)
                {
                    //visitou todos. acabou o algoritmo
                    continuar = false;
                }
                else
                {
                    //A busca percorreu toda a componente conexa e tem mais vértices no grafo.
                    //a partir daqui não existe caminho do nó de origem ao de destino. Parar a busca.
                    return NULL;
                }
            }
        }
    }

    //indice.imprimeIndice();
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
    //1� passo-> preciso procurar o no que posssui esse id
    cout<<"entrei\n";
    No *no;
    no=getNo(id);
    cout<<"1� passo\n";
    No *raiz= this->listaNos;//aponta para o primeiro no da lista
    int auxTam=0;
    int aux[ordem];//lista de id na qual j� passei (ir� funcionar como uma estrutura de fila)
    No *auxVetorOrdem=NULL;
    Aresta *listaCaminho=NULL;//esta � a lista de n�s para chegar at� o n� procurado
    Aresta *auxPrimeiro=NULL;// guarda a �ltima aresta adj do n� visitada
    No *primeiro;//aponta para o primeiro vertice de aux
    if(raiz->getAresta()==NULL){
        cout<<"N�o tem aresta no n� raiz, ou seja, o n� n�o est� ligado a nenhum outro n�!";
        return NULL;
    }
    else{
        cout<<"caiu no else\n";
        listaCaminho=new Aresta(raiz->getAresta()->getNoAdj(),raiz->getId(),raiz->getPeso());
        cout<<"para onde e quem s�o os envolvidos: "<<listaCaminho->getNoOrigem()<<" e  fim:"<<listaCaminho->getNoAdj()<<"\n";
        aux[0]=raiz->getId();
//        auxVetorOrdem=getNo(aux[0]);
//        cout<<"marcou raiz de id:"<<auxVetorOrdem->getId()<<"\n";
        No *w=NULL;
        auxPrimeiro=raiz->getAresta();
        w=getNo(auxPrimeiro->getNoAdj());//pego o id do n� adjacente a aresta
        cout<<"criei w, de id:"<<w->getId()<<"\n";
        //enquanto o aux n�o estiver vazio
        Aresta *prox=NULL;
        while(w->getId()!=no->getId() && auxTam!=-1){
            cout<<"Entrou no while\n";
            cout<<"Valor do no:"<<no->getId()<<"\n";
            primeiro=getNo(aux[0]);
            auxPrimeiro=primeiro->getAresta();
            w=getNo(auxPrimeiro->getNoAdj());
            cout<<"para onde o primeiro aponta:"<<primeiro->getId()<<"\n";
            for(w; w!=NULL && w->getId()!=no->getId(); w=getNo(auxPrimeiro->getNoAdj())){
                cout<<"entrou no for\n";
                cout<<"w:"<<w->getId()<<"\n";
//                listaCaminho->setProx(getAresta(primeiro->getId(),w->getId()));

                for(prox=listaCaminho;prox->getProx()!=NULL;prox=prox->getProx()){};
                prox->setProx(new Aresta(w->getId(), primeiro->getId(),primeiro->getAresta()->getPeso()));
                for(Aresta* a = listaCaminho; a != NULL; a = a->getProx()) {
                    cout<<"Origem:"<< a->getNoOrigem()<<" ";
                    cout<<"Fim:"<<a->getNoAdj()<<"\n";
                }
                auxTam++;
                aux[auxTam]=w->getId();
                cout<<"vetor de id:"<<aux[0]<<" "<<aux[1]<<" "<<aux[2]<<"\n";
//                cout<<"get:"<<raiz->getAresta()->getProx()<<"\n";
                if(auxPrimeiro->getProx()==NULL){
                    break;
                }
                else
                    auxPrimeiro=auxPrimeiro->getProx();
//                cout<<"pr�ximo n� adjacente:"<< auxPrimeiro->getNoId()<<"\n";
            }
            for(int i=0;i<auxTam;i++){
                    aux[i]=aux[i+1];
            }
            auxTam=auxTam-1;

        }

        prox->setProx(new Aresta(w->getId(), primeiro->getId(),primeiro->getAresta()->getPeso()));
        cout<<"Imprimindo depois\n";
        for(Aresta* a = listaCaminho; a != NULL; a = a->getProx()) {
                    cout<<"Origem:"<< a->getNoOrigem()<<" ";
                    cout<<"Fim:"<<a->getNoAdj()<<"\n";
        }
    }

    cout<<"Vai retornar\n";
    return listaCaminho;
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
    for (list; list->getProx() != nullptr; list = list->getProx()) {
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
    for (list; list != nullptr; list = list->getProx()) {

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

Aresta* Grafo::getAresta(int idOrigem, int idFim) {
    No *n = this->getNo(idOrigem); // Encontrando nó de origem

    // Se encontrar nó inicia a busca se não retorna nullptr
    if (n != nullptr) {
        Aresta* a = n->getAresta();

        // Procurando aresta com nó passado, se encontrar o retorna, se não retorna nullptr
        for (a; a != nullptr && a->getNoAdj() != idFim; a = a->getProx());

        return a;

    } else {
        return nullptr;
    }

}

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
    for (no; no != nullptr; no = no->getProx()) {
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

