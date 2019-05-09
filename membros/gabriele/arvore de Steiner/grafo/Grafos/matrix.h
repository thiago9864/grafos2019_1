#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
 class Matrix_adj{
 public:
     Matrix_adj(int tamanho);
     ~Matrix_adj();
     void inserirMatrix(int indNo1,int indNo2,float peso);
     int retornaIndNo(int ind);
     void inserirIndNo(int ind);
     int grauEntrada(int ind);
     int grauSaida(int ind);

 private:
     int ordem;
     float matrix[ordem][ordem];//matriz com os pesos das arestas
     int indNo[ordem];//vetor de indice dos nós(hasing com a matriz´=)
     int cont;
 };


#endif // MATRIX_H_INCLUDED
