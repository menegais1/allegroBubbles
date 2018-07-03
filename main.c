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
    int exit = 0, gameRodou = 0, criarArquivo;

    srand(time(NULL));

    Controle controle;
    Hexagono hexagono;
    hexagono.bolaHexagonos = NULL;
    Canhao canhao;


    criarArquivo=lerArquivo(&controle);
    if(criarArquivo == 0 ){
        inicializaRecordes(&controle);
    }

    controle.faseAtual = 1;
    controle.telaGameOver = 0;


    do {


        if (controle.faseAtual == 1) {
            controle.pontuacao = 0;
        }

        controle.rodadasRestantesParaAdicionar = RODADAS_TOTAIS_PARA_ADICIONAR - controle.faseAtual;

        controle.telaGameOver = 0;
        controle.recordeGravado = 0;


        inicializaParedes();
        inicializaHexagono(&hexagono);
        inicializaCanhao(&canhao, &hexagono);

        if(gameRodou == 0 ){
            tela_inicio(LARGURA_TELA, ALTURA_TELA, "BubbleSpinner");
        }

        exit = atualiza(&controle, &hexagono, &canhao);

        gameRodou++;

    } while (exit == 0);

    escreveArquivo(&controle);

    tela_fim();
}

