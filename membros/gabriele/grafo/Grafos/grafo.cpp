#include <iostream>
#include "grafo.h"
#include"no.h"
#include"aresta.h"
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
    for (No* n = this->listaNos; n != NULL; n = n->getProx()) {

        cout << n->getId() << " ---> ";

        for (Aresta *a = n->getAresta(); a != NULL; a = a->getProx()) {
            // Se for ponderado nas arestas é imprimido o peso
            if (ponderadoAresta) {
                if (a->getProx() != NULL)
                    cout << a->getNoId() << " (" << a->getPeso() << ") ---> ";
                else
                    cout << a->getNoId() << " (" << a->getPeso() << ")";
            } else {
                if (a->getProx() != NULL)
                    cout << a->getNoId() << " ---> ";
                else
                    cout << a->getNoId();
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
        for (No *n = this->listaNos; n != NULL; n = n->getProx()) {

            file << n->getId() << " ---> ";

            for (Aresta *a = n->getAresta(); a != NULL; a = a->getProx()) {
                // Se for ponderado nas arestas é imprimido o peso
                if (ponderadoAresta) {
                    if (a->getProx() != NULL)
                        file << a->getNoId() << " (" << a->getPeso() << ") ---> ";
                    else
                        file << a->getNoId() << " (" << a->getPeso() << ")";
                } else {
                    if (a->getProx() != NULL)
                        file << a->getNoId() << " ---> ";
                    else
                        file << a->getNoId();
                }
            }

            file << endl;

        }
    } else {
        cout << "Output file does not open." << endl;
    }
}

// *** GETTERS E SETTERS ***


void Grafo::setNo(int id, float peso) {

    No* no = new No(id, peso);

    No *list = this->listaNos;

    if (list == NULL) {
        this->listaNos = no;
        this->ordem = 1; // Inicializa a ordem
        return;
    }

    // Percorrendo lista de nós até encontrar o ultimo
    for (list; list->getProx() != NULL; list = list->getProx()) {
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
    No * origem = NULL;
    No * fim = NULL;

    // Evitando self loops
    if (idOrigem == idFim) {
        cout << "Nao e permitido self-loop" << endl;
        return;
    }

    // Percorrendo lista de nós até encontrar os nós que irão receber a aresta
    for (list; list != NULL; list = list->getProx()) {

        if (list->getId() == idOrigem)
            origem = list;

        if (list->getId() == idFim)
            fim = list;

        // Evitando percorrer até o final desnecessáriamente
        if (origem != NULL && fim != NULL) break;

    }

    if (origem != NULL && fim != NULL) {
        Aresta *origem_fim = new Aresta(idFim,idOrigem, peso);

        if (origem->setAresta(origem_fim))
            fim->aumentaGrauEntrada();

    } else {
        cout << "No nao encontrado" << endl;
        return;
    }

    // Se o grafo não for direcional o nó de chegada também recebe uma aresta
    if (!this->direcional) {
        Aresta *fim_origem = new Aresta(idOrigem,idFim,peso);

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
    No *n=NULL;

    // Percorrendo lista de nós até encontrar o desejado
    for (n = this->listaNos; n != NULL && n->getId() != id; n = n->getProx());

    return n;
}

Aresta* Grafo::getAresta(int idOrigem, int idFim) {
    No *n = this->getNo(idOrigem); // Encontrando nó de origem

    // Se encontrar nó inicia a busca se não retorna NULL
    if (n != NULL) {
        Aresta* a = n->getAresta();

        // Procurando aresta com nó passado, se encontrar o retorna, se não retorna NULL
        for (a; a != NULL && a->getNoId() != idFim; a = a->getProx());

        return a;

    } else {
        return NULL;
    }

}

// *** REMOÇÃO ***

void Grafo::removeAresta(int idOrigem, int idFim) {
    No *origem = this->getNo(idOrigem);  // Encontrando nó de inicio da aresta
    No *fim = this->getNo(idFim);        // Caso seja necessário manipular o nó de destino

    bool removeu = false;

    if (origem != NULL && fim != NULL) {

        removeu = origem->removeAresta(idFim); // Removendo aresta do nó de origem
        if (removeu)
            fim->diminuiGrauEntrada();   // Diminuindo grau de entrada do fim

        // Se o grafo não for direcional removemos também a aresta que indica a "volta"
        if (!this->direcional) {

            if (fim != NULL)
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
    for (no; no != NULL; no = no->getProx()) {
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

        no->setProx(NULL);          // Evita apagar o nó subsequente
        delete no;

        // Inicia remoção de arestas ligadas a tal nó removido
        for (No *n = this->listaNos; n != NULL; n = n->getProx()) {
            removeu = n->removeAresta(id);

            if (removeu) {
                this->m--;             // Diminuindo número de arestas se foi removido

                if (!this->direcional)  // Se não for direcional temos que diminuir o grau de entrada
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

    for (No *no = this->listaNos; no != NULL; no = no->getProx()) {
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

//***Caminho largura ***
//estou retornando uma lista do caminho até chegar ao no desejado
Aresta* Grafo::caminho_largura(int id){
    //1º passo-> preciso procurar o no que posssui esse id
    cout<<"entrei\n";
    No *no;
    no=getNo(id);
    cout<<"1º passo\n";
    No *raiz= this->listaNos;//aponta para o primeiro no da lista
    int auxTam=0;
    int aux[ordem];//lista de id na qual já passei (irá funcionar como uma estrutura de fila)
    No *auxVetorOrdem=NULL;
    Aresta *listaCaminho=NULL;//esta é a lista de nós para chegar até o nó procurado
    Aresta *auxPrimeiro=NULL;// guarda a última aresta adj do nó visitada
    No *primeiro;//aponta para o primeiro vertice de aux
    if(raiz->getAresta()==NULL){
        cout<<"Não tem aresta no nó raiz, ou seja, o nó não está ligado a nenhum outro nó!";
        return NULL;
    }
    else{
        cout<<"caiu no else\n";
        listaCaminho=new Aresta(raiz->getAresta()->getNoId(),raiz->getId(),raiz->getPeso());
        cout<<"para onde e quem são os envolvidos: "<<listaCaminho->getOrigemId()<<" e  fim:"<<listaCaminho->getNoId()<<"\n";
        aux[0]=raiz->getId();
//        auxVetorOrdem=getNo(aux[0]);
//        cout<<"marcou raiz de id:"<<auxVetorOrdem->getId()<<"\n";
        No *w=NULL;
        auxPrimeiro=raiz->getAresta();
        w=getNo(auxPrimeiro->getNoId());//pego o id do nó adjacente a aresta
        cout<<"criei w, de id:"<<w->getId()<<"\n";
        //enquanto o aux não estiver vazio
        Aresta *prox=NULL;
        while(w->getId()!=no->getId() && auxTam!=-1){
            cout<<"Entrou no while\n";
            cout<<"Valor do no:"<<no->getId()<<"\n";
            primeiro=getNo(aux[0]);
            auxPrimeiro=primeiro->getAresta();
            w=getNo(auxPrimeiro->getNoId());
            cout<<"para onde o primeiro aponta:"<<primeiro->getId()<<"\n";
            for(w; w!=NULL && w->getId()!=no->getId(); w=getNo(auxPrimeiro->getNoId())){
                cout<<"entrou no for\n";
                cout<<"w:"<<w->getId()<<"\n";
//                listaCaminho->setProx(getAresta(primeiro->getId(),w->getId()));

                for(prox=listaCaminho;prox->getProx()!=NULL;prox=prox->getProx()){};
                prox->setProx(new Aresta(w->getId(), primeiro->getId(),primeiro->getAresta()->getPeso()));
                for(Aresta* a = listaCaminho; a != NULL; a = a->getProx()) {
                    cout<<"Origem:"<< a->getOrigemId()<<" ";
                    cout<<"Fim:"<<a->getNoId()<<"\n";
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
//                cout<<"próximo nó adjacente:"<< auxPrimeiro->getNoId()<<"\n";
            }
            for(int i=0;i<auxTam;i++){
                    aux[i]=aux[i+1];
            }
            auxTam=auxTam-1;

        }

        prox->setProx(new Aresta(w->getId(), primeiro->getId(),primeiro->getAresta()->getPeso()));
        cout<<"Imprimindo depois\n";
        for(Aresta* a = listaCaminho; a != NULL; a = a->getProx()) {
                    cout<<"Origem:"<< a->getOrigemId()<<" ";
                    cout<<"Fim:"<<a->getNoId()<<"\n";
        }
    }

    cout<<"Vai retornar\n";
    return listaCaminho;
}
