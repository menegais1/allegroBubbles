


#ifndef canhao_h
#define canhao_h



#include "hexa.h"
#include "bola.h"
#include "hexagono.h"
#include "helpers.h"


typedef struct {
    Vetor direcao;
    Bola bolaAtual;
    Bola bolaSeguinte;
    char disparado;
    int errosAtuais;
} Canhao;



void inicializaCanhao(Canhao *canhao, Hexagono *hexagono);

void disparaCanhao(Canhao *canhao);

void atualizaCanhao(Canhao *canhao, Hexagono *hexagono);

#endif // canhao
