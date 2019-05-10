#include <iostream>
#include <string>
#include "Grafo.h"

/* Linha de comando pra rodar
UNIX (macOS / Linux): clear && g++ -std=c++11 *.cpp -o grafosGrupo7 && ./grafosGrupo7 ../data/entrada_conexas.txt ../data/saida.txt 0 0 1
*/

#include <iostream>
#include <string>
#include "Grafo.h"
#include "Steiner.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 6) {
        cout << "Argumentos passados invalidos";

        return 0;
    }

    Grafo *g;

    // Verificando a quantidade de argumentos passados
    if (argc == 6) {
        g = new Grafo(argv[1], argv[2], stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
    } else if (argc == 5) {
        g = new Grafo(argv[1], argv[2], stoi(argv[3]), stoi(argv[4]));
    } else if (argc == 4) {
        g = new Grafo(argv[1], argv[2], stoi(argv[3]));
    } else {
        g = new Grafo(argv[1], argv[2]);
    }

    g->imprime();

    Grafo *p = g->getComplementar();

    p->imprime();

    //teste 1 da busca em profundidade (Thiago)
    Aresta *caminho;
    cout << endl << "**** Busca em Profundidade ****" << endl << endl;

    caminho = g->buscaEmProfundidade(80, 90);
    cout << "Procura caminho 80-90." << endl;
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

    cout << endl << "**** Caminho Mínimo ****" << endl << endl;

    //teste 1 caminho minimo
    Steiner s(g);
    float distancia = s.obtemMenorDistancia(25, 10);

    cout << "Distancia minima entre 25 e 10: " << distancia << endl;

    return 0;
}
