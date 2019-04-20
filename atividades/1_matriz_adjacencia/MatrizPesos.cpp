#include "MatrizPesos.h"

MatrizPesos::MatrizPesos(int n)
{
    _n = n;
    log = new Log("saida.txt");

    // aloca o vetor de vetores
    matriz = new float*[n];

    // aloca cada um dos vetores (cada linha)
    for(int i = 0; i < n; i++)
    {
        //aloca um vetor temporario
        float *tmp = new float[n];

        //seta valores 0
        for(int i = 0; i < n; i++)
        {
            tmp[i] = 0;
        }

        //passa ponteiro do vetor tmp pra matriz
        matriz[i] = tmp;
    }

}

MatrizPesos::~MatrizPesos()
{
    // desaloca a matriz
    for(int i = 0; i < _n; i++)
    {
        delete [] matriz[i];
    }
    delete [] matriz;
    delete log;
}

/**
 * Esse metodo insere um valor na matriz
 * parametro: i (indice da linha)
 * parametro: j (indice da coluna)
 * parametro: valor (valor a inserir)
 * encapsulamento: public
 **/
void MatrizPesos::setValor(int i, int j, float valor){
    if(i >= 0 && i < _n && j >= 0 && j < _n){
        matriz[i][j] = valor;
    }
}


/**
 * Esse metodo imprime essa matriz
 * parametro: indices (ponteiro para a instancia da classe Indice)
 * encapsulamento: public
 **/
void MatrizPesos::imprime(Indice *indices){
    int numCasas = 3;
    char fillchar = ' ';
    string espacador = " ";
    stringstream ss;

    //espaço da linha dos indices
    for(int i=0; i < numCasas; i++){
        ss << fillchar;
    }
    ss << espacador;

    //insere linha de indices
    for(int i = 0; i < indices->getTamIndice(); i++){
        ss << setfill(fillchar) << setw(numCasas) << indices->getPos(i) << espacador;
    }
    ss << endl;

    for(int i = 0; i < _n; i++){
        //insere coluna de indices
        ss << setfill(fillchar) << setw(numCasas) << indices->getPos(i) << espacador;

        //insere valores
        for(int j = 0; j < _n; j++){
            ss << setfill(fillchar) << setw(numCasas) << matriz[i][j] << espacador;
        }
        ss << endl;
    }
    log->textoPuro(ss.str());
}


