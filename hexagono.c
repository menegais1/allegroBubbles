
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
    float posTrianguloCima = 1.8, posTrianguloBaixo = 0.3;
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
        } else if (posHexa.x <= MAX_DIST_NUM_INICIAL_HEXA_X - (RAIO_BOLA * posTrianguloCima * NUM_INICIAL_HEXA) &&
                   posHexa.x >= MIN_DIST_NUM_INICIAL_HEXA_X + (RAIO_BOLA * posTrianguloCima * NUM_INICIAL_HEXA) &&
                   posHexa.y >= MIN_DIST_NUM_INICIAL_HEXA_Y - (RAIO_BOLA * 1 * NUM_INICIAL_HEXA) &&
                   posHexa.y <= MIN_DIST_NUM_INICIAL_HEXA_Y) {

            hexagono->bolaHexagonos[i].existe = 1;
            int cor;
            cor = rand() % 6;
            hexagono->corBolinhas[cor].numBolinhas++;
            hexagono->bolaHexagonos[i].cor = hexagono->corBolinhas[cor].cor;
            posTrianguloCima -= 0.165;

        } else if (posHexa.x <= MAX_DIST_NUM_INICIAL_HEXA_X - (RAIO_BOLA * posTrianguloBaixo * NUM_INICIAL_HEXA) &&
                   posHexa.x >= MIN_DIST_NUM_INICIAL_HEXA_X + (RAIO_BOLA * posTrianguloBaixo * NUM_INICIAL_HEXA) &&
                   posHexa.y <= MAX_DIST_NUM_INICIAL_HEXA_Y + (RAIO_BOLA * 1 * NUM_INICIAL_HEXA) &&
                   posHexa.y >= MAX_DIST_NUM_INICIAL_HEXA_Y) {

            hexagono->bolaHexagonos[i].existe = 1;
            int cor;
            cor = rand() % 6;
            hexagono->corBolinhas[cor].numBolinhas++;
            hexagono->bolaHexagonos[i].cor = hexagono->corBolinhas[cor].cor;
            posTrianguloBaixo += 0.165;
        } else {
            hexagono->bolaHexagonos[i].existe = 0;
        }
    }
    hexagono->bolaHexagonos[234].existe = 0;
}

void inicializaGiro(Coordenadas coordenadas, Vetor direcao, Hexagono *hexagono) {
    hexagono->girando = 1;
    //ARRUMAR A VELOCIDADE
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
            if (direcao.x > 0 && direcao.y < 0) {
                hexagono->direcao = 1;
            } else if (direcao.x < 0 && direcao.y < 0) {
                hexagono->direcao = -1;
            } else if (direcao.x < 0 && direcao.y > 0) {
                hexagono->direcao = 1;
            }
            break;
    }


}

int incorporaBolaHexagono(Coordenadas posicao, int cor, Hexagono *hexagono) {
    ponto posHexa = {posicao.x, posicao.y};
    int numHexa = hexa_pos(posHexa, hexagono->angulo);
    hexagono->bolaHexagonos[numHexa].existe = 1;
    hexagono->bolaHexagonos[numHexa].cor = cor;

    int i, j, vizinhos[300], numVizinhos = 0, vizinhoHexa, pontuacao = 0;

    for (i = 0; i < 6; i++) {
        vizinhoHexa = vizinho(numHexa, i);
        if (vizinhoHexa != -1) {
            if (hexagono->bolaHexagonos[vizinhoHexa].existe == 1 &&
                hexagono->bolaHexagonos[vizinhoHexa].cor == cor) {
                vizinhos[numVizinhos] = vizinhoHexa;
                numVizinhos++;
            }
        }
    }

    if (numVizinhos >= 1) {
        for (i = 0; i < numVizinhos; i++) {
            for (j = 0; j < 6; j++) {
                vizinhoHexa = vizinho(vizinhos[i], j);
                if (vizinhoHexa != -1 && buscaVizinho(vizinhoHexa, vizinhos, numVizinhos) == 0) {
                    if (hexagono->bolaHexagonos[vizinhoHexa].existe == 1 &&
                        hexagono->bolaHexagonos[vizinhoHexa].cor == cor) {
                        vizinhos[numVizinhos] = vizinhoHexa;
                        numVizinhos++;
                    }
                }
            }
        }
    }

    if (numVizinhos > 2) {
        pontuacao = -1;
        for (i = 0; i < numVizinhos; i++) {
            hexagono->bolaHexagonos[vizinhos[i]].existe = 0;
            hexagono->bolaHexagonos[vizinhos[i]].cor = transparente;
            pontuacao++;
        }

        int existeVizinhos = 0;

        for (i = 0; i <= num_hexa(); i++) {
            if (hexagono->bolaHexagonos[i].existe == 1) {
                existeVizinhos = 0;
                for (j = 0; j < 6; j++) {
                    vizinhoHexa = vizinho(i, j);
                    if (vizinhoHexa != -1) {
                        if (hexagono->bolaHexagonos[vizinhoHexa].existe == 1) {
                            existeVizinhos = 1;
                        }
                    }
                }
                if (existeVizinhos != 1) {
                    hexagono->bolaHexagonos[i].existe = 0;
                    hexagono->bolaHexagonos[i].cor = transparente;
                    pontuacao++;
                }
            }
        }

    }
    return pontuacao;
}

int buscaVizinho(int num, int array[], int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        if (array[i] == num) {
            return 1;
        }
    }
    return 0;
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

int checaColisaoParedeHexagono(Hexagono *hexagono) {
    int x, y, numHexa;
    ponto posicaoHexa;
    for (x = paredeCima.pontoInicial.x, y = paredeCima.pontoInicial.y;
         x <= paredeCima.pontoFinal.x; x += RAIO_BOLA) {
        posicaoHexa.x = x;
        posicaoHexa.y = y;
        numHexa = hexa_pos(posicaoHexa, hexagono->angulo);
        if (hexagono->bolaHexagonos[numHexa].existe == 1) {
            return 1;
        }
    }
    for (x = paredeBaixo.pontoInicial.x, y = paredeBaixo.pontoInicial.y;
         x <= paredeBaixo.pontoFinal.x; x += RAIO_BOLA) {
        posicaoHexa.x = x;
        posicaoHexa.y = y;
        numHexa = hexa_pos(posicaoHexa, hexagono->angulo);
        if (hexagono->bolaHexagonos[numHexa].existe == 1) {
            return 1;
        }
    }
    for (x = paredeEsquerda.pontoInicial.x, y = paredeEsquerda.pontoInicial.y;
         y <= paredeEsquerda.pontoFinal.y; y += RAIO_BOLA) {
        posicaoHexa.x = x;
        posicaoHexa.y = y;
        numHexa = hexa_pos(posicaoHexa, hexagono->angulo);
        if (hexagono->bolaHexagonos[numHexa].existe == 1) {
            return 1;
        }
    }
    for (x = paredeDireita.pontoInicial.x, y = paredeDireita.pontoInicial.y;
         y <= paredeDireita.pontoFinal.y; y += RAIO_BOLA) {
        posicaoHexa.x = x;
        posicaoHexa.y = y;
        numHexa = hexa_pos(posicaoHexa, hexagono->angulo);
        if (hexagono->bolaHexagonos[numHexa].existe == 1) {
            return 1;
        }
    }

    return 0;
}


