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
#include "Grafo.h"
#include "Log.h"
#include "Utils.h"
#include"Steiner.h"

using namespace std;

/**
Prototipo de codigo pra avaliacao

pra chegar nas pastas
cd \membros\thiago\Trabalho\Lista

*** não direcionado ***
MAC/LINUX:  clear && g++ -std=c++11 *.cpp -o GrafosGrupo7 && ./GrafosGrupo7 ../instancias/entrada2.txt ../saidas/entrada2.txt 0 0 1
WINDOWS:    cls & g++ -std=c++11 *.cpp -o GrafosGrupo7 & GrafosGrupo7.exe ../instancias/entrada2.txt ../saidas/entrada2.txt 0 0 1

*** direcionado ***
MAC/LINUX:  clear && g++ -std=c++11 *.cpp -o GrafosGrupo7 && ./GrafosGrupo7 ../instancias/entrada2.txt ../saidas/entrada2.txt 1 0 1
WINDOWS:    cls & g++ -std=c++11 *.cpp -o GrafosGrupo7 & GrafosGrupo7.exe ../instancias/entrada2.txt ../saidas/entrada2.txt 1 0 1

../instancias/pequenas/cc3-4p.stp ../saidas/cc3-4p.txt 0 0 1 2338
../instancias/grandes/cc7-3p.stp ../saidas/cc7-3p.txt 0 0 1 56779
../instancias/grandes/hc12p.stp ../saidas/hc12p.txt 0 0 1 236949

LISTA DE EXERCICIOS 3:
clear && g++ -std=c++11 *.cpp -o main && ./main ../data/lista3.txt ../data/saida.txt 0 0 1
cls & g++ -std=c++11 *.cpp -o main & main.exe ../data/lista3.txt ../data/saida.txt 0 0 1


Comando descrito para o professor
./main <arq entrada> <arq saida> <direcionado> <ponderadoVertice> <ponderadoAresta> <solucaoBest>

Parametros
<arq entrada>       = Caminho do arquivo contendo a instancia
<arq saida>         = Caminho do arquivo com os logs de saída
<direcionado>       = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoVertice>  = 1: Sim, 0: Não (opcional, Não por padrão)
<ponderadoAresta>   = 1: Sim, 0: Não (opcional, Sim por padrão)
<solucaoBest>       = valor float que representa a melhor solução pra instancia de Steiner fornecida
**/
long int unix_timestamp()
{
    time_t t = std::time(0);
    long int now = static_cast<long int> (t);
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

    //time_t t_inicio = std::time(0);
    //cout << t_inicio << endl;

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
    //string arg3, arg4, arg5;
    if(argc >= 4)
    {
        if(stoi(argv[3]) == 1)
        {
            cout << "3" << endl;
            isDirecionado = true;
        }
    }
    if(argc >= 5)
    {

        if(stoi(argv[4]) == 1)
        {
            cout << "4" << endl;
            isPonderadoNo = true;
        }
    }
    if(argc >= 6)
    {

        if(stoi(argv[5]) == 1)
        {
            cout << "5" << endl;
            isPonderadoAresta = true;
        }
    }
    if(argc >= 7)
    {
        solucao_best = stof(argv[6]);
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

    //verifica a quantidade de parametros recebidos
    if(argc < 3)
    {
        cout << "Número de parametros insuficiente. use: main <arq entrada> <arq saida> no mínimo." << endl;
        cout << "Ou use parametros opcionais nessa ordem após os obrigatórios: <direcionado> <ponderadoVertice> <ponderadoAresta>" << endl;
        return 0;
    }

    // Inicia o grafo
    Grafo *g = new Grafo(formato, arquivoEntrada, arquivoSaida, isDirecionado, isPonderadoNo, isPonderadoAresta);

    //testepoda
    Utils u;
    u.gerarArquivoGraphViz(g,"C:/Users/gabic/Desktop/grafos2019_1/membros/gabriele/Parte2/instancias/antes.gv");
    Steiner *stenio=new Steiner(g->getTerminais(),g->getNumTerminais());
    stenio->poda(g);
    u.gerarArquivoGraphViz(g,"C:/Users/gabic/Desktop/grafos2019_1/membros/gabriele/Parte2/instancias/depois.gv");
    return 0;

    //teste arestas
    /*
    No*p = g->getListaNos();
    while(p != NULL){
        Aresta *a = p->getAresta();
        while(a != NULL){
            cout << "testa aresta " << p->getId() << "--" << a->getNoAdj()<<endl;
            if(g->getAresta(p->getId(), a->getNoAdj())!= NULL){
                cout << "aresta passou" << endl;
            } else {
                cout << "problema na aresta" << endl;
                return 1;
            }
            a = a->getProx();
        }
        p = p->getProx();
    }
    return 0;
    */

    /*
    Utils u;
    Grafo *grafo = new Grafo(false, true, false);
    grafo->adicionaNo(1, 1);
    u.imprime(grafo);
    grafo->removeNo(1);
    u.imprime(grafo);
    grafo->adicionaAresta(2, 1, 3, 1, 1);
    grafo->adicionaAresta(4, 1, 5, 1, 1);
    grafo->adicionaAresta(6, 1, 7, 1, 1);
    grafo->adicionaAresta(2, 1, 7, 1, 1);
    u.imprime(grafo);
    grafo->removeAresta(4, 5);
    u.imprime(grafo);
    u.gerarArquivoGraphViz(grafo, "../saidas/teste1.gv");
    return 0;
    */
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

            Log::getInstance().line("[timestamp], [tempo], [custo], [best], [erro]");
            string linhaRes = to_string(unix_timestamp()) + "," + to_string(resultado.tempo) + "," + to_string(resultado.custo) + "," + to_string(solucao_best) + "," + to_string(erro);
            Log::getInstance().line(linhaRes);
            Log::getInstance().breakLine();

            //grava no arquivo
            Log::getInstance().salvaLinhaNoArquivo(linhaRes, "../saidas/G_" + nomeArquivoSemExtensao + ".csv");
        }

        if(cmd == "11"){
            Log::getInstance().line("\n## Algoritmo guloso randomizado para Arvore de Steiner ##\n");
            float alfa = 0;
            int numIteracoes = 1000;
            float erro = 0;

            Log::getInstance().line("Digite o valor de alfa e o numero de iteracoes");
            cin >> alfa >> numIteracoes;
            Log::getInstance().lineArquivo(to_string(alfa) + " " + to_string(numIteracoes));

            ResultadoGuloso resultado = g->gulosoRandomizado(alfa, numIteracoes);

            if(solucao_best != 0){
                //calcula o erro
                erro = fabs((resultado.custo - solucao_best) / solucao_best);
            }

            Log::getInstance().line("[timestamp], [tempo], [custo], [best], [erro], [semente]");
            string linhaRes = to_string(unix_timestamp()) + "," + to_string(resultado.tempo) + "," + to_string(resultado.custo) + "," + to_string(solucao_best) + "," + to_string(erro) + "," + to_string(resultado.semente);
            Log::getInstance().line(linhaRes);
            Log::getInstance().breakLine();

            //grava no arquivo
            Log::getInstance().salvaLinhaNoArquivo(linhaRes, "../saidas/GR_" + nomeArquivoSemExtensao + ".csv");
        }

        if(cmd == "12"){
            Log::getInstance().line("\n## Algoritmo guloso randomizado reativo para Arvore de Steiner ##\n");
            int numIteracoes = 1000;
            float erro = 0;
            float alfa = 0;

            Log::getInstance().line("Digite o numero de iteracoes");
            cin >> numIteracoes;
            Log::getInstance().line(to_string(numIteracoes));

            ResultadoGuloso resultado = g->gulosoRandomizadoReativo(numIteracoes);

            if(solucao_best != 0){
                //calcula o erro
                erro = fabs((resultado.custo - solucao_best) / solucao_best);
            }

            //grava no log
            Log::getInstance().line("[timestamp], [tempo], [custo], [best], [erro], [semente]");
            string linhaRes = to_string(unix_timestamp()) + "," + to_string(resultado.tempo) + "," + to_string(resultado.custo) + "," + to_string(solucao_best) + "," + to_string(erro) + "," + to_string(resultado.semente);
            Log::getInstance().line(linhaRes);
            Log::getInstance().breakLine();

            //grava no arquivo
            Log::getInstance().salvaLinhaNoArquivo(linhaRes, "../saidas/GRR_" + nomeArquivoSemExtensao + ".csv");
        }

        if(cmd == "13"){
            Log::getInstance().line("\n## Algoritmo extra para Arvore de Steiner ##\n");

            ResultadoGuloso resultado = g->gulosoExtra();
            float erro = 0;

            if(solucao_best != 0){
                //calcula o erro
                erro = fabs((resultado.custo - solucao_best) / solucao_best);
            }

            //grava no log
            Log::getInstance().line("[timestamp], [media tempo], [media custo], [best], [erro]");
            string linhaRes = to_string(unix_timestamp()) + "," + to_string(resultado.tempo) + "," + to_string(resultado.custo) + "," + to_string(solucao_best) + "," + to_string(erro);
            Log::getInstance().line(linhaRes);
            Log::getInstance().breakLine();

            //grava no arquivo
            Log::getInstance().salvaLinhaNoArquivo(linhaRes, "../saidas/GEX_" + nomeArquivoSemExtensao + ".csv");
        }
    }

    return 0;
}
