/**
    Universidade Federal de Juiz de Fora
    main.cpp
    Propósito: Arquivo principal do trabalho.

    @author Thiago Almeida
    @version 1.0 30/03/19
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cmath>
#include <chrono>
#include "Grafo.h"
#include "Log.h"
#include "Utils.h"
#include "Steiner.h"

using namespace std;

/**

######### Lista de comandos pra rodar pelo terminal ##########

*** teste ***
MAC/LINUX:  clear && g++ -std=c++11 *.cpp -o GrafosGrupo7 && ./GrafosGrupo7 ../instancias/teste/cc3-4p.stp ../saidas/cc3-4p.txt 0 0 1 2338
WINDOWS:    cls & g++ -std=c++11 *.cpp -o GrafosGrupo7 & GrafosGrupo7.exe ../instancias/teste/cc3-4p.stp ../saidas/cc3-4p.txt 0 0 1 2338

*** não direcionado ***
MAC/LINUX:  clear && g++ -std=c++11 *.cpp -o GrafosGrupo7 && ./GrafosGrupo7 ../instancias/grandes/I053.stp ../saidas/I053.txt 0 0 1 59797
WINDOWS:    cls & g++ -std=c++11 *.cpp -o GrafosGrupo7 & GrafosGrupo7.exe ../instancias/grandes/I053.stp ../saidas/I053.txt 0 0 1 30854904

*** direcionado ***
MAC/LINUX:  clear && g++ -std=c++11 *.cpp -o GrafosGrupo7 && ./GrafosGrupo7 ../instancias/entrada2.txt ../saidas/entrada2.txt 1 0 1
WINDOWS:    cls & g++ -std=c++11 *.cpp -o GrafosGrupo7 & GrafosGrupo7.exe ../instancias/entrada2.txt ../saidas/entrada2.txt 1 0 1

LISTA DE EXERCICIOS 3:
clear && g++ -std=c++11 *.cpp -o main && ./main ../data/lista3.txt ../data/saida.txt 0 0 1
cls & g++ -std=c++11 *.cpp -o main & main.exe ../data/lista3.txt ../data/saida.txt 0 0 1


######### Descricao dos atributos passados ao programa ##########


Como executar o programa
./GrafosGrupo7 <arq entrada> <arq saida> <direcionado> <ponderadoVertice> <ponderadoAresta> <solucaoBest> <comando> <maxitera> <alfa>

Parametros
<arq entrada>       = Caminho do arquivo contendo a instancia
<arq saida>         = Caminho do arquivo com os logs de saída
<direcionado>       = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoVertice>  = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoAresta>   = 1: Sim, 0: Não (opcional, Sim por padrão)
<solucaoBest>       = valor float que representa a melhor solução pra instancia de Steiner fornecida (opcional, Não por padrão)
<comando>           = comando pro menu (opcional)
<maxitera>          = max iteracoes (opcional)
<alfa>              = alfa do randomizado (opcional)


######### Lista de argumentos pra cada instancia do experimento ##########

Argumentos das instancias
../instancias/pequenas/hc7p.stp ../saidas/hc7p.txt 0 0 1 7905
../instancias/pequenas/cc3-5p.stp ../saidas/cc3-5p.txt 0 0 1 3661
../instancias/pequenas/bipe2p.stp ../saidas/bipe2p.txt 0 0 1 5616

../instancias/medias/hc10p.stp ../saidas/hc10p.txt 0 0 1 59797
../instancias/medias/cc10-2p.stp ../saidas/cc10-2p.txt 0 0 1 35297
../instancias/medias/bip42p.stp ../saidas/bip42p.txt 0 0 1 24657
../instancias/medias/cc6-3p.stp ../saidas/cc6-3p.txt 0 0 1 20270

../instancias/grandes/I056.stp ../saidas/I056.txt 0 0 1 14171206
../instancias/grandes/cc7-3p.stp ../saidas/cc7-3p.txt 0 0 1 56799
../instancias/grandes/I052.stp ../saidas/I052.txt 0 0 1 13309487



######### Argumentos de algumas instancias usadas como teste ##########

../instancias/teste/cc3-4p.stp ../saidas/cc3-4p.txt 0 0 1 2338
../instancias/entrada_conexas.txt ../saidas/entrada_conexas.txt 0 0 1 0 8


**/



uint64_t unix_timestamp()
{
    uint64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return now;
}


int main(int argc, char *argv[])
{
    //variaveis
    string arquivoEntrada, arquivoSaida;
    bool isDirecionado = false;
    bool isPonderadoNo = false;
    bool isPonderadoAresta = false;
    float solucao_best = 0;
    int comando=-1;
    int max_iteracoes=1;
    float alfa_recebido=0;

    //verifica a quantidade de parametros recebidos
    if(argc < 3)
    {
        cout << "Número de parametros insuficiente. use: main <arq entrada> <arq saida> no mínimo." << endl;
        cout << "Ou use parametros opcionais nessa ordem após os obrigatórios: <direcionado> <ponderadoVertice> <ponderadoAresta>" << endl;
        return 0;
    }

    //obtem parametros obrigatórios
    arquivoEntrada = argv[1];
    arquivoSaida = argv[2];

    //obtem parametros opcionais, se fornecidos
    if(argc >= 4)
    {
        if(stoi(argv[3]) == 1)
        {
            isDirecionado = true;
        }
    }
    if(argc >= 5)
    {

        if(stoi(argv[4]) == 1)
        {
            isPonderadoNo = true;
        }
    }
    if(argc >= 6)
    {

        if(stoi(argv[5]) == 1)
        {
            isPonderadoAresta = true;
        }
    }
    if(argc >= 7)
    {
        solucao_best = stof(argv[6]);
    }
    if(argc >= 8)
    {
        comando = stoi(argv[7]);
    }
    if(argc >= 9)
    {
        max_iteracoes = stoi(argv[8]);
    }
    if(argc >= 10)
    {
        alfa_recebido = stof(argv[9]);
    }

    //verifica o formato do arquivo
    std::size_t found_ext = arquivoEntrada.find("stp");
    std::size_t found_lastBar = arquivoEntrada.rfind("/");

    string formato = "txt";
    string nomeArquivoSemExtensao = "";

    if(found_ext != std::string::npos){
        formato = "stp";
        for(int i=found_lastBar+1; i<found_ext-1; i++){
            nomeArquivoSemExtensao += arquivoEntrada[i];
        }
    } else {
        nomeArquivoSemExtensao = arquivoEntrada;
    }


    // Inicia o grafo
    Grafo *g = new Grafo(formato, arquivoEntrada, arquivoSaida, isDirecionado, isPonderadoNo, isPonderadoAresta);

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

    if(isDirecionado){
        Log::getInstance().line("isDirecionado: Sim");
    } else {
        Log::getInstance().line("isDirecionado: Não");
    }

    if(isPonderadoNo){
        Log::getInstance().line("isPonderadoVertice: Sim");
    } else {
        Log::getInstance().line("isPonderadoVertice: Não");
    }

    if(isPonderadoAresta){
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
        Log::getInstance().line("13: Algoritmo construtivo caminho minimo Arvore de Steiner");

        if(comando == -1){
            cin >> cmd;
        } else {
            cmd = to_string(comando);
        }

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

            caminho = g->caminhamentoEmLargura(int_cmd2);
            Log::getInstance().line("Procura caminho até "+to_string(int_cmd2)+".");
            if(caminho != NULL){
                Log::getInstance().line("Encontrado.");
                Aresta *aux = caminho;
                while(aux != NULL){
                    Log::getInstance().line(aux->toString());
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

            caminho = g->caminhamentoEmProfundidade(int_cmd1, int_cmd2);
            Log::getInstance().line("Procura caminho entre "+to_string(int_cmd1)+"-"+to_string(int_cmd2)+".");
            if(caminho != NULL){
                Log::getInstance().line("Encontrado.");
                Aresta *aux = caminho;
                while(aux != NULL){
                    Log::getInstance().line(aux->toString());
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

            caminho = g->caminhoMinimoDijkstra(int_cmd1, int_cmd2);
            Log::getInstance().line("Procura caminho entre "+to_string(int_cmd1)+"-"+to_string(int_cmd2)+".");
            float custo = 0;
            if(caminho != NULL){
                Log::getInstance().line("Encontrado.");
                Aresta *aux = caminho;
                while(aux != NULL){
                    Log::getInstance().line(aux->toString());
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

            caminho = g->getCaminhoMinimoFloyd(int_cmd1, int_cmd2);
            if(caminho != NULL){
                Log::getInstance().line("Encontrado.");

                Aresta *aux = caminho;
                while(aux != NULL){
                    Log::getInstance().line(aux->toString());
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
                //u.imprimeNoLog(arvoreAGM);
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

                if(g->listarComponentesConexas(indComp, idNos) == 1) {
                    float pesoTotal;
                    Grafo *arvoreAGM = g->KruskalAGM(&pesoTotal);
                    Utils u;

                    Log::getInstance().line("Arvore geradora minima: ");
                    Log::getInstance().line("\n");
                    //u.imprimeNoLog(arvoreAGM);
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

            Log::getInstance().line("[tempo], [custo], [best], [erro]");
            string linhaRes = to_string(resultado.tempo) + "," + to_string(resultado.custo) + "," + to_string(solucao_best) + "," + to_string(erro);
            Log::getInstance().line(linhaRes);
            Log::getInstance().breakLine();

            //grava no arquivo
            Log::getInstance().salvaLinhaNoArquivo(linhaRes, "../saidas/G_" + nomeArquivoSemExtensao + ".csv");
        }

        if(cmd == "11" || comando==11){
            Log::getInstance().line("\n## Algoritmo guloso randomizado para Arvore de Steiner ##\n");
            float alfa = 0;
            int numIteracoes = 1000;
            float erro = 0;

            if(comando==11){
                alfa = alfa_recebido;
                numIteracoes = max_iteracoes;
            } else {
                Log::getInstance().line("Digite o valor de alfa e o numero de iteracoes");
                cin >> alfa >> numIteracoes;
            }
            Log::getInstance().lineArquivo(to_string(alfa) + " " + to_string(numIteracoes));

            ResultadoGuloso resultado = g->gulosoRandomizado(alfa, numIteracoes);

            if(solucao_best != 0){
                //calcula o erro
                erro = fabs((resultado.custo - solucao_best) / solucao_best);
            }

            Log::getInstance().line("[alfa], [tempo], [custo], [best], [erro], [semente]");
            string linhaRes = to_string(alfa) + "," + to_string(resultado.tempo) + "," + to_string(resultado.custo) + "," + to_string(solucao_best) + "," + to_string(erro) + "," + to_string(resultado.semente);
            Log::getInstance().line(linhaRes);
            Log::getInstance().breakLine();

            //grava no arquivo
            Log::getInstance().salvaLinhaNoArquivo(linhaRes, "../saidas/GR_" + to_string(alfa) + "_" + nomeArquivoSemExtensao + ".csv");
        }

        if(cmd == "12" || comando==12){
            Log::getInstance().line("\n## Algoritmo guloso randomizado reativo para Arvore de Steiner ##\n");
            int numIteracoes = 1000;
            float erro = 0;

            if(comando==12){
                numIteracoes = max_iteracoes;
            } else {
                Log::getInstance().line("Digite o numero de iteracoes");
                cin >> numIteracoes;
            }

            Log::getInstance().line(to_string(numIteracoes));

            ResultadoGuloso resultado = g->gulosoRandomizadoReativo(numIteracoes);

            if(solucao_best != 0){
                //calcula o erro
                erro = fabs((resultado.custo - solucao_best) / solucao_best);
            }

            //grava no log
            Log::getInstance().line("[alfa], [tempo], [custo], [best], [erro], [semente]");
            string linhaRes = to_string(resultado.alfa_reativo) + "," + to_string(resultado.tempo) + "," + to_string(resultado.custo) + "," + to_string(solucao_best) + "," + to_string(erro) + "," + to_string(resultado.semente);
            Log::getInstance().line(linhaRes);
            Log::getInstance().breakLine();

            //grava no arquivo
            Log::getInstance().salvaLinhaNoArquivo(linhaRes, "../saidas/GRR_" + nomeArquivoSemExtensao + ".csv");
        }

        if(cmd == "13" || comando==13){
            Log::getInstance().line("\n## Algoritmo Construtivo Caminho Minimo Arvore de Steiner ##\n");

            ResultadoGuloso resultado = g->construtivoCaminhoMinimo();
            float erro = 0;

            if(solucao_best != 0){
                //calcula o erro
                erro = fabs((resultado.custo - solucao_best) / solucao_best);
            }

            //grava no log
            Log::getInstance().line("[tempo], [custo], [best], [erro]");
            string linhaRes = to_string(resultado.tempo) + "," + to_string(resultado.custo) + "," + to_string(solucao_best) + "," + to_string(erro);
            Log::getInstance().line(linhaRes);
            Log::getInstance().breakLine();

            //grava no arquivo
            Log::getInstance().salvaLinhaNoArquivo(linhaRes, "../saidas/CCM_" + nomeArquivoSemExtensao + ".csv");
        }
        if(comando != -1){
            cmd = "0";
        }
    }

    return 0;
}
