#include <iostream>
#include <string>
#include "Grafo.h"

/* 
Linha de comando pra rodar

*** txt ***
UNIX (macOS / Linux): clear && g++ -std=c++11 *.cpp -o main && ./main ../data/entrada2.txt ../data/saida.txt 0 0 1
WINDOWS: cls & g++ -std=c++11 *.cpp -o main & main.exe ../data/entrada2.txt ../data/saida.txt 0 0 1

*** stp ***
UNIX (macOS / Linux): clear && g++ -std=c++11 *.cpp -o grafosGrupo7 && ./grafosGrupo7 ../data/bipe2p.stp ../data/saida.txt 0 0 1
WINDOWS: cls & g++ -std=c++11 *.cpp -o grafosGrupo7 & grafosGrupo7.exe ../data/bipe2p.stp ../data/saida.txt 0 0 1


*** Resultados ***
Instancia  | Custo da arvore
bipe2p.stp | 5616

*/

#include <iostream>
#include <string>
#include "Grafo.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 6) {
        cout << "Argumentos passados invalidos";

        return 0;
    }

    Grafo *g;

    //verifica o formato do arquivo
    string arquivoEntrada = argv[1];
    std::size_t found = arquivoEntrada.find("stp");
    string formato = "txt";

    if(found != std::string::npos){
        formato = "stp";
    } 

    // Verificando a quantidade de argumentos passados
    if (argc == 6) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
    } else if (argc == 5) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]), stoi(argv[4]));
    } else if (argc == 4) {
        g = new Grafo(formato, argv[1], argv[2], stoi(argv[3]));
    } else {
        g = new Grafo(formato, argv[1], argv[2]);
    }

    //g->imprime();

    //Grafo *p = g->getComplementar();

    //p->imprime();

    //teste 1 da busca em profundidade (Thiago)
    
    Aresta *caminho;
    cout << endl << "**** Busca em Profundidade ****" << endl << endl;
    
    caminho = g->buscaEmProfundidade(10, 90);
    cout << "Procura caminho 10-90." << endl;
    if(caminho != NULL){
        cout << "Encontrado." << endl;
        Aresta *aux = caminho;
        while(aux != NULL){
            cout << "Aresta: (" << aux->getNoOrigem() << ", " << aux->getNoAdj() << ") peso: " << aux->getPeso() << endl;
            aux = aux->getProx();
        }
        cout << endl;
    } else {
        cout << "Não foi encontrado." << endl;
    }
    /*
    //teste 2 da busca em profundidade (Thiago)
    caminho = g->buscaEmProfundidade(10, 24);
    cout << "Procura caminho 10-24." << endl;
    if(caminho != NULL){
        cout << "Encontrado." << endl;
        Aresta *aux = caminho;
        while(aux != NULL){
            cout << "Aresta: (" << aux->getNoOrigem() << ", " << aux->getNoAdj() << ") peso: " << aux->getPeso() << endl;
            aux = aux->getProx();
        }
        cout << endl;
    } else {
        cout << "Não foi encontrado." << endl;
    }

    //teste 3 da busca em profundidade (Thiago)
    //tenta achar um caminho que não existe entre duas componentes conexas
    caminho = g->buscaEmProfundidade(10, 82);
    cout << "Procura caminho que não existe entre 10-82." << endl;
    if(caminho != NULL){
        cout << "Encontrado." << endl;
        Aresta *aux = caminho;
        while(aux != NULL){
            cout << "Aresta: (" << aux->getNoOrigem() << ", " << aux->getNoAdj() << ") peso: " << aux->getPeso() << endl;
            aux = aux->getProx();
        }
        cout << endl;
    } else {
        cout << "Não foi encontrado." << endl;
    }

    cout << endl << "**** Busca em Largura ****" << endl << endl;

    //teste 1 da busca em largura (Gabriele)
    Aresta *largura;
    cout<<"criou aresta e vai entrar em caminho\n";
    largura=g->caminho_largura(24);
    cout<<"vai entrar no while main\n";
    for(Aresta* a = largura; a != NULL; a = a->getProx()) {
            cout<<"Origem:"<< a->getNoOrigem()<<" ";
            cout<<"Fim:"<<a->getNoAdj()<<"\n";
    }

    //teste 1 da cobertura de vertices (thiago)
    cout << endl << "**** Cobertura de vértices ****" << endl;

    No* cobertura = g->getCoberturaVertices();

    if(cobertura != NULL){
        No *n = cobertura;
        cout << "Cobertura encontrada:" << endl;
        while(n != NULL){
            cout << n->getId() << " ";
            n = n->getProx();
        }
        cout << endl;
    } else {
        cout << "Nenhuma cobertura foi retornada." << endl;
    }
    */

    return 0;
}