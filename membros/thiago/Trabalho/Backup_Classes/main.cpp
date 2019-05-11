#include <iostream>
#include <string>

using namespace std;

int tamVetor;
int* visitados;
int *numVisitados;

void imprime(){
    for(int i=0; i < 6; i++)
    {
        cout << visitados[i] << " ";
    }
    cout << endl;
}


void setVisitado(int id)
{
    //cout << *numVisitados << endl;

    if(*numVisitados == 0 || visitados[*numVisitados-1] < id)
    {
        //se o vetor estiver vazio, ou o id for maior que o ultimo valor, insere em o(1)
        visitados[*numVisitados] = id;
        (*numVisitados)++;
        cout << "a" << endl;
    }
    else if(*numVisitados == 1)
    {
        //o vetor tem 1 e o id é menor que o visitados[0], insere em o(1)
        int aux = visitados[0];
        visitados[0] = id;
        visitados[*numVisitados] = aux;
        (*numVisitados)++;
        cout << "b" << endl;
    }
    else
    {
        imprime();
        /* code */
        int i;

        for(i=0; i < *numVisitados; i++)
        {
            if(visitados[i] > id)
            {
                break;
            }
        }
        for(int j=*numVisitados; j > i; j--)
        {
            visitados[j] = visitados[j-1];
        }
        visitados[i] = id;
        
        //insere o ultimo
        (*numVisitados)++;
        cout << "c" << endl;
    }
    
}


int main(int argc, char* argv[]) {
    int nv = 0;

    tamVetor = 6;
    visitados = new int[tamVetor];
    numVisitados = &nv;

    for(int j = 0; j < tamVetor; j++){
        visitados[j] = 0;
    }

    setVisitado(25);
    setVisitado(13);
    setVisitado(20);
    setVisitado(24);
    setVisitado(50);
    setVisitado(1);

    imprime();

    return 0;
}
