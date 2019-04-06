#ifndef MATRIX_ADJ_H_INCLUDED
#define MATRIX_ADJ_H_INCLUDED
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
     int tam;
     float matrix[tam][tam];
     int indNo[tam];
     int cont;
 };


#endif // MATRIX_ADJ_H_INCLUDED
