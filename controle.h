

#include "hexa.h"
#include "helpers.h"
#include "bola.h"
#include "canhao.h"
#include "hexagono.h"

#ifndef controle_h
#define controle_h

typedef struct {
    int pontuacao;
    char nome[20];
} Recorde;

typedef struct {
    int faseAtual;
    int pontuacao;
    Recorde recordes[10];
    char helpAberto;
    char recordesAberto;
} Controle;



int cliqueDoMouse(int x, int y);

void atualiza(Controle *controle, Hexagono *hexagono, Canhao *canhao);


#endif // controle
