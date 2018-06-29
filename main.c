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
    srand(time(NULL));

    Controle controle;
    Hexagono hexagono;
    Canhao canhao;

    controle.pontuacao = 0;

    inicializaParedes();
    inicializaHexagono(&hexagono);
    inicializaCanhao(&canhao, &hexagono);

    tela_inicio(LARGURA_TELA, ALTURA_TELA, "BubbleSpinner");

    atualiza(&controle, &hexagono, &canhao);

}

