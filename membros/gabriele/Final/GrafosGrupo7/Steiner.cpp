/**
    Universidade Federal de Juiz de Fora
    Steiner.cpp

    @author Victor Aquiles
    @version 1.0 01/04/19
*/

#include <iostream>
#include "Steiner.h"

using namespace std;


Steiner::Steiner(Grafo *grafo)
{
    this->g = grafo;
    this->terminais = grafo->getTerminais();
    this->tam_terminais = grafo->getNumTerminais();
}

void Steiner::gerarSemente()
{
    // seed do random baseado no tempo
    semente = time(NULL);
    srand (semente);
}
int Steiner::getSemente()
{
    return semente;
}
void Steiner::setSemente(int semente)
{
    this->semente = semente;
    srand (semente);
}

/*========================================================================*/
/*===================== Algoritmo Guloso Randomizado =====================*/
/*========================================================================*/


float Steiner::GulosoRandomizado(float alfa, int maxiter)
{
    Grafo* steinerSol=new Grafo(false,true,false);
    No** solucao = new No*[this->g->getOrdem()];
    No** solucao_adj = new No*[this->g->getOrdem()];
    int it = 0;
    float custo = 0;
    Grafo* recebeKruskal;

    int tam_sol = 0;
    int tam_adj = 0;
    // Preenchendo o vetor de solucao
    for(tam_sol=0;tam_sol < tam_terminais;tam_sol++){
        solucao[tam_sol]=this->g->getNo(terminais[tam_sol]);
        solucao[tam_sol]->set_marcaTerminal();
    }
    //Preeenchendo solucao_adj
    for (tam_sol = 0; tam_sol < tam_terminais; tam_sol++) {


        No* n = this->g->getNo(terminais[tam_sol]);

        n->set_marcaTerminal();


        for (Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) {
            No* adj = this->g->getNo(a->getNoAdj());
            if(adj->get_marcaTerminal()==false&& adj->getMarca()==false) { // Evita inserir nós repetidos
                solucao_adj[tam_adj] = adj;
                adj->setMarca();
                tam_adj++;
            }
        }

    }


    this->ordenaAdj(solucao_adj, solucao, tam_adj, tam_sol);

    //preencher o grafo da solucao com os terminais
    for(int i=0;i<this->tam_terminais;i++){
        solucao[i]->setMarca();
        steinerSol->adicionaNo(solucao[i]->getId(),1);
    }


    while (steinerSol->getConexo()==false&&it < maxiter) {
        int param = alfa * (tam_adj - 1);

        // Adicionando um no adjacente a solucao
        solucao[tam_sol] = solucao_adj[0];

        Grafo *grafoInduzido=steinerSol->subgrafoInduzido(solucao,tam_sol);
        //aqui chama o kruskal
        recebeKruskal=grafoInduzido->KruskalAGM(&custo);
        steinerSol=recebeKruskal;
        tam_sol++;

        // Atualizando vetor de nós adjacentes com o nós adjacentes ao recém adicionado
        tam_adj = this->atualizaLista(solucao_adj, tam_adj, 0);
        this->ordenaAdj(solucao_adj, solucao, tam_adj, tam_sol);

        it++;
    }
    //retira os nós que não se encontram entre os terminais
    //    poda(recebeKruskal);

    //retorna a arvore de Steiner
    return recebeKruskal->getCusto();
}



int Steiner::binarySearch(float a[], int item, int low, int high) {
    if (high <= low)
        return (item > a[low])?  (low + 1): low;

    int mid = (low + high)/2;

    if(item == a[mid])
        return mid+1;

    if(item > a[mid])
        return binarySearch(a, item, mid+1, high);
    return binarySearch(a, item, low, mid-1);
}

// Function to sort an array a[] of size 'n'
void Steiner::ordenaAdj(No** adj, No** sol, int tam_adj, int tam_sol) {
    int i, loc, j, k;
    No* selected_adj;
    float selected;

    // Preenchendo pesos com valores muito grandes
    float* pesos = new float[tam_adj];
    for (int c = 0; c < tam_adj; c++) pesos[c] = 9999999999.9;

    // Percorrendo vetor de solucao adjacente para encontrar as suas aretas de menor peso ligadas a solução
    for (int c = 0; c < tam_adj; c++) {

        No* atual_adj = adj[c];

        for (int s = 0; s < tam_sol; s++) { // Percorrendo nós da solucao
            No* n = sol[s];

            for (Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) { // Percorrendo arestas da solucao
                if (a->getNoAdj() == atual_adj->getId() && pesos[c] > a->getPeso())
                    pesos[c] = a->getPeso();
            }

        }
    }

    // Ordenando solucao de adj em relação aos pesos das arestas
    for (i = 1; i < tam_adj; ++i) {
        j = i - 1;
        selected = pesos[i];
        selected_adj = adj[i];

        // find location where selected sould be inseretd
        loc = binarySearch(pesos, selected, 0, j);

        // Move all elements after location to create space
        while (j >= loc)
        {
            pesos[j+1] = pesos[j];
            adj[j+1] = adj[j];
            j--;
        }
        pesos[j+1] = selected;
        adj[j+1] = selected_adj;
    }
}

int Steiner::atualizaLista(No** adja, int tam, int pos) {
    No* novo = adja[pos];

    // Adicionando nós adjacentes ao nó em pos
    for (Aresta *a = novo->getAresta(); a != nullptr; a = a->getProx()) {
        No* adj = this->g->getNo(a->getNoAdj());

        if(!adj->getMarca()) {
            adja[tam] = adj;
            adj->setMarca();
            tam++;
        }
    }

    // removendo nó em pos
    for (int i = pos; i < tam; i++) {
        adja[i] = adja[i+1];
    }
    adja[tam-1] = nullptr; // removendo ultima posicao
    tam--;

    return tam;
}

//Poda da árvore
//retirar nós de grau 1 que não estejam no caminho entre os terminais
void Steiner::poda(Grafo* grafo_novo)
{
    //1º passo: fazer um vetor com os terminais
    //2º passo: procurar nó que tenha grau 1 com a função auxpoda, por meio de uma recursao

    No** term=new No *[this->tam_terminais];

    for(int i=0;i<this->tam_terminais;i++){
        term[i]=grafo_novo->getNo(this->terminais[i]);
        term[i]->set_marcaTerminal();

    }

    No* noAdj=grafo_novo->getNo(this->terminais[0]);
    auxPoda(grafo_novo, noAdj, noAdj);
}
void Steiner::auxPoda(Grafo* grafo_novo, No *aux, No *ant)
{
    if(aux->getGrauEntrada()==1){//caso base: encontrar nó de grau 1
        if(aux->get_marcaTerminal() != true){// se nao for terminal remove
             grafo_novo->removeNo(aux->getId());
        }
    } else {

        Aresta* adjacente=aux->getAresta();
        while(adjacente!=NULL){
            if(ant->getId() != adjacente->getNoAdj()){
                auxPoda(grafo_novo, grafo_novo->getNo(adjacente->getNoAdj()), aux);
            }
            adjacente = adjacente->getProx();
        }

    }

    if(aux->getGrauEntrada()==1){
        if(aux->get_marcaTerminal() != true){
             grafo_novo->removeNo(aux->getId());
        }
    }

}


/*========================================================================*/
/*================= Algoritmo Guloso Randomizado Reativo =================*/
/*========================================================================*/


float Steiner::GulosoRandomizadoReativo(int maxiter)
{
    int B = 10;//bloco de iteracoes
    int max_alfas = 100;//quantidade de alfas
    float *alfas = new float[max_alfas];
    int cont=0;//iteracoes do bloco
    float sum_custo=0;
    float *S = new float[max_alfas];
    float S_estrela = 0;
    float *P = new float[max_alfas];
    int indexAlfa=-1;

    //inicia com solução gulosa
    S_estrela = GulosoRandomizado(0, 1);

    for (int i=0; i<maxiter; i++)
    {
        if(i%B == 0){
            atualizaProb(alfas, cont, sum_custo, S, S_estrela, P);
        }
        indexAlfa = selecionaAlfa(P);
        S[indexAlfa] = GulosoRandomizado(alfas[indexAlfa], 1);

        if(S[indexAlfa] < S_estrela){
            S_estrela = S[indexAlfa];
        }

        atualizaVetores(S, indexAlfa, cont, sum_custo);

    }
    return 0;
}

void Steiner::atualizaProb(float *alfas, int cont, float sum_custo, float *S, float S_estrela, float *P)
{

}

void Steiner::atualizaVetores(float *S, int indexAlfa, int cont, float sum_custo)
{

}

int Steiner::selecionaAlfa(float *P)
{
    return 0;
}



/*========================================================================*/
/*================ Algoritmo Heurística de Caminho Mínimo ================*/
/*========================================================================*/


float Steiner::ConstrutivoHeuristicaCaminhoMinimo()
{
    int *S = new int[g->getOrdem()];
    S[0] = terminais[0];
    int n_sol = 1;

    int *C = new int[tam_terminais];
    int n_can = 0;
    for(int j=1; j<tam_terminais;j++){
        C[n_can] = terminais[j];
        n_can++;
    }

    //processa o floyd uma unica vez
    cout << "Processando Floyd" << endl;
    Floyd *floyd = new Floyd(g, g->getMatrizAdj());

    //inicia o grafo solucao
    Grafo *h = new Grafo(false, true, false);

    cout << "Processando algoritmo" << endl;

    while(n_can > 0){
        float custo = 99999999999999.9;
        int id_origem_escolhido=-1;
        int id_destino_escolhido=-1;

        for(int i=0; i<n_sol;i++){
            int id_sol = S[i];

            for(int j=0; j<n_can;j++){
                int id_can = C[j];
                float peso = floyd->getDistancia(id_sol, id_can);

                //cout << id_sol << " " << id_can << " " << peso << endl;
                if(peso < custo){
                    custo = peso;
                    id_origem_escolhido = id_sol;
                    id_destino_escolhido = id_can;
                }
            }

        }

        if(id_origem_escolhido != -1){
            Aresta *aux = floyd->getCaminhoAresta(id_origem_escolhido, id_destino_escolhido);
            while(aux != NULL){
                //cout << "Add Aresta: (" << aux->getOrigem() << ", " << aux->getNoAdj() << ") " << aux->getPeso() << endl;
                h->adicionaAresta(aux->getOrigem(), 1, aux->getNoAdj(), 1, aux->getPeso());
                aux = aux->getProx();
            }
            remover(C, &n_can, id_destino_escolhido);
            adicionar(S, &n_sol, id_destino_escolhido);

            cout << n_sol << " de " << tam_terminais << endl;

        } else {
            cout << "Steiner::ConstrutivoHeuristicaCaminhoMinimo: O grafo nao e conexo!" << endl;
            return NULL;
        }

    }

    return h->getCusto();

}

void Steiner::remover(int *vetor, int *tam, int valor)
{
    //encontra
    int indice = -1;
    for(int i=0; i<*tam; i++){
        if(vetor[i] == valor){
            indice = i;
            break;
        }
    }
    //desloca
    if(indice != -1){
        for(int i=indice+1; i<*tam; i++){
            vetor[i-1] = vetor[i];
        }
    }
    *tam = *tam - 1;
}
void Steiner::adicionar(int *vetor, int *tam, int valor)
{
    vetor[*tam] = valor;
    *tam = *tam + 1;
}

