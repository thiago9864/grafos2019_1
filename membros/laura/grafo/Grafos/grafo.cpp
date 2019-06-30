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

// Fun��o que retorna o n�mero de componentes conexas presentes no grafo.
// Tamb�m possibilita a identifica��o de qual v�rtice pertence a qual componente a partir do vetor indComp, que ser� modificado
// durante a execu��o.
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

// Fun��o que retorna o subgrafo induzido por um conjunto de n�s passado por par�metro.
Grafo* Grafo::subgrafoInduzido(No **solucao, int tam)
{
    Aresta **subInduzido = new Aresta*[this->m]; // Vetor que recebe as arestas que far�o parte do subgrafo induzido.
    int contAresta = 0;
    Aresta *arestaAdj;
    bool verifica[ordem]; // Vetor auxiliar que ser� utilizado para que n�o haja repeti��o de arestas adicionadas a 'subInduzido'.
    int idNos[ordem]; // Vetor que ser� preenchido com os ids dos n�s do grafo.
    vetorIdNos(idNos);

    for(int i = 0; i < ordem; i++) {
        verifica[i] = false;
    }

    for(int i = 0; i < tam; i++) { // Encontra as arestas do grafo que posuem ambas as extremidades em 'solucao' e as adiciona ao vetor 'subInduzido'.
        int a = encontraIndice(idNos, solucao[i]->getId());
        for(arestaAdj = solucao[i]->getAresta(); arestaAdj != nullptr; arestaAdj = arestaAdj->getProx()) {
            int noAd = arestaAdj->getNoAdj();
            int b = encontraIndice(idNos, noAd);

            for(int j = 0; j < tam; j++) {
                if(noAd == solucao[j]->getId()) {
                    if(verifica[b] != true) {
                        subInduzido[contAresta] = arestaAdj;
                        contAresta++;
                    }
                    break;
                }
            }
        }

        verifica[a] = true;
    }

    Grafo *h = new Grafo(); // Cria-se o grafo que ir� receber as arestas de 'subInduzido'.
    h->ponderadoAresta = true;
    h->m = 0;
    h->grau = 0;

    if(contAresta > 0) {
        for(int i = 0; i < contAresta; i++) { // Cria em 'h' as arestas com as mesmas caracter�sticas das presentes em 'subInduzido'.
            int origem = subInduzido[i]->getOrigem();
            int fim = subInduzido[i]->getNoAdj();
            float peso = subInduzido[i]->getPeso();

            h->setNo(origem);
            h->setNo(fim);
            h->setAresta(origem, fim, peso);
        }
    }

    for(int i = 0; i < tam; i++) { // Adiciona ao grafo os n�s que n�o foram adicionados anteriormente (possivelmente n�s isolados).
        if(h->getNo(solucao[i]->getId()) == nullptr) {
            h->setNo(solucao[i]->getId());
        }
    }

    return h;
}

// Fun��o que retorna o subgrafo correspondente � �rvore geradora m�nima do grafo.
Grafo* Grafo::kruskal(float *soma)
{
    Aresta arestasAGM[getOrdem() - 1];
    *soma = auxKruskal(arestasAGM); // Chama a fun��o 'auxKruskal' e encontra as arestas da �rvore geradora m�nima.

    Grafo *h = new Grafo(); // Cria-se o grafo que ir� receber as arestas encontradas por 'auxKruskal'.
    h->ponderadoAresta = true;
    h->m = 0;
    h->grau = 0;
    for(int i = 0; i < getOrdem() - 1; i++) { // Cria em 'h' as arestas com as mesmas caracter�sticas das presentes em 'arestasAGM'.
        int origem = arestasAGM[i].getOrigem();
        int fim = arestasAGM[i].getNoAdj();
        float peso = arestasAGM[i].getPeso();

        h->setNo(origem);
        h->setNo(fim);
        h->setAresta(origem, fim, peso);
    }

    return h;
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
            // Se for ponderado nas arestas � imprimido o peso
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
        for (No *n = this->listaNos; n != nullptr; n = n->getProx()) {

            file << n->getId() << " ---> ";

            for (Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) {
                // Se for ponderado nas arestas � imprimido o peso
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

int Grafo::getNoPos(int id) {
    int c = 0;
    for (No* n = this->listaNos; n->getId() != id; n = n->getProx(), c++);
    return c;
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

    // Percorrendo lista de n�s at� encontrar o ultimo
    for (list; list->getProx() != nullptr; list = list->getProx()) {
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
    No * origem = nullptr;
    No * fim = nullptr;

    // Evitando self loops
    if (idOrigem == idFim) {
        cout << "Nao e permitido self-loop" << endl;
        return;
    }

    // Percorrendo lista de n�s at� encontrar os n�s que ir�o receber a aresta
    for (list; list != nullptr; list = list->getProx()) {

        if (list->getId() == idOrigem)
            origem = list;

        if (list->getId() == idFim)
            fim = list;

        // Evitando percorrer at� o final desnecess�riamente
        if (origem != nullptr && fim != nullptr) break;

    }

    if (origem != nullptr && fim != nullptr) {
        Aresta *origem_fim = new Aresta(idOrigem, idFim, peso);

        if (origem->setAresta(origem_fim))
            fim->aumentaGrauEntrada();

    } else {
        cout << "No nao encontrado" << endl;
        return;
    }

    // Se o grafo n�o for direcional o n� de chegada tamb�m recebe uma aresta
    if (!this->direcional) {
        Aresta *fim_origem = new Aresta(idFim, idOrigem, peso);

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
    No *n;

    // Percorrendo lista de n�s at� encontrar o desejado
    for (n = this->listaNos; n != nullptr && n->getId() != id; n = n->getProx());

    return n;
}

No* Grafo::getNo() {
    return this->listaNos;
}

Aresta* Grafo::getAresta(int idOrigem, int idFim) {
    No *n = this->getNo(idOrigem); // Encontrando n� de origem

    // Se encontrar n� inicia a busca se n�o retorna nullptr
    if (n != nullptr) {
        Aresta* a = n->getAresta();

        // Procurando aresta com n� passado, se encontrar o retorna, se n�o retorna nullptr
        for (a; a != nullptr && a->getNoAdj() != idFim; a = a->getProx());

        return a;

    } else {
        return nullptr;
    }

}

int Grafo::getOrdem()
{
    return ordem;
}

bool Grafo::getDirecional()
{
    return direcional;
}


// *** REMO��O ***

void Grafo::removeAresta(int idOrigem, int idFim) {
    No *origem = this->getNo(idOrigem);  // Encontrando n� de inicio da aresta
    No *fim = this->getNo(idFim);        // Caso seja necess�rio manipular o n� de destino

    bool removeu = false;

    if (origem != nullptr && fim != nullptr) {

        removeu = origem->removeAresta(idFim); // Removendo aresta do n� de origem
        if (removeu)
            fim->diminuiGrauEntrada();   // Diminuindo grau de entrada do fim

        // Se o grafo n�o for direcional removemos tamb�m a aresta que indica a "volta"
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

    // Se o n� foi encontrado � retirado o n� e colocado os seguintes para o n� anterior
    if (encontrou) {

        grauNo = no->getGrauSaida();

        No *prox = no->getProx();
        bool removeu = false;

        if (ant == no)
            this->listaNos = prox;     // Se o n� for o primeiro reiniciamos a sequencia a partir do pr�ximo
        else
            ant->setProx(prox);        // Sen�o colocamos o seguinte no anterior

        no->setProx(nullptr);          // Evita apagar o n� subsequente
        delete no;

        // Inicia remo��o de arestas ligadas a tal n� removido
        for (No *n = this->listaNos; n != nullptr; n = n->getProx()) {
            removeu = n->removeAresta(id);

            if (removeu) {
                this->m--;             // Diminuindo n�mero de arestas se foi removido

                if (!this->direcional) // Se n�o for direcional temos que diminuir o grau de entrada
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


// Fun��o auxiliar recursiva que executa uma busca em profundidade para encontrar as componentes conexas do grafo.
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

void Grafo::vetorIdNos(int* idNos) // Fun��o auxiliar que preenche o vetor com os ids dos n�s da lista.
{
    No *n;
    int i;
    for(n = listaNos, i = 0; n != nullptr; n = n->getProx(), i++) {
        idNos[i] = n->getId();
    }

}

int Grafo::encontraIndice(int *idNos, int id) // Fun��o auxiliar que encontra a posi��o "i" de um id em um vetor idNos.
{
    int i;
    for(i = 0; i < ordem; i++) {
        if(idNos[i] == id) {
            break;
        }
    }
    return i;
}

// Fun��o auxiliar que realiza a troca de posi��es entre valores dos vetores passados como par�metro.
void Grafo::troca(float *pesos, Aresta *conj, int i, int j)
{
    float pAux = pesos[i];
    pesos[i] = pesos[j];
    pesos[j] = pAux;

    Aresta aAux = conj[i];
    conj[i] = conj[j];
    conj[j] = aAux;
}

// Fun��o auxiliar que retorna o �ndice da parti��o do QuickSort. Utiliza-se como piv� a �ltima posi��o do vetor.
int Grafo::particao(float *pesos, Aresta *conj, int inicio, int fim)
{
    float pivo = pesos[fim];
    int i = inicio - 1;

    for(int j = inicio; j < fim; j++) {
        if(pesos[j] <= pivo) {
            i++;
            troca(pesos, conj, i, j);
        }
    }
    troca(pesos, conj, i + 1, fim);

    return (i + 1);
}

// Fun��o recursiva que implementa um QuickSort para fazer a ordena��o dos vetores passados como par�metro.
void Grafo::ordenaVetor(float *pesos, Aresta *conj, int inicio, int fim)
{
    if(inicio < fim) {
        int indPart = particao(pesos, conj, inicio, fim);

        ordenaVetor(pesos, conj, inicio, indPart - 1);
        ordenaVetor(pesos, conj, indPart + 1, fim);
    }
}

// Fun��o usada para encontrar o conjunto de arestas da �rvore geradora m�nima de um grafo.
// Retorna a soma dos pesos das arestas desse conjunto.
float Grafo::auxKruskal(Aresta *arestasAGM)
{
    if(direcional == false) {
        int cont = 0;
        bool verifica[ordem]; // Vetor auxiliar que ser� utilizado para que n�o haja repeti��o de arestas adicionadas a 'conjArestas'.
        Aresta conjArestas[m]; // Vetor que ser� preenchido com todas as arestas do grafo (conjunto de arestas candidatas � solu��o).
        int idNos[ordem]; // Vetor que ser� preenchido com os ids dos n�s do grafo.
        vetorIdNos(idNos);
        float pesosArestas[m]; // Vetor que ser� preenchido com os pesos das arestas do grafo.

        Aresta *a;
        No *n;
        int i;

        for(int i = 0; i < ordem; i++) {
            verifica[i] = false;
        }

        int r = 0;
        for(i = 0, n = listaNos; i < ordem && n != nullptr; i++, n = n->getProx()) { // Preenche 'conjArestas' com as arestas do grafo.
            for(a = n->getAresta(); a!= nullptr; a = a->getProx()) {
                int j = encontraIndice(idNos, a->getNoAdj()); // Encontra �ndice do vetor 'idNos' correspondente ao id do n� adjacente � aresta em quest�o.

                if(verifica[j] != true) { // Checa se a aresta j� se encontra em 'conjArestas'.
                    conjArestas[r] = *a; // Adiciona aresta a 'conjArestas'.
                    r++; // Passar� para a pr�xima posi��o do vetor 'conjArestas'.
                }
            }

            verifica[i] = true; // Marca no vetor auxiliar 'verifica' que todas as arestas que possuem o n� de �ndice 'i' em 'idNos' como extremidade j� foram colocadas em 'conjArestas'.
        }

        for(int i = 0; i < m; i++) { // Preenche 'pesosArestas' com os pesos das arestas do grafo.
            pesosArestas[i] = conjArestas[i].getPeso();
        }

        // Ordena em ordem crescente o vetor 'pesosArestas' e o vetor 'conjArestas'.
        ordenaVetor(pesosArestas, conjArestas, 0, m - 1);

        int comp[ordem]; // Vetor que indicar� a quais componentes conexas cada n� do grafo pertence (ao longo do processo).
        for(int i = 0; i < ordem; i++) { // Inicialmente, temos o n�mero de componentes conexas igual ao n�mero de n�s.
            comp[i] = idNos[i];
        }

        i = 0;

        while(i < m && cont < ordem - 1) { // Preenche 'arestasAGM' com as arestas que formar�o a �rvore geradora m�nima do grafo.
            int a = encontraIndice(idNos, conjArestas[i].getOrigem());
            int b = encontraIndice(idNos, conjArestas[i].getNoAdj());
            if(comp[a] != comp[b]) { // Se os n�s pertencem a componentes conexas distintas, � poss�vel a adi��o da aresta � solu��o (pois n�o se formar� um ciclo).
               arestasAGM[cont] = conjArestas[i]; // Adiciona a aresta � solu��o.
               cont++;
               if(comp[a] < comp[b]) { // N�s que pertencem � mesma componente ficam com o valor de id do n� de menor id da componente.
                  int t = comp[b];
                  comp[b] = comp[a];
                for(int f = 0; f < ordem; f++) {
                    if(comp[f] == t) {
                        comp[f] = comp[a];
                    }
                }
               }
               else {
                int p = comp[a];
                comp[a] = comp[b];
                for(int f = 0; f < ordem; f++) {
                    if(comp[f] == p) {
                        comp[f] = comp[b];
                    }
                }
               }
            }

            i++;
        }

        float somaPesos = 0.0;
        for(int c = 0; c < ordem - 1; c++) { // Soma os pesos das arestas que est�o na solu��o.
            somaPesos += arestasAGM[c].getPeso();
        }

        return somaPesos;
    }

    return -1.0;
}


/// Atualiza grau a partir de um grau passado como parametro
void Grafo::atualizaGrau(int grau) {
    if (grau > this->grau)
        this->grau = grau;
}

/// Atualiza grau percorrendo todos os n�s do grafo e procura pelo maior grau
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
