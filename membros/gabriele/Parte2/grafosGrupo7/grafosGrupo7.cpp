#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include "Log.h"
#include "Utils.h"
#include "Grafo.h"
#include"Steiner.h"

/*
Linha de comando pra rodar

*** não direcionado ***
MAC/LINUX:  clear && g++ -std=c++11 *.cpp -o grafosGrupo7 && ./grafosGrupo7 ../data/entrada2.txt ../data/saida.txt 0 0 1
WINDOWS:    cls & g++ -std=c++11 *.cpp -o grafosGrupo7 & grafosGrupo7.exe ../data/entrada2.txt ../data/saida.txt 0 0 1

*** direcionado ***
MAC/LINUX:  clear && g++ -std=c++11 *.cpp -o grafosGrupo7 && ./grafosGrupo7 ../data/entrada2.txt ../data/saida.txt 1 0 1
WINDOWS:    cls & g++ -std=c++11 *.cpp -o grafosGrupo7 & grafosGrupo7.exe ../data/entrada2.txt ../data/saida.txt 1 0 1

../instancias/pequenas/cc3-4p.stp ../saidas/cc3-4p.txt 0 0 1 2338
../instancias/grandes/cc7-3p.stp ../saidas/cc7-3p.txt 0 0 1 56779
../instancias/grandes/hc12p.stp ../saidas/hc12p.txt 0 0 1 236949
*/

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 7) {
        cout << "Argumentos passados invalidos";
        return 0;
    }

    Grafo *g;
    float solucao_best = 0;

    //verifica o formato do arquivo
    string arquivoEntrada = argv[1];
    std::size_t found = arquivoEntrada.find("stp");
    string formato = "txt";

    if(found != std::string::npos){
        formato = "stp";
    }


    // Verificando a quantidade de argumentos passados

    if (argc == 7) {
        solucao_best = stof(argv[6]);
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
    } else if (argc == 6) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
    } else if (argc == 5) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]), stoi(argv[4]));
    } else if (argc == 4) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]));
    } else {
        g = new Grafo(formato, argv[1], argv[2]);
    }


    Utils u;
    u.imprime(g);
    u.gerarArquivoGraphViz(g, "C:/Users/gabic/Desktop/grafos2019_1/membros/gabriele/Parte2/saidas/grafoAntes.gv");
//    Steiner* stenio=new Steiner(g->getTerminais(),g->getNumTerminais());
//    stenio->poda(g);
    g->removeNo(1);
    u.gerarArquivoGraphViz(g, "C:/Users/gabic/Desktop/grafos2019_1/membros/gabriele/Parte2/saidas/grafoDepois.gv");


    //menu da aplicação
    //inicializa log
    string arquivoSaida = argv[2];

    Log::getInstance().iniciaArquivoSaida(arquivoSaida);

    Log::getInstance().line("**** Trabalho Grafos 2019.1 - Grupo 7 ****");

    Log::getInstance().line("\n## Membros ##");
    Log::getInstance().line("Laura Polverari");
    Log::getInstance().line("Gabriele Cesar");
    Log::getInstance().line("Thiago Almeida");
    Log::getInstance().line("Victor Aquiles\n");

    Log::getInstance().line("## Parametros recebidos ##");
    Log::getInstance().line("arquivoEntrada: " + arquivoEntrada);
    Log::getInstance().line("arquivoSaida: " + arquivoSaida);

    if(formato == "stp"){
        Log::getInstance().line("best: " + to_string(solucao_best));
    }
    if(stoi(argv[3])){
        Log::getInstance().line("isDirecionado: Sim");
    } else {
        Log::getInstance().line("isDirecionado: Não");
    }

    if(stoi(argv[5])){
        Log::getInstance().line("isPonderadoVertice: Sim");
    } else {
        Log::getInstance().line("isPonderadoVertice: Não");
    }

    if(stoi(argv[4])){
        Log::getInstance().line("isPonderadoAresta: Sim");
    } else {
        Log::getInstance().line("isPonderadoAresta: Não");
    }

    Log::getInstance().line("\n");



    string cmd;
    int int_cmd1, int_cmd2;
    bool todos = false;
    Aresta *caminho;

    while(cmd != "0"){
        cmd = "";
        todos = false;

        Log::getInstance().line("## MENU ##\n");

        Log::getInstance().line("Digite o número correspondente a opção desejada");
        Log::getInstance().line("0: Sair do programa");
        Log::getInstance().line("1: Caminhamento em Largura");
        Log::getInstance().line("2: Caminhamento em Profundidade");
        Log::getInstance().line("3: Componentes Fortemente Conexas (para grafo orientado)");
        Log::getInstance().line("4: Ordenação Topológica (para grafo orientado)");
        Log::getInstance().line("5: Dijkstra: Caminho Mínimo (para grafos ou digrafos ponderados ou não)");
        Log::getInstance().line("6: Floyd: Caminho Mínimo (para grafos ou digrafos ponderados ou não)");
        Log::getInstance().line("7: Prim: Árvore Geradora Mínima (para grafos não orientados ponderados ou não)");
        Log::getInstance().line("8: Kruskal: Árvore Geradora Mínima (para grafos não orientados ponderados ou não)");
        Log::getInstance().line("9: Todos os testes da primeira etapa");
        Log::getInstance().line("10: Algoritmo guloso para Arvore de Steiner");
        Log::getInstance().line("11: Algoritmo guloso randomizado para Arvore de Steiner");
        Log::getInstance().line("12: Algoritmo guloso randomizado reativo para Arvore de Steiner");
        Log::getInstance().line("13: Algoritmo extra para Arvore de Steiner");

        cin >> cmd;
        Log::getInstance().lineArquivo(cmd);

        if(cmd == "9"){
            Log::getInstance().line("\n## Executar todos os teste ##\n");
            Log::getInstance().line("Digite o id do vértice de origem e destino separados por um espaço");
            cin >> int_cmd1 >> int_cmd2;
            Log::getInstance().lineArquivo(to_string(int_cmd1) + " " + to_string(int_cmd2));
            todos = true;
        }
        if(cmd == "1" || todos == true){
            Log::getInstance().line("\n## Caminhamento em Largura ##\n");

            if(todos == false){
                Log::getInstance().line("Digite o id do vértice de destino");
                cin >> int_cmd2;
                Log::getInstance().lineArquivo(to_string(int_cmd1));
            } else {
                Log::getInstance().line("Usando o vertice de destino: " + to_string(int_cmd2));
            }

            caminho = g->caminho_largura(int_cmd2);
            Log::getInstance().line("Procura caminho até "+to_string(int_cmd2)+".");
            if(caminho != NULL){
                Log::getInstance().line("Encontrado.");
                Aresta *aux = caminho;
                while(aux != NULL){
                    Log::getInstance().line("Aresta: (" + to_string(aux->getOrigem()) + ", " + to_string(aux->getNoAdj()) + ") peso: " + to_string(aux->getPeso())+")");
                    aux = aux->getProx();
                }
                Log::getInstance().line("\n");
            } else {
                Log::getInstance().line("Não foi encontrado.");
            }
        }

        if(cmd == "2" || todos == true){
            Log::getInstance().line("\n## Caminhamento em Profundidade ##\n");

            if(todos == false){
                Log::getInstance().line("Digite o id do vértice de origem e destino separados por um espaço");
                cin >> int_cmd1 >> int_cmd2;
                Log::getInstance().lineArquivo(to_string(int_cmd1) + " " + to_string(int_cmd2));
            } else {
                Log::getInstance().line("Usando o vertice de origem: " + to_string(int_cmd1) + " e destino: " + to_string(int_cmd2));
            }

            caminho = g->buscaEmProfundidade(int_cmd1, int_cmd2);
            Log::getInstance().line("Procura caminho entre "+to_string(int_cmd1)+"-"+to_string(int_cmd2)+".");
            if(caminho != NULL){
                Log::getInstance().line("Encontrado.");
                Aresta *aux = caminho;
                while(aux != NULL){
                    Log::getInstance().line("Aresta: (" + to_string(aux->getOrigem()) + ", " + to_string(aux->getNoAdj()) + ") peso: " + to_string(aux->getPeso())+")");
                    aux = aux->getProx();
                }
                Log::getInstance().line("\n");
            } else {
                Log::getInstance().line("Não foi encontrado.");
            }
        }

        if(cmd == "3" || todos == true){
            if(g->isDirecionado()){
                Log::getInstance().line("\n## Componentes Fortemente Conexas (para grafo orientado) ##\n");
            } else {
                Log::getInstance().line("\n%%% Atenção: O grafo precisa ser orientado para calcular as componentes fortemente conexas! %%%\n");
            }
        }

        if(cmd == "4" || todos == true){
            if(g->isDirecionado()){
                Log::getInstance().line("\n## Ordenação Topológica (para grafo orientado) ##\n");

                int *ordenado = g->ordenacaoTopologica();
                Log::getInstance().line("Ids em ordem");

                for(int i=0; i<g->getOrdem(); i++){
                    if(i!=0){
                        Log::getInstance().semEndl(", ");
                    }
                    Log::getInstance().semEndl(to_string(ordenado[i]));
                }
                Log::getInstance().line("\n");//vai ter duas quebras de linha
            } else {
                Log::getInstance().line("\n%%% Atenção: O grafo precisa ser orientado para calcular a ordenação topológica! %%%n");
            }
        }

        if(cmd == "5" || todos == true){
            Log::getInstance().line("\n## Dijkstra: Caminho Mínimo (para grafos ou digrafos ponderados ou não) ##\n");

            if(todos == false){
                Log::getInstance().line("Digite o id do vértice de origem e destino separados por um espaço");
                cin >> int_cmd1 >> int_cmd2;
                Log::getInstance().lineArquivo(to_string(int_cmd1) + " " + to_string(int_cmd2));
            } else {
                Log::getInstance().line("Usando o vertice de origem: " + to_string(int_cmd1) + " e destino: " + to_string(int_cmd2));
            }

            caminho = g->getCaminhoDijkstra(int_cmd1, int_cmd2);
            Log::getInstance().line("Procura caminho entre "+to_string(int_cmd1)+"-"+to_string(int_cmd2)+".");
            float custo = 0;
            if(caminho != NULL){
                Log::getInstance().line("Encontrado.");
                Aresta *aux = caminho;
                while(aux != NULL){
                    Log::getInstance().line("Aresta: (" + to_string(aux->getOrigem()) + ", " + to_string(aux->getNoAdj()) + ") peso: " + to_string(aux->getPeso())+")");
                    custo += aux->getPeso();
                    aux = aux->getProx();
                }
                Log::getInstance().line("\n");
                Log::getInstance().line("Custo: " + to_string(custo));
            } else {
                Log::getInstance().line("Não foi encontrado.");
            }
        }

        if(cmd == "6" || todos == true){
            Log::getInstance().line("\n## Floyd: Caminho Mínimo (para grafos ou digrafos ponderados ou não) ##\n");


            if(todos == false){
                Log::getInstance().line("Digite o id do vértice de origem e destino separados por um espaço");
                cin >> int_cmd1 >> int_cmd2;
                Log::getInstance().lineArquivo(to_string(int_cmd1) + " " + to_string(int_cmd2));
            } else {
                Log::getInstance().line("Usando o vertice de origem: " + to_string(int_cmd1) + " e destino: " + to_string(int_cmd2));
            }

            caminho = g->getCaminhoFloyd(int_cmd1, int_cmd2);
            if(caminho != NULL){
                Log::getInstance().line("Encontrado.");

                Aresta *aux = caminho;
                while(aux != NULL){
                    Log::getInstance().line("Aresta: (" + to_string(aux->getOrigem()) + ", " + to_string(aux->getNoAdj()) + ") peso: " + to_string(aux->getPeso())+")");
                    aux = aux->getProx();
                }
                Log::getInstance().line("\n");
                Log::getInstance().line("Custo: " + to_string(g->getDistanciaFloyd(int_cmd1, int_cmd2)));
            } else {
                Log::getInstance().line("Não foi encontrado.");
            }
        }

        if(cmd == "7" || todos == true){
            Log::getInstance().line("\n## Prim: Árvore Geradora Mínima (para grafos não orientados ponderados ou não) ##\n");
            if(g->isDirecionado()){
                Log::getInstance().line("\n%%% Atenção: O grafo não pode ser orientado para calcular a arvore geradora mínima por Prim! %%%\n");
            } else {
                float pesoTotal;
                Grafo *arvoreAGM = g->PrimAGM(&pesoTotal);
                Utils u;

                Log::getInstance().line("Arvore geradora minima: ");
                Log::getInstance().line("\n");
                u.imprimeNoLog(arvoreAGM);
                u.gerarArquivoGraphViz(arvoreAGM, "../saidas/prim.gv");
                Log::getInstance().line("\n");
                Log::getInstance().line("Soma dos pesos das arestas da arvore geradora minima: " + to_string(pesoTotal) + "\n");
            }
        }

        if(cmd == "8" || todos == true){
            Log::getInstance().line("\n## Kruskal: Árvore Geradora Mínima (para grafos não orientados ponderados ou não) ##\n");

            if(g->isDirecionado()){
                Log::getInstance().line("\n%%% Atenção: O grafo não pode ser orientado para calcular a arvore geradora mínima por Kruskal! %%%\n");
            } else {
                Aresta arestasAGM[g->getOrdem() - 1];
                int indComp[g->getOrdem()];
                int idNos[g->getOrdem()];

                if(g->componenteConexa(indComp, idNos) == 1) {
                    float pesoTotal;
                    Grafo *arvoreAGM = g->KruskalAGM(&pesoTotal);
                    Utils u;

                    Log::getInstance().line("Arvore geradora minima: ");
                    Log::getInstance().line("\n");
                    u.imprimeNoLog(arvoreAGM);
                    u.gerarArquivoGraphViz(arvoreAGM, "../saidas/kruskal.gv");
                    Log::getInstance().line("\n");
                    Log::getInstance().line("Soma dos pesos das arestas da arvore geradora minima: " + to_string(pesoTotal) + "\n");
                }
            }
        }

        if(cmd == "10"){
            Log::getInstance().line("\n## Algoritmo guloso para Arvore de Steiner ##\n");

            ResultadoGuloso resultado = g->guloso();
            float erro = 0;

            if(solucao_best != 0){
                //calcula o erro
                erro = fabs((resultado.custo - solucao_best) / solucao_best);
            }

            Log::getInstance().line("[media tempo], [media custo], [best], [erro]");
            Log::getInstance().line(to_string(resultado.tempo) + ", " + to_string(resultado.custo) + ", " + to_string(solucao_best) + ", " + to_string(erro));
            Log::getInstance().breakLine();
        }

        if(cmd == "11"){
            Log::getInstance().line("\n## Algoritmo guloso randomizado para Arvore de Steiner ##\n");
            float alfas[3];
            int N = 30;
            int numIteracoes = 1000;

            Log::getInstance().line("Digite os 3 valores de alfa");
            cin >> alfas[0] >> alfas[1] >> alfas[2];
            Log::getInstance().lineArquivo(to_string(alfas[0]) + " " + to_string(alfas[1]) + " " + to_string(alfas[2]));

            for(int i=0; i<3; i++){

                float m_custo=0;
                float *vet_custo = new float[N];
                float m_tempo=0;
                float desvio_padrao=0;
                float erro = 0;

                Log::getInstance().line("\n---------------------------------\n");
                Log::getInstance().line("Executando para o alfa["+to_string(i)+"] = " + to_string(alfas[i]));
                Log::getInstance().line("\n[execucao], [tempo], [custo]");

                for(int j=0; j<N; j++){
                    ResultadoGuloso resultado = g->gulosoRandomizado(alfas[i], numIteracoes);
                    vet_custo[j] = resultado.custo;
                    m_custo += resultado.custo;
                    m_tempo += resultado.tempo;
                    Log::getInstance().line(to_string(j) + ", " + to_string(resultado.tempo) + ", " + to_string(resultado.custo));
                }

                m_custo = m_custo / N;
                m_tempo = m_tempo / N;

                //calcula desvio padrão
                float soma=0;
                for(int k=0; k<N; k++){
                    soma += pow(vet_custo[k] - m_custo, 2.0);
                }
                desvio_padrao = sqrt(soma / N);

                if(solucao_best != 0){
                    //calcula o erro
                    erro = fabs((m_custo - solucao_best) / solucao_best);
                }

                Log::getInstance().line("\nTotal");
                Log::getInstance().line("[media tempo], [media custo], [best], [erro], [desvio padrao]");
                Log::getInstance().line(to_string(m_tempo) + ", " + to_string(m_custo) + ", " + to_string(solucao_best) + ", " + to_string(erro) + ", " + to_string(desvio_padrao));
                Log::getInstance().breakLine();
            }
        }

        if(cmd == "12"){
            Log::getInstance().line("\n## Algoritmo guloso randomizado reativo para Arvore de Steiner ##\n");
            int N = 30;
            int numIteracoes = 1000;

            float m_custo=0;
            float *vet_custo = new float[N];
            float m_tempo=0;
            float desvio_padrao=0;
            float erro = 0;

            Log::getInstance().line("\n[execucao], [tempo], [custo]");

            for(int j=0; j<N; j++){
                ResultadoGuloso resultado = g->gulosoRandomizadoReativo(numIteracoes);
                vet_custo[j] = resultado.custo;
                m_custo += resultado.custo;
                m_tempo += resultado.tempo;
                Log::getInstance().line(to_string(j) + ", " + to_string(resultado.tempo) + ", " + to_string(resultado.custo));
            }

            m_custo = m_custo / N;
            m_tempo = m_tempo / N;

            //calcula desvio padrão
            float soma=0;
            for(int k=0; k<N; k++){
                soma += pow(vet_custo[k] - m_custo, 2.0);
            }
            desvio_padrao = sqrt(soma / N);

            if(solucao_best != 0){
                //calcula o erro
                erro = fabs((m_custo - solucao_best) / solucao_best);
            }

            Log::getInstance().line("\nTotal");
            Log::getInstance().line("[media tempo], [media custo], [best], [erro], [desvio padrao]");
            Log::getInstance().line(to_string(m_tempo) + ", " + to_string(m_custo) + ", " + to_string(solucao_best) + ", " + to_string(erro) + ", " + to_string(desvio_padrao));
            Log::getInstance().breakLine();
        }

        if(cmd == "13"){
            Log::getInstance().line("\n## Algoritmo extra para Arvore de Steiner ##\n");

            ResultadoGuloso resultado = g->gulosoExtra();
            float erro = 0;

            if(solucao_best != 0){
                //calcula o erro
                erro = fabs((resultado.custo - solucao_best) / solucao_best);
            }

            Log::getInstance().line("[media tempo], [media custo], [best], [erro]");
            Log::getInstance().line(to_string(resultado.tempo) + ", " + to_string(resultado.custo) + ", " + to_string(solucao_best) + ", " + to_string(erro));
            Log::getInstance().breakLine();
        }
    }

    return 0;
}
