/**
    Universidade Federal de Juiz de Fora
    Steiner.cpp

    @author Victor Aquiles
    @version 1.0 01/04/19
*/

#include <iostream>
#include <math.h>
#include "Steiner.h"

using namespace std;


Steiner::Steiner(Grafo *grafo)
{
    this->g = grafo;
    this->terminais = grafo->getTerminais();
    this->tam_terminais = grafo->getNumTerminais();
    this->solucaoGulosa = -1;
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

uint64_t Steiner::unix_timestamp()
{
    uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return now;
}

/*========================================================================*/
/*===================== Algoritmo Guloso Construtivo =====================*/
/*========================================================================*/

float Steiner::GulosoConstrutivo() {
    Grafo *steinerSol = NULL;
    No** solucao = new No*[this->g->getOrdem()];
    No** solucao_adj = new No*[this->g->getOrdem()];
    int tam_sol = 0;
    int tam_adj = 0;
    bool isConexo = false;
    float custo=0;
    int cont=0;

    // Preenchendo o vetor de solucao
    for(tam_sol=0;tam_sol < tam_terminais;tam_sol++){
        solucao[tam_sol]=this->g->getNo(terminais[tam_sol]);
    }

    //preenche os vetores pra primeira execução
    atualizaLista(solucao, tam_sol, solucao_adj, &tam_adj);

    while(!isConexo && tam_adj > 0){

        //ordena a solução_adj do menor para o maior
        this->ordenaAdj(solucao_adj, solucao, tam_adj, tam_sol);

        //coloca o melhor vertice da solução_adj
        solucao[tam_sol] = solucao_adj[0];
        tam_sol++;

        //limpa a memória alocada pelo subgrafo induzido
        if(steinerSol != NULL){
            delete steinerSol;
            steinerSol = NULL;
        }

        //gera subgrafo induzido
        steinerSol=g->subgrafoInduzido(solucao, tam_sol);

        //verifica se é conexo
        if(steinerSol->getNumArestas() < (steinerSol->getOrdem()-1)){
            isConexo = false;
        } else {
            isConexo = steinerSol->getConexo();
        }

        //atualiza os vetores para próxima execução
        atualizaLista(solucao, tam_sol, solucao_adj, &tam_adj);

        //exibe info
        if(cont>30 && g->getOrdem() > 400){
            cout << "Processando: tam_sol: " << tam_sol << ", tam_adj: " << tam_adj << endl;
            cont=0;
        }
        cont++;
    }

    //gera a arvore da solucao
    Grafo *steinerTree = steinerSol->KruskalAGM(&custo);
    delete steinerSol;
    steinerSol = NULL;

    // marca os terminais na solução encontrada para a poda poder reconhecer eles
    for(int i=0;i < tam_terminais;i++){
        steinerTree->setTerminal(terminais[i], tam_terminais);
    }

    //executa a poda da arvore de solução
    poda(steinerTree);

    //obtem o custo da arvore e salva o resultado da solução gulosa pra uso futuro
    custo = steinerTree->getCusto();
    solucaoGulosa = custo;

    //desaloca memória usada
    for(int i=0;i < tam_sol;i++){
        solucao[i] = NULL;
    }
    for(int i=0;i < tam_adj;i++){
        solucao_adj[i] = NULL;
    }
    delete steinerTree;
    delete[] solucao;
    delete[] solucao_adj;
    steinerTree = NULL;
    solucao = NULL;
    solucao_adj = NULL;

    //retorna o custo da arvore de solução
    return custo;
}



/*========================================================================*/
/*===================== Algoritmo Guloso Randomizado =====================*/
/*========================================================================*/



float Steiner::GulosoRandomizado(float alfa, int maxiter)
{
    Grafo* steinerSol = NULL;
    No** solucao = NULL;
    No** solucao_adj = NULL;
    int it = 0;
    float custo = 0;
    int tam_sol = 0;
    int tam_adj = 0;
    bool isConexo = false;

    float melhorGrafo = solucaoGulosa;
    if(solucaoGulosa == -1){
        cout << "Obtem uma solução gulosa" << endl;
        melhorGrafo=this->GulosoConstrutivo();
    }

    cout << "Inicia randomizado com " << maxiter << " iteracoes" << endl;
    while(it < maxiter){//roda maxiter e pega melhor resultado entre os grafos gerados
        int cont=0;
        int m = 0;
        int n = 0;
        solucao = new No*[this->g->getOrdem()];
        solucao_adj = new No*[this->g->getOrdem()];
        tam_sol = 0;
        tam_adj = 0;
        isConexo = false;

        // Preenchendo o vetor de solucao
        for(tam_sol=0;tam_sol < tam_terminais;tam_sol++){
            solucao[tam_sol]=this->g->getNo(terminais[tam_sol]);
        }

        this->atualizaLista(solucao, tam_sol,solucao_adj, &tam_adj);

        while (isConexo==false&&tam_adj>0) {

            //gera o numero aleatorio correspondente ao alfa
            int param = alfa * (tam_adj - 1);
            int r= rand()% param;

            //ordena o vetor adjacente
            this->ordenaAdj(solucao_adj, solucao, tam_adj, tam_sol);

            // Adicionando um no aleatório adjacente a solucao
            solucao[tam_sol] = solucao_adj[r];
            tam_sol++;

            //desaloca memória
            if(steinerSol != NULL){
                delete steinerSol;
                steinerSol = NULL;
            }

            //gera um subgrafo induzido do conjunto solução
            steinerSol=g->subgrafoInduzido(solucao, tam_sol);

            //verifica se é conexo
            m = steinerSol->getNumArestas();
            n = steinerSol->getOrdem();
            if(m < (n-1)){
                isConexo = false;
            } else {
                isConexo = steinerSol->getConexo();
            }


            // Atualizando vetor de nós adjacentes com o nós adjacentes ao recém adicionado
            this->atualizaLista(solucao, tam_sol,solucao_adj, &tam_adj);

            if(cont>30 && g->getOrdem() > 400){
                cout<<"Processando: tam_sol: "<<tam_sol<<", tam_adj:"<<tam_adj << endl;
                //cout << ", subgrafoInduzido: |V| = " << n << ", |E| = " << m << endl;
                cont=0;
            }
            cont++;
        }

        //calcula a AGM do grafo conexo
        Grafo*steinerTree = steinerSol->KruskalAGM(&custo);
        delete steinerSol;
        steinerSol = NULL;

        // marca os terminais na solução
        for(int i=0;i < tam_terminais;i++){
            steinerTree->setTerminal(terminais[i], tam_terminais);
        }

        //poda a arvore obtida
        poda(steinerTree);

        //testa o custo pra atualizar a melhor arvore
        float aux=steinerTree->getCusto();
        if(melhorGrafo>aux){
            melhorGrafo=aux;
        }

        it++;
        cout<<"Iteracao do Randomizado: " << it << " de " << maxiter << endl;

        //desaloca memoria
        for(int i=0;i < tam_sol;i++){
            solucao[i] = NULL;
        }
        for(int i=0;i < tam_adj;i++){
            solucao_adj[i] = NULL;
        }
        delete steinerTree;
        delete[] solucao;
        delete[] solucao_adj;
        steinerTree = NULL;
        solucao = NULL;
        solucao_adj = NULL;
    }

    return melhorGrafo;
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
    int i, loc, j;
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

    //desaloca memória
    delete[] pesos;
    pesos = NULL;
}

void Steiner::atualizaLista(No** solucao, int tam_sol, No** solucao_adj, int *tam_adj)
{
    *tam_adj = 0;

    //Preeenchendo solucao_adj
    for (int i = 0; i < tam_sol; i++) {
        No* n = solucao[i];

        for (Aresta *a = n->getAresta(); a != nullptr; a = a->getProx()) {
            No* adj = g->getNo(a->getNoAdj());

            //checa se está na solucao
            bool estaNaSolucao=false;
            for(int j=0; j<tam_sol; j++){
                if(solucao[j]->getId() == adj->getId()){
                    estaNaSolucao=true;
                    break;
                }
            }

            //checa se está na solucao_adj
            bool estaNaSolucaoAdj=false;
            for(int j=0; j<(*tam_adj); j++){
                if(solucao_adj[j]->getId() == adj->getId()){
                    estaNaSolucaoAdj=true;
                    break;
                }
            }

            //adiciona na solucao_adj se não for um terminal
            if(adj != nullptr && adj->get_marcaTerminal()==false && estaNaSolucao == false && estaNaSolucaoAdj == false) { // Evita inserir nós repetidos
                solucao_adj[(*tam_adj)] = adj;
                (*tam_adj)++;
            }
        }

    }

}

//Poda da árvore
//retirar nós de grau 1 que não estejam no caminho entre os terminais
void Steiner::poda(Grafo* grafo_novo)
{
    //1º passo: fazer um vetor com os terminais
    //2º passo: procurar nó que tenha grau 1 com a função auxpoda, por meio de uma recursao

    No *terminal = grafo_novo->getNo(this->terminais[0]);
    No* noAdj = grafo_novo->getNo(terminal->getAresta()->getNoAdj());
    auxPoda(grafo_novo, noAdj, noAdj);
}
void Steiner::auxPoda(Grafo* grafo_novo, No *aux, No *ant)
{

    if(aux == nullptr){
        cout << "Steiner::AuxPoda() -> aux é nulo" << endl;
        return;
    }

    if(aux->getGrauEntrada()==1){//caso base: encontrar nó de grau 1

        if(aux->get_marcaTerminal() == false){// se nao for terminal remove
            grafo_novo->removeNo(aux->getId());
            aux = nullptr;
            return;
        }
    } else {
        //procura lista de adjacencia
        Aresta* adjacente=aux->getAresta();
        while(adjacente!=NULL){
            Aresta *proximo = adjacente->getProx();//salva o proximo caso o atual for deletado
            if(ant->getId() != adjacente->getNoAdj()){//se nao for o mesmo do anterior, ele encaminha para o proximo
                auxPoda(grafo_novo, grafo_novo->getNo(adjacente->getNoAdj()), aux);
            }
            adjacente = proximo;
        }

    }

    //se ele remover todos os adjacentes e ficar com grau 1, remove tambem
    if(aux->getGrauEntrada()==1){
        if(aux->get_marcaTerminal() ==false){
             grafo_novo->removeNo(aux->getId());
             aux = nullptr;
        }
    }

}



/*========================================================================*/
/*================= Algoritmo Guloso Randomizado Reativo =================*/
/*========================================================================*/



float Steiner::GulosoRandomizadoReativo(int maxiter, float *melhor_alfa)
{
    int B = 10;//bloco de iteracoes
    int max_alfas = 15;//quantidade de alfas
    float alfas[max_alfas];
    float S[max_alfas]; // armazena somatório de soluções do alfa
    int S_iter[max_alfas]; // numero de iterações de cada alfa
    float S_estrela = 0;
    float A_estrela = 0;
    float P[max_alfas];
    int indexAlfa=-1;
    int it = 0;
    float fator = 1.5;
    uint64_t ta, tb, tc, td;

    //inicia com solução gulosa
    S_estrela = solucaoGulosa;

    if(solucaoGulosa == -1){
        cout << "Obtem uma solução gulosa" << endl;
        S_estrela = this->GulosoConstrutivo();
    }

    cout << "Inicia o randomizado reativo com " << maxiter << " iteracoes" << endl;

    // inicializando vetores
    for (int i = 0; i < max_alfas; i++) {
        // inicializando soluções de alfa
        S[i] = 1.0;
        S_iter[i] = 0;

        // inicializando porcentagens
        P[i] = 1.0/max_alfas;

        // inicializando alfas
        alfas[i] = (float)1.0-i*(1.0/max_alfas);
    }



    while (it < maxiter) {
        float porcentagemAtual = P[0];
        indexAlfa = 0;
        ta = unix_timestamp();

        for (int i = 0; i < B; i++) {
            tc = unix_timestamp();
            if (porcentagemAtual <= (float)i/(float)B) {
                indexAlfa++;
                porcentagemAtual = porcentagemAtual + P[indexAlfa];
                i--;
                continue;
            } else {

                float solucaoAtual = this->GulosoRandomizado(alfas[indexAlfa], 1);

                //salva a melhor solucao
                if (S_estrela > solucaoAtual) {
                    S_estrela = solucaoAtual;
                    A_estrela = alfas[indexAlfa];
                }

                // Ao fim será responsável por retornar solução média de cada alfa
                S[indexAlfa] = S[indexAlfa] + solucaoAtual;
                S_iter[indexAlfa]++;

            }
            td = unix_timestamp();
            cout<<"Bloco: " << (i+1) << " de " << B << ", Com tempo de " << ((td-tc)/(float)1000) << endl;
        }

        // Recalculando probabilidades
        float recalculaP[max_alfas];
        float soma = 0;
        for (int k = 0; k < max_alfas; k++) {
            float aux = (float)S_estrela/((float)S[k]/(float)S_iter[k]);
            recalculaP[k] = pow(aux, fator);
            soma = soma + recalculaP[k];
        }
        for (int k = 0; k < max_alfas; k++) {
            P[k] = recalculaP[k]/soma;
        }
        it++;
        tb = unix_timestamp();
        cout<<"Iteracao do Reativo: " << it << " de " << maxiter << ", Com tempo de " << ((tb-ta)/(float)1000) << endl;
    }

    (*melhor_alfa) = A_estrela;
    return S_estrela;
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
            return 0;
        }

    }

    float custo = h->getCusto();

    //desaloca memória
    delete[] S;
    delete[] C;
    delete floyd;
    delete h;
    S = NULL;
    C = NULL;
    floyd = NULL;
    h = NULL;

    return custo;

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

