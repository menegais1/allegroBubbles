



#ifndef controle_h
#define controle_h

#include "hexa.h"
#include "helpers.h"
#include "bola.h"
#include "canhao.h"
#include "hexagono.h"

typedef struct {
    int pontuacao;
    char nome[20];
} Recorde;

typedef struct {
    int faseAtual;
    int pontuacao;
    Recorde recordes[TOTAL_RECORDES];
    char helpAberto;
    char recordesAberto;
    char telaGameOver;
    char recordeGravado;
    int rodadasRestantesParaAdicionar;
} Controle;


void adicionaBolas(Hexagono *hexagono, Controle *controle);

int cliqueDoMouse(int x, int y, Controle *controle);

int atualiza(Controle *controle, Hexagono *hexagono, Canhao *canhao);

void atribuiRecordes(Controle *controle);

int lerArquivo(Controle *controle);

int escreveArquivo(Controle *controle);

void inicializaRecordes(Controle *controle);

#endif // controle
