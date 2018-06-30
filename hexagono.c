
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
    //Alterar para zero ap�s testar
    hexagono->corBolinhas[0].numBolinhas = 1;
    hexagono->corBolinhas[1].numBolinhas = 1;
    hexagono->corBolinhas[2].numBolinhas = 1;
    hexagono->corBolinhas[3].numBolinhas = 1;
    hexagono->corBolinhas[4].numBolinhas = 1;
    hexagono->corBolinhas[5].numBolinhas = 1;

    return;
}


void inicializaHexagono(Hexagono *hexagono) {
    hexagono->raioHexagono = RAIO_BOLA;
    hexagono->angulo = 0;
    inicializaCoresBolinhas(hexagono);
    hexa_inicio(DIST_HEXA_CENTRO, hexagono->raioHexagono * 2, HEXA_CENTRO_X, HEXA_CENTRO_Y);

    BolaHexagono *temp = malloc(sizeof(BolaHexagono) * (num_hexa() + 1));
    if (temp == NULL) {
        printf("ERRO AO ALOCAR HEXAGONOS");
        return;
    }

    hexagono->bolaHexagonos = temp;
    int i = 0;
    ponto posHexa;

    for (i = 0; i <= num_hexa(); i++) {

        hexagono->bolaHexagonos[i].numHexa = i;
        posHexa = pos_hexa(i, hexagono->angulo);
        if (posHexa.x <= MAX_DIST_NUM_INICIAL_HEXA_X && posHexa.x >= MIN_DIST_NUM_INICIAL_HEXA_X &&
            posHexa.y <= MAX_DIST_NUM_INICIAL_HEXA_Y && posHexa.y >= MIN_DIST_NUM_INICIAL_HEXA_Y) {
            hexagono->bolaHexagonos[i].existe = 1;
            //REVISAR A EXISTENCIA DESSE CODIGO
            int j, cont = 0,cor;
            do {
                cor = rand() % 6;
                for (j = 0; j <= 5; j++) {
                    int vizinhoHexaNum = vizinho(j, hexagono->angulo);
                    if (hexagono->bolaHexagonos[vizinhoHexaNum].existe == 1) {
                        if (cor == hexagono->bolaHexagonos[vizinhoHexaNum].cor) {
                            cont++;
                        }
                    }
                }
            } while (cont > 1);
            hexagono->corBolinhas[cor].numBolinhas++;
            hexagono->bolaHexagonos[i].cor = hexagono->corBolinhas[cor].cor;
        } else {
            hexagono->bolaHexagonos[i].existe = 0;
        }
    }
}

