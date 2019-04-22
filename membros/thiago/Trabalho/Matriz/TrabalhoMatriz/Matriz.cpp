#include "Matriz.h"

Matriz::Matriz(int n)
{
    _n = n;
    
    // aloca o vetor de vetores
    matriz = new int*[n];

    // aloca cada um dos vetores (cada linha)
    for(int i = 0; i < n; i++)
    {
        //aloca um vetor temporario
        int *tmp = new int[n];

        //seta valores 0
        for(int i = 0; i < n; i++)
        {
            tmp[i] = 0;
        }

        //passa ponteiro do vetor tmp pra matriz
        matriz[i] = tmp;
    }

}

Matriz::~Matriz()
{
    // desaloca a matriz
    for(int i = 0; i < _n; i++)
    {
        delete [] matriz[i];
    }
    delete [] matriz;
}

/**
 * Esse metodo insere um valor na matriz
 * parametro: i (indice da linha)
 * parametro: j (indice da coluna)
 * parametro: valor (valor a inserir)
 * encapsulamento: public
 **/
void Matriz::setValor(int i, int j, int valor){
    if(i >= 0 && i < _n && j >= 0 && j < _n){
        matriz[i][j] = valor;
    }
}

/**
 * Esse metodo imprime essa matriz
 * parametro: indices (ponteiro para a instancia da classe Indice)
 * encapsulamento: public
 **/
void Matriz::imprime(Indice *indices){
    int numCasas = 3;
    char fillchar = ' ';
    string espacador = " ";

    //espaço da linha dos indices
    for(int i=0; i < numCasas; i++){
        cout << fillchar;
    }
    cout << espacador;
    
    //insere linha de indices
    for(int i = 0; i < indices->getTamIndice(); i++){
        cout << setfill(fillchar) << setw(numCasas) << indices->getPos(i) << espacador;
    }
    cout << endl;

    for(int i = 0; i < _n; i++){
        //insere coluna de indices
        cout << setfill(fillchar) << setw(numCasas) << indices->getPos(i) << espacador;

        //insere valores
        for(int j = 0; j < _n; j++){
            cout << setfill(fillchar) << setw(numCasas) << matriz[i][j] << espacador;
        }
        cout << endl;
    }
}


