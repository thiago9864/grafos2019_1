#include <iostream>
#include"matrix_adj.h"

using namespace std;

Matrix_adj::Matrix_adj(int tamanho){
    ordem=tamanho;
    cont=0;
    for(int i=0;i<tam;i++){
        for(int j=0;j<tam;j++){
            matrix[i][j]=0;
        }
    }
}
Matrix_adj::~Matrix_adj(){}

int Matrix_adj::grauEntrada(int ind){
    int indice;
    float soma=0;
    indice=retornaIndNo(ind);
    if(indice!=-1){
        for(int i=0;i<tam;i++){
            if(matrix[][i]!=0){
                soma+=1;
            }
        }
    }
    return soma;
}

int Matrix_adj::grauSaida(int ind){
    int indice;
    float soma=0;
    indice=retornaIndNo(ind);
    if(indice!=-1){
        for(int i=0;i<tam;i++){
            if(matrix[i][]!=0){
                soma+=1;
            }
        }
    }
    return soma;
}

void Matrix_adj::inserirIndNo(int ind){
    bool pular=false;
    for(int i=0;i<cont;i++){
        if(indNo[i]==ind){
            pular=true;
            break;
        }
    }
    if(pular==false){
      indNo[cont]=ind;
      cont++;
    }
}
int Matrix_adj::retornaIndNo(int ind){
    for(int i=0;i<cont;i++){
        if(indNo[i]==ind){
            return i;
        }
    }
    return -1;
}
void Matrix_adj::inserirMatrix(int indNo1,int indNo2,float peso){
    int ind1,ind2;
    ind1=retornaIndNo(indNo1);
    ind2=retornaIndNo(indNo2);
    if(ind1!==-1 && ind2!=-1){
        matrix[ind1][ind2]=peso;
        matrix[ind2][ind1]=peso;
    }
}
