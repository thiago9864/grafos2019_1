#include "ObjGrafo.h"

ObjGrafo::ObjGrafo()
{
    //construtor
    aresta = NULL;
    no = NULL;
}

ObjGrafo::~ObjGrafo()
{
    //destrutor
}

int ObjGrafo::getRotulo() { return rotulo; }
void ObjGrafo::setRotulo(int rot) { rotulo = rot; }

int ObjGrafo::getPeso() { return peso; }
void ObjGrafo::setPeso(int pes) { peso = pes; }

ObjGrafo* ObjGrafo::getAresta() { return aresta; }
void ObjGrafo::setAresta(ObjGrafo *a) { aresta = a; }

ObjGrafo* ObjGrafo::getNo() { return no; }
void ObjGrafo::setNo(ObjGrafo *n) { no = n; }