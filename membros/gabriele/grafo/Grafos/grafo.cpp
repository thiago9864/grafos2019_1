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
     * Imprime na tela grafo no formato de lista de adjac�ncia:
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
            // Se for ponderado nas arestas � imprimido o peso
            if (ponderadoAresta) {
                if (a->getProx() != NULL)
                    cout << a->getNoAdj() << " (" << a->getPeso() << ") ---> ";
                else
                    cout << a->getNoAdj() << " (" << a->getPeso() << ")";
            } else {
                if (a->getProx() != NULL)
                    cout << a->getNoAdj() << " ---> ";
                else
                    cout << a->getNoAdj();
            }
        }

        cout << endl;

    }
}

/**
     * Imprime na tela grafo no formato de lista de adjac�ncia:
     *
     * DADOS:
     * Grau: valor
     * Ordem: valor
     * M: valor
     *
     * LISTA DE ADJACENCIA:
     * Vertice de origem --> Vertice adjacente (Peso) --> ...
     *
     * @param arquivo: Caminho do arquivo onde ser� gravada a impress�o
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
                // Se for ponderado nas arestas � imprimido o peso
                if (ponderadoAresta) {
                    if (a->getProx() != NULL)
                        file << a->getNoAdj() << " (" << a->getPeso() << ") ---> ";
                    else
                        file << a->getNoAdj() << " (" << a->getPeso() << ")";
                } else {
                    if (a->getProx() != NULL)
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

// *** GETTERS E SETTERS ***


void Grafo::setNo(int id, float peso) {

    No* no = new No(id, peso);

    No *list = this->listaNos;

    if (list == NULL) {
        this->listaNos = no;
        this->ordem = 1; // Inicializa a ordem
        return;
    }

    // Percorrendo lista de n�s at� encontrar o ultimo
    for (list; list->getProx() != NULL; list = list->getProx()) {
        if (list->getId() == no->getId()) {
            //cout << "No com mesmo id ja inserido" << endl;
            return;
        }
    }

    // Certificando se o n� j� n�o foi inserido
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

    // Percorrendo lista de n�s at� encontrar os n�s que ir�o receber a aresta
    for (list; list != NULL; list = list->getProx()) {

        if (list->getId() == idOrigem)
            origem = list;

        if (list->getId() == idFim)
            fim = list;

        // Evitando percorrer at� o final desnecess�riamente
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

    // Se o grafo n�o for direcional o n� de chegada tamb�m recebe uma aresta
    if (!this->direcional) {
        Aresta *fim_origem = new Aresta(idOrigem,idFim,peso);

        if (fim->setAresta(fim_origem))
            origem->aumentaGrauEntrada();

        // Atualizando o grau do grafo

        // Como ambos graus s�o atualizados para grafos n�o direcionais
        // Tanto faz verifivar o grau de sa�da ou entrada;
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
    // Verifica se o grafo � ponderado ou n�o da aresta para colocar um valour default
    if (!this->ponderadoAresta)
        this->setAresta(idOrigem, idFim, -1);
    else
        this->setAresta(idOrigem, idFim, 1);

}


No* Grafo::getNo(int id) {
    No *n=NULL;

    // Percorrendo lista de n�s at� encontrar o desejado
    for (n = this->listaNos; n != NULL && n->getId() != id; n = n->getProx());

    return n;
}

Aresta* Grafo::getAresta(int idOrigem, int idFim) {
    No *n = this->getNo(idOrigem); // Encontrando n� de origem

    // Se encontrar n� inicia a busca se n�o retorna NULL
    if (n != NULL) {
        Aresta* a = n->getAresta();

        // Procurando aresta com n� passado, se encontrar o retorna, se n�o retorna NULL
        for (a; a != NULL && a->getNoAdj() != idFim; a = a->getProx());

        return a;

    } else {
        return NULL;
    }

}

// *** REMO��O ***

void Grafo::removeAresta(int idOrigem, int idFim) {
    No *origem = this->getNo(idOrigem);  // Encontrando n� de inicio da aresta
    No *fim = this->getNo(idFim);        // Caso seja necess�rio manipular o n� de destino

    bool removeu = false;

    if (origem != NULL && fim != NULL) {

        removeu = origem->removeAresta(idFim); // Removendo aresta do n� de origem
        if (removeu)
            fim->diminuiGrauEntrada();   // Diminuindo grau de entrada do fim

        // Se o grafo n�o for direcional removemos tamb�m a aresta que indica a "volta"
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

    // Se o n� foi encontrado � retirado o n� e colocado os seguintes para o n� anterior
    if (encontrou) {

        grauNo = no->getGrauSaida();

        No *prox = no->getProx();
        bool removeu = false;

        if (ant == no)
            this->listaNos = prox;     // Se o n� for o primeiro reiniciamos a sequencia a partir do pr�ximo
        else
            ant->setProx(prox);        // Sen�o colocamos o seguinte no anterior

        no->setProx(NULL);          // Evita apagar o n� subsequente
        delete no;

        // Inicia remo��o de arestas ligadas a tal n� removido
        for (No *n = this->listaNos; n != NULL; n = n->getProx()) {
            removeu = n->removeAresta(id);

            if (removeu) {
                this->m--;             // Diminuindo n�mero de arestas se foi removido

                if (!this->direcional)  // Se n�o for direcional temos que diminuir o grau de entrada
                    n->diminuiGrauEntrada();
            }
        }

        if (this->direcional)          // Diminuindo arestas que saiam do n� removido (direcional)
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

/// Atualiza grau percorrendo todos os n�s do grafo e procura pelo maior grau
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
    int n_nos = 0; // Numero de n�s
    string line; // Auxilar para leitura de cada linha

    file.open(arquivo, ios::in); // Lendo arquivo de entrada

    if (file.is_open()) {

        getline(file, line); // Lendo a primeira linha com n�mero de n�s

        n_nos = stoi(line); // Convertendo de string para int

        //this->ordem = n_nos;

        // Percorrendo cada linha do arquivo e adicionando a variavel dados
        while (getline(file, line)) {

            istringstream str_stream(line);

            int origem, fim;
            float peso;

            // Verifica se � ponderado nas arestas
            if (this->ponderadoAresta) {

                // Lendo valores
                str_stream >> origem >> fim >> peso;

                // TODO implementar pensando que pode ser ponderado no n�

                // Inserindo n�s da aresta, a verifica�ao de existencia � feita pelo m�todo
                this->setNo(origem);
                this->setNo(fim);
                this->setAresta(origem,fim,peso);

            } else {

                // Lendo valores
                str_stream >> origem >> fim;

                // TODO implementar pensando que pode ser ponderado no n�

                // Inserindo n�s da aresta, a verifica�ao de existencia � feita pelo m�todo
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
//estou retornando uma lista do caminho at� chegar ao no desejado
Aresta* Grafo::caminho_largura(int id){
    //1� passo-> preciso procurar o no que posssui esse id
    No *no;
    no=getNo(id);
    No *raiz= this->listaNos;//aponta para o primeiro no da lista
    int auxTam=0;//guarda o tamanho exato do meu vetor aux. Dessa forma, n�o precisa percorrer o vetor todo.
    int aux[ordem];//lista de id na qual j� passei (ir� funcionar como uma estrutura de fila)
    No *auxVetorOrdem=NULL;// lista dos n�s com o id armazenado em aux
    Aresta *listaCaminho=NULL;//esta � a lista de n�s para chegar at� o n� procurado
    Aresta *auxPrimeiro=NULL;// guarda a �ltima aresta adj do n� visitada
    No *primeiro;//aponta para o primeiro vertice de aux
    if(raiz->getAresta()==NULL){
        cout<<"N�o tem aresta no n� raiz, ou seja, o n� n�o est� ligado a nenhum outro n�!";
        return NULL;
    }
    else{
        aux[0]=raiz->getId();
        No *w=NULL;
        auxPrimeiro=raiz->getAresta();
        w=getNo(auxPrimeiro->getNoAdj());
        Aresta *prox=NULL;// auxiliar para garantir que o cada aresta ser� armazenada no final da minha listaCaminho
        while(w->getId()!=no->getId() && auxTam != -1){//percorrer at� achar o no procurado ou at� a fila ficar vazia.
            getNo(aux[auxTam])->setMarca();
            primeiro=getNo(aux[0]);
            auxPrimeiro=primeiro->getAresta();
            w=getNo(auxPrimeiro->getNoAdj());//pego o id do n� adjacente a aresta

            for(w; w!=NULL && w->getId()!=no->getId(); w=getNo(auxPrimeiro->getNoAdj())){//w � um n� que procura os vizinhos do meu n� primeiro

                    if(listaCaminho!=NULL){
                        for(prox=listaCaminho;prox->getProx()!=NULL;prox=prox->getProx());
                        prox->setProx(new Aresta(w->getId(), primeiro->getId(),primeiro->getAresta()->getPeso()));
                    }
                    else
                       listaCaminho=(new Aresta(w->getId(), primeiro->getId(),primeiro->getAresta()->getPeso()));

                    if(w->getMarca()==false){
                        auxTam++;
                        aux[auxTam]=w->getId();
                    }

                    if(auxPrimeiro->getProx()==NULL){//avalia se o pr�ximo vizinho � vazio
                        break;
                    }
                    else
                        auxPrimeiro=auxPrimeiro->getProx();


            }
            for(int i=0;i<auxTam;i++){ //depois de armazenar as arestas dos vizinhos do primeiro, atualizo o primeiro para o pr�ximo n� vizinho
                    aux[i]=aux[i+1];
            }
            auxTam=auxTam-1; //atualizo o tamanho do meu vetor aux

        }
        for(prox=listaCaminho;prox->getProx()!=NULL;prox=prox->getProx()){};
        prox->setProx(new Aresta(w->getId(),primeiro->getId(),primeiro->getAresta()->getPeso()));
    }
    return listaCaminho;
}
//**Algoritmo de Prim**//
//retorna lista de arestas da �rvore geradora de custo m�nima
Aresta** Grafo::prim(){
    No *noAtual=NULL;
    int aux;
    int tamSolucao=0;//conta o tamanho de primVet
    int cont=0;//conta o tamanho da lista de arestas adjacentes do noAtual
    noAtual=this->listaNos;//n� atual de an�lise
    Aresta **primVet=new Aresta*[this->ordem];//vetor de arestas de menor peso
    Aresta *arestaAdj=NULL;//lista de arestas adjacentes aos noAtuais, que s�o atualizados na intera��o
    Aresta **arestaVet=new Aresta*[this->ordem];//auxilar para arestaAdj com o objetivo de ordenar
    //1� passo: transformar em um vetor de aresta
    //2� passo: pegar o vetor de arestas adjacentes e ordenar
    //3� passo: marcar o n� visitado
    //4� passo: pegar a primeira posi��o deste vetor
    //5� passo: atualizar o n� atual
    while(noAtual->getMarca()==false&&tamSolucao<this->ordem-1){
        arestaAdj=noAtual->getAresta();//recebeu uma lista de arestas adjacentes
        for(Aresta *w=arestaAdj;w!=NULL;w=w->getProx()){
            if(tamSolucao==0){//primeira vez que for inserir no vetor de arestas adjacentes
                arestaVet[cont]=new Aresta(w->getNoAdj(),w->getOrigemId(),w->getPeso());
                cont++;
            }
            else{//evitar a forma��o de ciclos
                for(aux=0;aux<cont&&getNo(arestaVet[aux]->getNoAdj())!=getNo(w->getNoAdj());aux++);//verificar se o n� adjacente da lista de arestaAdj j� foi inserido como n� adjacente da solu��o primVet
                if(aux==cont){//percorreu e n�o encontrou no adjacente igual ao da arestaVet
                    arestaVet[cont]=new Aresta(w->getNoAdj(),w->getOrigemId(),w->getPeso());
                    cont++;
                }
                else{
                    if(arestaVet[aux]->getPeso()>w->getPeso()){//se uma aresta com o n� adjacente a um j� pertencente ao vetor arestaVet tiver peso menor a aresta do vetor arestaVet, fa�o a substitui��o
                        arestaVet[aux]=new Aresta(w->getNoAdj(),w->getOrigemId(),w->getPeso());
                    }
                }
            }
        }

        this->ordenar(arestaVet,cont);
        if(getNo(arestaVet[0]->getNoAdj())->getMarca()==true){//se a menor aresta j� foi inserida, verifica a possibilidade de inserir at� achar uma que ainda n�o tenha sido inserida, na lista de arestas de menor peso
              for(aux=0;aux<tamSolucao && getNo(arestaVet[aux]->getNoAdj())->getMarca()==true;aux++);
              primVet[tamSolucao]=arestaVet[aux];
              tamSolucao++;
              noAtual->setMarca();
              noAtual=getNo(arestaVet[aux]->getNoAdj());
              for(int i=aux;i<cont-1;i++){
                  arestaVet[i]=arestaVet[i+1];
              }
              cont--;
        }
        else{
            primVet[tamSolucao]=arestaVet[0];
            tamSolucao++;
            noAtual->setMarca();
            noAtual=getNo(arestaVet[0]->getNoAdj());
            for(int i=0;i<cont-1;i++){
                arestaVet[i]=arestaVet[i+1];
            }
            cont--;
        }

    }
    return  primVet;
}
//fun��o para ordenar
int Grafo::binarySearch(Aresta **a, Aresta *item, int low, int high)
{
    if (high <= low){
       return (item->getPeso() > a[low]->getPeso())?  (low + 1): low;
    }


    int mid = (low + high)/2;
    if(item->getPeso() == a[mid]->getPeso())
        return mid+1;

    if(item->getPeso() > a[mid]->getPeso())
        return binarySearch(a, item, mid+1, high);

    return binarySearch(a, item, low, mid-1);
}
void Grafo:: ordenar(Aresta **a,int n){
    int i, loc, j, k;
    Aresta *selected=NULL;

    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = a[i];
        // find location where selected sould be inseretd
        loc = binarySearch(a, selected, 0, j);
        // Move all elements after location to create space
        while (j >= loc)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = selected;
    }
}
//Poda Steiner
//retirar os n�s que n�o est�o entre os n�s terminais
//void Grafo::poda(No **solucao,int n){
//    int i=0;//serve de auxiliar para procurar um no de grau 1
//    for(i=0;i<n&&solucao[i]->getGrauEntrada()==1;i++);
//    if(getNo(this->terminais[i]);
//}
