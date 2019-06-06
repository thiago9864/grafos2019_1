/**
    Universidade Federal de Juiz de Fora
    Steiner.cpp
    Propósito: Resolve o problema de Steiner.

    @author Thiago Almeida
    @version 1.0 09/05/19
*/

#include "Steiner.h"

Steiner::Steiner(Grafo *grafo){
    this->grafo = grafo;
    this->caminhoMinimo = new CaminhoMinimoDijkstra(grafo);
};
Steiner::~Steiner(){
    //destrutor
};

float Steiner::obtemMenorDistancia(int origem, int destino)
{
    caminhoMinimo->calcular(origem, destino);
    return caminhoMinimo->getDistanciaMinima();
}

float Steiner::calcular()
{
    int num_terminais = grafo->getNumTerminais();
    int *terminais = grafo->getTerminais();
    int *arvore = new int[grafo->getOrdem()]; 
    int tam_arvore = 0;
    int tam_candidatos = 0;
    float distancia_calculada = 0;

    cout << "num_terminais: " << num_terminais << endl;
    time_t t_inicio = std::time(0);

    int terminal_atual = terminais[0];
    
    //inicia a subarvore
    arvore[tam_arvore] = terminal_atual;
    tam_arvore++;

    while(tam_arvore < num_terminais){

        tam_candidatos=0;
        int mais_proximo_arvore = -1;
        int mais_proximo_na_arvore = -1;
        float dist_mais_proximo_arvore = maxFloat;
        float prc = ((float)tam_arvore / (float)num_terminais) * 100;
        cout << "--------------------" << endl;
        cout << "prc concluida: " << prc << "%" << endl;
        /*cout << "Arvore: ";
        for(int j=0; j < tam_arvore; j++)
        {
            if(j>0){
                cout << ", ";
            }
            cout << arvore[j];
        }
        cout << endl;
        */

        //seleciona o terminal mais proximo de algum terminal
        //que já está na lista
        for(int i=0; i < tam_arvore; i++)
        {
            int terminal_arvore = arvore[i];
            float dist_minima = maxFloat;
            float dist = 0;
            int term_mais_prox = -1;

            //cout << "tam_arvore: " << tam_arvore << endl;

            for(int j=0; j < num_terminais; j++)
            {
                bool estaNaArvore = false;
                int terminal_fora = terminais[j];

                //cout << "verificando se o terminal " << terminal_fora << " está na arvore" << endl;

                for(int t=0; t < tam_arvore; t++)
                {
                    if(arvore[t] == terminal_fora)
                    {
                        estaNaArvore = true;
                        break;
                    }
                }

                //cout << "estaNaArvore: " << estaNaArvore << endl;

                if(!estaNaArvore)
                {
                    //cout << "o terminal " << terminal_fora << " não está na arvore" << endl;

                    caminhoMinimo->calcular(terminal_arvore, terminal_fora);
                    dist = caminhoMinimo->getDistanciaMinima();

                    //cout << "testando o terminal " << terminal_arvore << " com o terminal " << terminal_fora  << endl;

                    if(terminal_arvore == terminal_fora) {
                        cout << "testando o terminal com ele mesmo sempre dará zero" << endl;
                        exit(1);
                    }

                    if(dist < dist_minima)
                    {
                        dist_minima = dist;
                        term_mais_prox = terminal_fora;
                        //cout << "o terminal " << term_mais_prox << " esta mais proximo do " << terminal_arvore << endl;
                    }
                }
            }

            //cout << "o terminal " << term_mais_prox << " esta mais proximo do " << terminal_arvore;
            //cout << " com distancia de: " << dist_minima << endl;

            //coloca o terminal mais proximo
            if(term_mais_prox != -1 && dist_minima < dist_mais_proximo_arvore){
                mais_proximo_arvore = term_mais_prox;
                mais_proximo_na_arvore = terminal_arvore;
                dist_mais_proximo_arvore = dist_minima;
            }
            
        }

        cout << "o terminal " << mais_proximo_arvore << " e o mais proximo do " << mais_proximo_na_arvore << " da arvore" << endl;

        if(mais_proximo_arvore == -1){
            cout << "Não foi encontrado o terminal mais próximo" << endl;
            exit(1);
        }

        arvore[tam_arvore] = mais_proximo_arvore;
        tam_arvore++;
        distancia_calculada += dist_mais_proximo_arvore;
    }
    
    cout << "prc concluida: 100%" << endl;
    cout << "arvore obtida com o custo minimo de: " << distancia_calculada << endl;

    time_t t_fim = std::time(0);
    time_t t_dif = t_fim - t_inicio;
    cout << "Tempo gasto: " << t_dif << " segundos" <<  endl;

    return distancia_calculada;
}

/*
Teste com o cc3-4p_R2338.stp
Custo Minimo: 2942
Custo Esperado: 2338
Tempo gasto: menos de 1 segundo (com busca binaria na matriz de pesos)
Erro: 26 %
*/

/*
Teste com o bipe2p_R5616.stp
Custo Minimo: 9898
Custo Esperado: 5616
Tempo gasto: 907 segundos (sem busca binaria na matriz de pesos)
Tempo gasto: 476 segundos (com busca binaria na matriz de pesos)
Erro: 76 %
*/

/*
Teste com o cc6-3p_R20720.stp
Custo Minimo: 27551
Custo Esperado: 20720
Tempo gasto: 2645 segundos (com busca binaria na matriz de pesos)
Erro: 32 %
*/