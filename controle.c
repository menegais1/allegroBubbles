#include <stdio.h>

#include "tela.h"
#include "hexagono.h"
#include "controle.h"
#include "desenha.h"

#include "canhao.h"
#include "bola.h"
#include "helpers.h"


//ARRUMAR OS DEFINES
int cliqueDoMouse(int x, int y) {
    int lugarDoClique = NENHUM;

    if (y >= 5 && y <= 25 && x >= 625 && x <= 675) {
        lugarDoClique = SAIR;
    } else if (y >= 45 && y <= 75 && x >= 550 && x <= 630) {
        lugarDoClique = HELP;
    } else if (y >= 45 && y <= 75 && x >= 420 && x <= 540) {
        lugarDoClique = RECORDE;
    } else if (y > 100) {
        lugarDoClique = CANHAO;
    }

    return lugarDoClique;
}


int atualiza(Controle *controle, Hexagono *hexagono, Canhao *canhao) {
    int xClique, yClique, clique;

    while (1) {


        if (canhao->disparado) {
            atualizaBola(&canhao->bolaAtual, hexagono);
            switch (canhao->bolaAtual.estado) {
                case DISPARADA:
                    moveBola(&canhao->bolaAtual);
                    break;
                case DESTRUIDA:
                    canhao->disparado = 0;
                    atualizaCanhao(canhao, hexagono);
                    controle->pontuacao -= 3;
                    break;
                case INCORPORADA:
                    canhao->disparado = 0;
                    inicializaGiro(canhao->bolaAtual.posicao, canhao->bolaAtual.direcao, hexagono);
                    controle->pontuacao += incorporaBolaHexagono(canhao->bolaAtual.posicao, canhao->bolaAtual.cor,
                                                                 hexagono);
                    atualizaCanhao(canhao, hexagono);
                    break;
            }
        }

        if (hexagono->girando == 1) {
            giraHexagono(hexagono);
        }

        printf("COLISAO: %d", checaColisaoParedeHexagono(hexagono));

        if (tela_rato_clicado() == 1) {
            xClique = tela_rato_x_clique();
            yClique = tela_rato_y_clique();
            clique = cliqueDoMouse(xClique, yClique);

            canhao->direcao.x = xClique - X_CANHAO;
            canhao->direcao.y = yClique - Y_CANHAO;

            if (controle->helpAberto == 1) {
                controle->helpAberto = 0;
            } else if (controle->recordesAberto == 1) {
                controle->recordesAberto = 0;
            } else {
                switch (clique) {
                    case SAIR:
                        return 1;
                        break;
                    case HELP:
                        controle->helpAberto = 1;
                        break;
                    case RECORDE:
                        controle->recordesAberto = 1;
                        break;
                    case CANHAO:
                        if (canhao->disparado == 0)
                            disparaCanhao(canhao);
                        break;
                    default:
                        printf("CLIQUE INVALIDO");
                        break;


                }
            }

        }

        //Desenha na tela
        desenha(canhao, hexagono, controle);
    }

    return;
}
