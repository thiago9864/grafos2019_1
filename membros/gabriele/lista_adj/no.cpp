#include <iostream>
#include "aresta.h"
#include "no.h"
using namespace std;

 No::No(){}
 No::~No(){}
 int No::getGrauEntrada(){
          return grauEntrada;
 }
 int No::getGrauSaida(){
     return grauSaida;
 }
 void No::setAresta_adj(Aresta *aresta_adj){
     this.aresta_adj=aresta_adj;
 }
 Aresta No:: *getAresta_adj(){
     return *aresta_adj;
 }
 void No::setId(int num){
     id=num;
 }
 int No::getId(){
     return id;
 }
 void No::setPeso(int peso){
     this.peso=peso;
 }
 int No::getPeso(){
     return peso;
 }
 void No::conta_grauEntrada(){
 }
 void No::conta_grauSaida(){
 }
