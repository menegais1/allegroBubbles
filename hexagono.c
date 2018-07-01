
#include <stdlib.h>
#include <stdio.h>
#include "hexagono.h"
#include "helpers.h"
#include "tela.h"
#include "hexa.h"


void inicializaCoresBolinhas(Hexagono *hexagono) {

    hexagono->corBolinhas[0].cor = amarelo;
    hexagono->corBolinhas[1].cor = verde;
    hexagono->corBolinhas[2].cor = marrom;
    hexagono->corBolinhas[3].cor = laranja;
    hexagono->corBolinhas[4].cor = rosa;
    hexagono->corBolinhas[5].cor = vermelho;

    hexagono->corBolinhas[0].numBolinhas = 0;
    hexagono->corBolinhas[1].numBolinhas = 0;
    hexagono->corBolinhas[2].numBolinhas = 0;
    hexagono->corBolinhas[3].numBolinhas = 0;
    hexagono->corBolinhas[4].numBolinhas = 0;
    hexagono->corBolinhas[5].numBolinhas = 0;

    return;
}


void inicializaHexagono(Hexagono *hexagono) {
    hexagono->raioHexagono = RAIO_BOLA;
    hexagono->angulo = 0;
    hexagono->girando = 0;
    inicializaCoresBolinhas(hexagono);
    hexa_inicio(DIST_HEXA_CENTRO, hexagono->raioHexagono * 2, HEXA_CENTRO_X, HEXA_CENTRO_Y);

    BolaHexagono *temp = malloc(sizeof(BolaHexagono) * (num_hexa() + 1));
    if (temp == NULL) {
        printf("ERRO AO ALOCAR HEXAGONOS");
        return;
    }

    hexagono->bolaHexagonos = temp;
    int i = 0;
    float posTrianguloCima=1.8, posTrianguloBaixo=0.3;
    ponto posHexa;

    for (i = 0; i <= num_hexa(); i++) {

        hexagono->bolaHexagonos[i].numHexa = i;
        posHexa = pos_hexa(i, hexagono->angulo);
        if (posHexa.x <= MAX_DIST_NUM_INICIAL_HEXA_X && posHexa.x >= MIN_DIST_NUM_INICIAL_HEXA_X &&
            posHexa.y <= MAX_DIST_NUM_INICIAL_HEXA_Y && posHexa.y >= MIN_DIST_NUM_INICIAL_HEXA_Y) {
            hexagono->bolaHexagonos[i].existe = 1;
            int cor;
            cor = rand() % 6;
            hexagono->corBolinhas[cor].numBolinhas++;
            hexagono->bolaHexagonos[i].cor = hexagono->corBolinhas[cor].cor;
        } else if (posHexa.x <= MAX_DIST_NUM_INICIAL_HEXA_X - (RAIO_BOLA * posTrianguloCima * NUM_INICIAL_HEXA ) &&
            posHexa.x >= MIN_DIST_NUM_INICIAL_HEXA_X + (RAIO_BOLA * posTrianguloCima * NUM_INICIAL_HEXA )&&
            posHexa.y >= MIN_DIST_NUM_INICIAL_HEXA_Y - (RAIO_BOLA * 1 * NUM_INICIAL_HEXA) &&
            posHexa.y <= MIN_DIST_NUM_INICIAL_HEXA_Y  ) {

            hexagono->bolaHexagonos[i].existe = 1;
            int cor;
            cor = rand() % 6;
            hexagono->corBolinhas[cor].numBolinhas++;
            hexagono->bolaHexagonos[i].cor = hexagono->corBolinhas[cor].cor;
            posTrianguloCima-=0.165;

        }else if (posHexa.x <= MAX_DIST_NUM_INICIAL_HEXA_X - (RAIO_BOLA * posTrianguloBaixo * NUM_INICIAL_HEXA ) &&
            posHexa.x >= MIN_DIST_NUM_INICIAL_HEXA_X + (RAIO_BOLA * posTrianguloBaixo * NUM_INICIAL_HEXA )&&
            posHexa.y <= MAX_DIST_NUM_INICIAL_HEXA_Y + (RAIO_BOLA * 1 * NUM_INICIAL_HEXA) &&
            posHexa.y >= MAX_DIST_NUM_INICIAL_HEXA_Y  ) {

            hexagono->bolaHexagonos[i].existe = 1;
            int cor;
            cor = rand() % 6;
            hexagono->corBolinhas[cor].numBolinhas++;
            hexagono->bolaHexagonos[i].cor = hexagono->corBolinhas[cor].cor;
            posTrianguloBaixo+=0.165;
        }else {
            hexagono->bolaHexagonos[i].existe = 0;
        }
    }
    hexagono->bolaHexagonos[234].existe=0;
}

void inicializaGiro(Coordenadas coordenadas, Vetor direcao, Hexagono *hexagono) {
    hexagono->girando = 1;
    hexagono->velocidade = absFloat(direcao.x) / 100;
    hexagono->direcao = 1;

    int quadrante = SUPERIOR_ESQUERDA;
    if (coordenadas.y < HEXA_CENTRO_Y && coordenadas.x < HEXA_CENTRO_X) {
        quadrante = SUPERIOR_ESQUERDA;
    } else if (coordenadas.y < HEXA_CENTRO_Y && coordenadas.x > HEXA_CENTRO_X) {
        quadrante = SUPERIOR_DIREITA;
    } else if (coordenadas.y > HEXA_CENTRO_Y && coordenadas.x < HEXA_CENTRO_X) {
        quadrante = INFERIOR_ESQUERDA;
    } else if (coordenadas.y > HEXA_CENTRO_Y && coordenadas.x > HEXA_CENTRO_X) {
        quadrante = INFERIOR_DIREITA;
    }

    switch (quadrante) {
        case SUPERIOR_ESQUERDA:
            if (direcao.x < 0 && direcao.y > 0) {
                hexagono->direcao = -1;
            } else if (direcao.x > 0 && direcao.y > 0) {
                hexagono->direcao = 1;
            } else if (direcao.x > 0 && direcao.y < 0) {
                hexagono->direcao = 1;
            }
            break;
        case SUPERIOR_DIREITA:
            if (direcao.x > 0 && direcao.y > 0) {
                hexagono->direcao = 1;
            } else if (direcao.x < 0 && direcao.y > 0) {
                hexagono->direcao = -1;
            } else if (direcao.x < 0 && direcao.y < 0) {
                hexagono->direcao = -1;
            }
            break;
        case INFERIOR_ESQUERDA:
            if (direcao.x > 0 && direcao.y > 0) {
                hexagono->direcao = -1;
            } else if (direcao.x < 0 && direcao.y < 0) {
                hexagono->direcao = -1;
            } else if (direcao.x > 0 && direcao.y < 0) {
                hexagono->direcao = 1;
            }
            break;
        case INFERIOR_DIREITA:
            if (direcao.x > 0  && direcao.y < 0) {
                hexagono->direcao = 1;
            } else if (direcao.x < 0 && direcao.y < 0) {
                hexagono->direcao = -1;
            } else if (direcao.x < 0 && direcao.y > 0) {
                hexagono->direcao = 1;
            }
            break;
    }


}


void giraHexagono(Hexagono *hexagono) {

    hexagono->angulo += hexagono->velocidade * hexagono->direcao;

    hexagono->velocidade -= hexagono->velocidade / TEMPO_DE_GIRO_HEXAGONO;
    if (hexagono->velocidade < 0) {
        hexagono->velocidade = 0;
        hexagono->girando = 0;
        hexagono->direcao = 0;
    }
}

