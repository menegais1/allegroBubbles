
#include "bola.h"
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



int colideBola(Coordenadas posicao, Bola *bola) {

    int colisao = NENHUMA;
    if (posicao.x - BOLA_COLISAO_RAIO < paredeEsquerda.pontoInicial.x) {
        colisao = ESQUERDA;
    } else if (posicao.x + BOLA_COLISAO_RAIO > paredeDireita.pontoInicial.x) {
        colisao = DIREITA;
    } else if (posicao.y + BOLA_COLISAO_RAIO > paredeBaixo.pontoInicial.y) {
        colisao = BAIXO;
    } else if (posicao.y - BOLA_COLISAO_RAIO < paredeCima.pontoInicial.y && bola->direcao.y < 0) {
        colisao = CIMA;
    }
    return colisao;
}

void moveBola(Bola *bola) {

    Coordenadas posicao = bola->posicao;
    posicao.x = bola->posicao.x + bola->direcao.x * bola->velocidade;
    posicao.y = bola->posicao.y + bola->direcao.y * bola->velocidade;
    switch (colideBola(posicao, bola)) {
        case DIREITA:
            bola->numColisoes++;
            bola->direcao.x *= -1;
            break;
        case ESQUERDA:
            bola->numColisoes++;
            bola->direcao.x *= -1;
            break;
        case CIMA:
            bola->numColisoes++;
            bola->direcao.y *= -1;
            break;
        case BAIXO:
            bola->numColisoes++;
            bola->direcao.y *= -1;
            break;
        case NENHUMA:
            break;
        default:
            break;
    }

    posicao.x = bola->posicao.x + bola->direcao.x * bola->velocidade;
    posicao.y = bola->posicao.y + bola->direcao.y * bola->velocidade;

    bola->posicao = posicao;


}
