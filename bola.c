
#include "bola.h"
#include "hexa.h"
#include "helpers.h"
#include <stdlib.h>


Bola geraBola(Coordenadas posicao, int raio, float velocidade, CorBolinhas corBolinhas[]) {

    int cor;
    cor = rand() % 6;
    Bola bola;
    bola.estado = NAO_GERADA;
    if (corBolinhas[cor].numBolinhas != 0) {
        bola.cor = corBolinhas[cor].cor;
        bola.velocidade = velocidade;
        bola.raio = raio;
        bola.estado = GERADA;
        bola.direcao.x = 0;
        bola.direcao.y = 0;
        bola.posicao = posicao;
        bola.numColisoes = 0;
    }

    return bola;
}


int colideBola(Coordenadas posicao, Bola *bola, Hexagono *hexagono) {

    int colisao = NENHUMA;
    if (posicao.x - BOLA_COLISAO_RAIO < paredeEsquerda.pontoInicial.x) {
        colisao = ESQUERDA;
    } else if (posicao.x + BOLA_COLISAO_RAIO > paredeDireita.pontoInicial.x) {
        colisao = DIREITA;
    } else if (posicao.y + BOLA_COLISAO_RAIO > paredeBaixo.pontoInicial.y) {
        colisao = BAIXO;
    } else if (posicao.y - BOLA_COLISAO_RAIO < paredeCima.pontoInicial.y && bola->direcao.y < 0) {
        colisao = CIMA;
    } else {
        int numHexa, i;
        //uso de ponto para facilitar o codigo
        ponto testes[4] = {{posicao.x + BOLA_COLISAO_RAIO, posicao.y},
                           {posicao.x - BOLA_COLISAO_RAIO, posicao.y},
                           {posicao.x, posicao.y - BOLA_COLISAO_RAIO},
                           {posicao.x, posicao.y + BOLA_COLISAO_RAIO}};
        for (i = 0; i < 4; i++) {
            numHexa = hexa_pos(testes[i], hexagono->angulo);
            if (hexagono->bolaHexagonos[numHexa].existe == 1) {
                colisao = HEXAGONO;
            }
        }
    }
    return colisao;
}

void moveBola(Bola *bola) {

    bola->posicao = atualizaPosicao(bola);

}

Coordenadas atualizaPosicao(Bola *bola) {

    Coordenadas posicao = bola->posicao;

    posicao.x = bola->posicao.x + bola->direcao.x * bola->velocidade;
    posicao.y = bola->posicao.y + bola->direcao.y * bola->velocidade;
    return posicao;
}

int atualizaBola(Bola *bola, Hexagono *hexagono) {

    Coordenadas posicao = atualizaPosicao(bola);
    int estadoColisao = colideBola(posicao, bola, hexagono);
    switch (estadoColisao) {
        case DIREITA:
        case ESQUERDA:
            bola->numColisoes++;
            bola->direcao.x *= -1;
            bola->estado = DISPARADA;
            break;
        case CIMA:
        case BAIXO:
            bola->numColisoes++;
            bola->direcao.y *= -1;
            bola->estado = DISPARADA;
            break;
        case HEXAGONO:
            bola->estado = INCORPORADA;
            ponto posHexa = {bola->posicao.x, bola->posicao.y};
            int numHexa = hexa_pos(posHexa, hexagono->angulo);
            hexagono->bolaHexagonos[numHexa].existe = 1;
            hexagono->bolaHexagonos[numHexa].cor = bola->cor;
            break;
        case NENHUMA:
            bola->estado = DISPARADA;
            break;
        default:
            break;
    }

    if (bola->numColisoes >= NUM_MAX_COLISOES) {
        bola->estado = DESTRUIDA;
    }
    return bola->estado;
}
