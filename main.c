#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#include "tela.h"
#include "hexa.h"

#include "controle.h"
#include "hexagono.h"
#include "bola.h"
#include "canhao.h"
#include "helpers.h"
#include "desenha.h"


int main() {
    int exit=0;

    srand(time(NULL));

    Controle controle;
    Hexagono hexagono;
    Canhao canhao;
    controle.faseAtual=1;

    inicializaParedes();

    do {

    if(controle.faseAtual == 1){
        controle.pontuacao = 0;
    }


    inicializaHexagono(&hexagono);
    inicializaCanhao(&canhao, &hexagono);

    tela_inicio(LARGURA_TELA, ALTURA_TELA, "BubbleSpinner");

    exit = atualiza(&controle, &hexagono, &canhao);

    }while(exit == 0);

}

