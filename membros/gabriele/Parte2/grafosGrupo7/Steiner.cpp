/**
    Universidade Federal de Juiz de Fora
    Steiner.cpp

    @author Victor Aquiles
    @version 1.0 01/04/19
*/

#include <iostream>
#include "Steiner.h"

using namespace std;


Steiner::Steiner(int* terminais, int tam_terminais) {
    this->terminais = terminais;
    this->tam_terminais = tam_terminais;
}

int* Steiner::steiner(float alfa, int maxiter) {
    Grafo* steinerSol;
    No** solucao = new No*[this->g->getOrdem()];
    No** solucao_adj = new No*[this->g->getOrdem()];
    int it = 0;

    srand (time(NULL)); // seed do random baseado no tempo

    int tam_sol = 0;
    int tam_adj = 0;
    // Preenchendo o vetor de solucao e solucao_adj
    for (tam_sol = 0; tam_sol < tam_terminais; tam_sol++) {
        solucao[tam_sol] = this->g->getNo(terminais[tam_sol]);

        No* n = this->g->getNo(terminais[tam_sol]);

        for (Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) {
            No* adj = this->g->getNo(a->getNoAdj());

            if(!adj->getMarca()) { // Evita inserir nós repetidos
                solucao_adj[tam_adj] = adj;
                adj->setMarca();
                tam_adj++;
            }
        }

    }

    this->ordenaAdj(solucao_adj, solucao, tam_adj, tam_sol);

    while (it < maxiter) {
        int param = alfa * (tam_adj - 1);
        int r = rand() % param;

        // Adicionando um no adjacente a solucao
        solucao[tam_sol] = solucao_adj[r];
        tam_sol++;

        // Atualizando vetor de nós adjacentes com o nós adjacentes ao recém adicionado
        tam_adj = this->atualizaLista(solucao_adj, tam_adj, r);
        this->ordenaAdj(solucao_adj, solucao, tam_adj, tam_sol);

        it++;
    }
    return nullptr;
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

int Steiner::atualizaLista(No** adj, int tam, int pos) {
    No* novo = adj[pos];

    // Adicionando nós adjacentes ao nó em pos
    for (Aresta *a = novo->getAresta(); a != nullptr; a = a->getProx()) {
        No* adj = this->g->getNo(a->getNoAdj());

        if(!adj->getMarca()) {
            adj[tam] = *adj;
            adj->setMarca();
            tam++;
        }
    }

    // removendo nó em pos
    for (int i = pos; i < tam; i++) {
        adj[i] = adj[i+1];
    }
    adj[tam-1] = nullptr; // removendo ultima posicao
    tam--;

    return tam;
}



//Poda da árvore
//retirar nós de grau 1 que não estejam no caminho entre os terminais
void Steiner::poda(Grafo* grafo_novo){
    //andar no grafo apartir de um nó terminal e ver seus adjacentes->um terminal por vez
    //depois vê o o grafo inteiro
    //1º passo: fazer um vetor com os terminais
    //2º passo: procurar nó que tenha grau 1

    No** term=new No *[this->tam_terminais];


    for(int i=0;i<this->tam_terminais;i++){
        term[i]=grafo_novo->getNo(this->terminais[i]);
        term[i]->set_marcaTerminal();

    }

    for(int i=0;i<this->tam_terminais;i++){
        for(Aresta* adjacente=term[i]->getAresta();adjacente!=NULL;adjacente=adjacente->getProx()){

             No* noAdj=grafo_novo->getNo(adjacente->getNoAdj());
             if(noAdj->getGrauEntrada()==1){
                 cout<<"1"<<endl;
                grafo_novo->removeNo(noAdj->getId());
             }
             else{
                 cout<<"nao grau 1"<<endl;
                 cout<<"noAdj:"<<noAdj->getId()<<endl;
                auxPoda(grafo_novo,noAdj);//verifica a possibilidade de achar nós de grau 1 que nao estão no caminho dos terminais
             }
        }
    }

}
void Steiner::auxPoda(Grafo* grafo_novo,No* aux){//retira de forma recursiva os nós de grau 1
    cout<<"aux:"<<aux->getId()<<endl;
    if(aux->getGrauEntrada()==1){
         cout<<"2"<<endl;
        if(aux->get_marcaTerminal()!=true){
             grafo_novo->removeNo(aux->getId());
        }
        return;
    }
    else{
        Aresta* adjacente=aux->getAresta();
        while(adjacente!=NULL){//verifica os adjacentes ao nó original
            cout<<"3"<<endl;
            auxPoda(grafo_novo,grafo_novo->getNo(adjacente->getNoAdj()));

            adjacente=adjacente->getProx();

        }
        if(aux->get_marcaTerminal()==false&&aux->getGrauEntrada()==1){
            grafo_novo->removeNo(aux->getId());
            return;
        }

    }
}
