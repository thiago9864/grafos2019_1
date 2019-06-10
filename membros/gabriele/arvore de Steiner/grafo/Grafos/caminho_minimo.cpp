#include <iostream>
#include "caminho_minimo.h"

using namespace std;





caminho::caminho(Grafo *a){
    g=a;
    no=g->getgetListaNos();
    Aresta *aresta=a->
    for(int i=0;i<g->getOrdem() && no!=NULL;i++,no=no->getProx()){
        indNo[i]=no->getId();
        marcador[i]=false;
        indCaminho[i]=-1;
        caminhoPeso[i]=999999;
        caminho[i]=-1;
    }
    no=NULL;

}
caminho::~caminho(){};
caminho::montandoMatriz(){
    for(int i=0;i<g->getOrdem();i++){
        auxMontando(i);
    }
}
caminho::auxMontando(int ind){

}
