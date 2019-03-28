#include "LeitorGrafo.h"

LeitorGrafo::LeitorGrafo(string arquivoEntrada)
{
    nomeArquivoEntrada = arquivoEntrada;
    indice_add_grafo = 0;
}

LeitorGrafo::~LeitorGrafo()
{
    //destrutor
    if(indice_add_grafo > 0){
        for(int i=0; i < numVertices; i++){
            ObjGrafo *no = grafo[i];

            //deleta todas as arestas do vertice
            ObjGrafo *p = NULL;
            ObjGrafo *a = no->getAresta();
            while(a != NULL){
                p = a->getAresta();
                delete a; 
                a = p;               
            }

            //deleta o vertice
            delete no;
        }
    } 

    //deleta o vetor que armazena os nos
    delete grafo;
}

/**
 * Esse metodo faz a leitura do arquivo txt e já vai gravando ele numa lista de adjacência
 **/
void LeitorGrafo::parse(){
    bool isPrimeiraLinha = true;
    int a, b, c;
    ObjGrafo *no_a = NULL;
    ObjGrafo *no_b = NULL;

    //abre arquivo de entrada
    inFile.open(nomeArquivoEntrada);
    string line;
    
    //verifica se o arquivo foi aberto
    if (!inFile || !inFile.is_open()) {
        log.logString("Impossivel abrir o arquivo");
        exit(1); // sai do programa se nao conseguir abrir o arquivo
    }
    
    while (getline(inFile, line)) {
        // using printf() in all tests for consistency
        //log.logString(line.c_str());
        istringstream iss(line);

        if(isPrimeiraLinha){
            //obtem o numero de vertices contido na primeira linha do arquivo
            iss >> numVertices;

            //registra que ja passou pela primeira linha
            isPrimeiraLinha = false;

            //cria vetor de nós
            grafo = new ObjGrafo*[numVertices];

            log.logString("Num Vertices: " + to_string(numVertices));
        } else {
            //obtem grupos de 3 inteiros de cada linha nas variaveis a, b, c da esq pra dir de acordo com o txt
            if (!(iss >> a >> b >> c)) { 
                log.logString("Erro de leitura!");
                exit(1); // sai do programa se houver algum erro de leitura
            } 
            log.logString("Aresta do vertice '" + to_string(a) + "' para o vertice '" + to_string(b) + "', com peso '" + to_string(c) + "'");

            //verifica existencia dos vertices de rotulo a, b
            no_a = NULL;
            no_b = NULL;
            if(indice_add_grafo > 0){
                for(int i=0; i < indice_add_grafo; i++){
                    ObjGrafo *no = grafo[i];
                    int rotulo = no->getRotulo();
                    if(no->getRotulo() == a){
                        no_a = no;
                    }
                    if(no->getRotulo() == b){
                        no_b = no;
                    }
                }
            } 

            //se nao existir o vertice de rotulo a, criar
            if(no_a == NULL){
                no_a = new ObjGrafo();
                no_a->setRotulo(a);
                grafo[indice_add_grafo] = no_a;
                indice_add_grafo++;
            }

            //se nao existir o vertice de rotulo b, criar
            if(no_b == NULL){
                no_b = new ObjGrafo();
                no_b->setRotulo(b);
                grafo[indice_add_grafo] = no_b;
                indice_add_grafo++;
            }

            //cria a aresta
            ObjGrafo *aresta = new ObjGrafo();
            aresta->setPeso(c);
            aresta->setNo(no_b);

            //adiciona a aresta a primeira posicao se nao tiver nenhuma aresta
            if(no_a->getAresta() == NULL){
                no_a->setAresta(aresta);
            } else {
                //vai até a ultima aresta
                ObjGrafo *a = no_a->getAresta();
                while(a->getAresta() != NULL){
                    a = a->getAresta();
                }
                //e adiciona lá
                a->setAresta(aresta);
            }
        }
    }
    
    //fecha arquivo de entrada
    inFile.close();
}

/**
 * Imprime o grafo de maneira bem simples
 * Esse metodo é só pra testar e não deve ser usado no projeto final
 **/
void LeitorGrafo::imprimir(){
    if(indice_add_grafo > 0){
        for(int i=0; i < numVertices; i++){
            ObjGrafo *no = grafo[i];

            cout << "no: " << no->getRotulo() << " ";

            //vai até a ultima aresta
            for(ObjGrafo *a = no->getAresta(); a != NULL; a = a->getAresta()){
                int rotulo;
                if(a->getNo() != NULL){
                    rotulo = a->getNo()->getRotulo();
                } else {
                    rotulo = -1;
                }
                cout << "aresta(no:" << rotulo << ", peso:"<< a->getPeso() << ") ";
            }

            cout << endl;
        }
    } 
}