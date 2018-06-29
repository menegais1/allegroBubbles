
#include "hexagono.h"
#include "helpers.h"
#include "tela.h"



void inicializaCoresBolinhas(Hexagono *hexagono) {

    hexagono->corBolinhas[0].cor = amarelo;
    hexagono->corBolinhas[1].cor = verde;
    hexagono->corBolinhas[2].cor = marrom;
    hexagono->corBolinhas[3].cor = laranja;
    hexagono->corBolinhas[4].cor = rosa;
    hexagono->corBolinhas[5].cor = vermelho;
    //Alterar para zero após testar
    hexagono->corBolinhas[0].numBolinhas = 1;
    hexagono->corBolinhas[1].numBolinhas = 1;
    hexagono->corBolinhas[2].numBolinhas = 1;
    hexagono->corBolinhas[3].numBolinhas = 1;
    hexagono->corBolinhas[4].numBolinhas = 1;
    hexagono->corBolinhas[5].numBolinhas = 1;

    return;
}





void inicializaHexagono(Hexagono *hexagono) {

    inicializaCoresBolinhas(hexagono);

}

