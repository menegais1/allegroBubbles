#include <stdio.h>
#include <stdlib.h>


#include "tela.h"
#include "hexa.h"


#ifndef helpers_h
#define helpers_h

#define CANHAO 1
#define HELP 2
#define SAIR 3

#define LARGURA_TELA 680
#define ALTURA_TELA 650

#define X_CANHAO LARGURA_TELA / 2
#define Y_CANHAO 100

#define RAIO_BOLA 15
#define BOLA_COLISAO_RAIO RAIO_BOLA * 0.75f
#define VELOCIDADE_BOLA 10.0f
#define RAIO_BOLA_SEGUINTE RAIO_BOLA * 0.75f
#define DESLOCAMENTO_BOLA_SEGUINTE 1.15f

#define NUM_MAX_COLISOES 6

#define TAMANHO_SETA 30


typedef struct {
    float x;
    float y;
} Coordenadas;

typedef struct {
    float x;
    float y;
} Vetor;

typedef struct {
    Coordenadas pontoInicial;
    Coordenadas pontoFinal;
} Parede;


typedef struct {
    int cor;
    int numBolinhas;
} CorBolinhas;

#endif // canhao


typedef enum {
    NAO_GERADA,
    DISPARADA,
    GERADA,
    DESTRUIDA,
    INCORPORADA
} EstadoBolaEnum;

typedef enum {
    CIMA, BAIXO, DIREITA, ESQUERDA, NENHUMA
} DirecaoColisaoEnum;

typedef struct {
    CorBolinhas corBolinhas[6];
} Hexagono;


typedef struct {
    int faseAtual;
    char helpAberto;
} Controle;


typedef struct {
    float velocidade;
    Vetor direcao;
    Coordenadas posicao;
    int cor;
    int raio;
    EstadoBolaEnum estado;
    int numColisoes;
} Bola;

typedef struct {
    Vetor direcao;
    Bola bolaAtual;
    Bola bolaSeguinte;
    char disparado;
    int errosAtuais;
} Canhao;


const Parede paredeCima = {
        {10,  100},
        {670, 100}
};
const Parede paredeBaixo = {
        {10,  640},
        {670, 640}
};
const Parede paredeEsquerda = {
        {10, 100},
        {10, 640}
};
const Parede paredeDireita = {
        {670, 100},
        {670, 640}
};


void desenhaLayout();

void desenhaJogo(Canhao *canhao, Hexagono *hexagono);

int CliqueDoMouse(int x, int y);

void renderiza(Hexagono *hexagono, Canhao *canhao);

void inicializaCoresBolinhas(Hexagono *hexagono);

Bola geraBola(Coordenadas posicao, int raio, float velocidade, CorBolinhas corBolinhas[]);

void inicializaCanhao(Canhao *canhao, Hexagono *hexagono);

void disparaCanhao(Canhao *canhao);

void moveBola(Bola *bola);

void inicializaHexagono(Hexagono *hexagono);

int colideBola(Coordenadas posicao, Bola *bola);

float absFloat(float number) {
    return number < 0 ? number * -1 : number;
}

float absInt(int number) {
    return number < 0 ? number * -1 : number;
}

void desenhaLayout() {

    //fundo branco
    tela_retangulo(0, 0, LARGURA_TELA, ALTURA_TELA, 0, 0, branco);

    //layout de cima
    tela_retangulo(0, 0, LARGURA_TELA, 100, 5, preto, azul);

    //Sair
    tela_retangulo(625, 5, 675, 25, 0, 0, vermelho);
    tela_texto(650, 15, 18, branco, "Sair");

    //Canhao
    tela_circulo(LARGURA_TELA / 2, 100, 60, 0, 0, branco);

    //Pontua��o
    tela_retangulo(80, 40, 250, 80, 2, preto, verde);
    tela_texto_dir(90, 50, 20, preto, "Pontuacao:");

    //Fase
    tela_retangulo(430, 40, 530, 80, 2, preto, verde);
    tela_texto_dir(440, 50, 20, preto, "Fase:");

    //help
    tela_retangulo(550, 40, 630, 80, 2, preto, verde);
    tela_texto_dir(565, 50, 20, preto, "Help");

    //mouse
    tela_circulo(tela_rato_x(), tela_rato_y(), 5, 2, preto, branco);

    //linhas de colisao
    //Coordenadas parede de cima :   xi=10    xf=670;        y = 100;
    //Coordenadas parede de baixo :  xi=10    xf=670;        y = 640;

    //Coordenadas parede da esquerda: x=10;         yi = 100  yf = 640;
    //Coordenadas parede da direita:  x=670;        yi = 100 yf = 640;

    tela_linha(paredeBaixo.pontoInicial.x, paredeBaixo.pontoInicial.y, paredeBaixo.pontoFinal.x,
               paredeBaixo.pontoFinal.y,
               0, preto);
    tela_linha(paredeEsquerda.pontoInicial.x, paredeEsquerda.pontoInicial.y, paredeEsquerda.pontoFinal.x,
               paredeEsquerda.pontoFinal.y, 0, preto);
    tela_linha(paredeDireita.pontoInicial.x, paredeDireita.pontoInicial.y, paredeDireita.pontoFinal.x,
               paredeDireita.pontoFinal.y, 0, preto);
}

void desenhaHelp() {
    tela_retangulo(90, 120, 610, 520, 0, 0, azul);
    tela_texto(350, 140, 30, preto, "Como jogar:");
    tela_texto(130, 170, 15, verde, "O jogador deve eliminar todas as bolinhas da tela para");
    tela_texto(130, 170, 15, verde, "eliminar todas as");
    tela_texto(130, 170, 15, verde, "bolinhas da tela para");
    tela_texto_dir(130, 185, 15, preto, "passar de fase.");
    tela_texto_dir(130, 200, 15, preto, "Faça o maximo de pontuação possivel destruindo as bolinhas!");
    tela_texto_dir(130, 215, 15, preto, "Para pontuar é muito simples, basta ");

}

void desenhaSeta(Canhao *canhao) {

    float xSeta, ySeta;

    xSeta = tela_rato_x() - X_CANHAO;
    ySeta = tela_rato_y() - Y_CANHAO;

    //ySeta = ySeta / (xSeta + ySeta);

    tela_linha(X_CANHAO, Y_CANHAO + 20, xSeta, ySeta * TAMANHO_SETA, 5, vermelho);


}

void atualizaCanhao(Canhao *canhao, Hexagono *hexagono) {

    Coordenadas posicaoBolaSeguinte = {X_CANHAO, Y_CANHAO - (RAIO_BOLA * 2 * DESLOCAMENTO_BOLA_SEGUINTE)};

    canhao->bolaAtual = canhao->bolaSeguinte;

    canhao->bolaAtual.raio = RAIO_BOLA;
    canhao->bolaAtual.posicao.x = X_CANHAO;
    canhao->bolaAtual.posicao.y = Y_CANHAO;

    canhao->bolaSeguinte = geraBola(posicaoBolaSeguinte, RAIO_BOLA_SEGUINTE, VELOCIDADE_BOLA, hexagono->corBolinhas);

    canhao->bolaSeguinte.estado = GERADA;

}

void desenhaJogo(Canhao *canhao, Hexagono *hexagono) {

    Bola bolaAtual = canhao->bolaAtual;
    Bola bolaSeguinte = canhao->bolaSeguinte;

    if (canhao->disparado) {
        if (canhao->bolaAtual.estado == DISPARADA) {
            moveBola(&canhao->bolaAtual);
            tela_circulo(bolaAtual.posicao.x, bolaAtual.posicao.y, bolaAtual.raio, 1, preto, bolaAtual.cor);
        }
    } else {
        tela_circulo(bolaAtual.posicao.x, bolaAtual.posicao.y, bolaAtual.raio, 1, preto, bolaAtual.cor);
    }

    tela_circulo(bolaSeguinte.posicao.x, bolaSeguinte.posicao.y, bolaSeguinte.raio, 1, preto, bolaSeguinte.cor);


}

//ARRUMAR OS DEFINES
int CliqueDoMouse(int x, int y) {
    int LugarDoClique = 0;

    if (y >= 5 && y <= 25 && x >= 625 && x <= 675) {
        LugarDoClique = SAIR;
    } else if (y >= 40 && y <= 80 && x >= 550 && x <= 630) {
        LugarDoClique = HELP;
    } else if (y > 100) {
        LugarDoClique = CANHAO;
    } else {
        LugarDoClique = 0;
    }

    return LugarDoClique;
}


void atualiza(Controle *controle, Hexagono *hexagono, Canhao *canhao) {
    int xClique, yClique, clique = 0;

    while (1) {
        tela_inicia_desenho();
        desenhaLayout();
        desenhaJogo(canhao, hexagono);

        if (canhao->bolaAtual.numColisoes > NUM_MAX_COLISOES) {
            canhao->bolaAtual.estado = DESTRUIDA;
            canhao->disparado = 0;
            atualizaCanhao(canhao, hexagono);
        }

        if (controle->helpAberto == 1) {
            desenhaHelp();
        }


        desenhaSeta(canhao);

        if (tela_rato_clicado() == 1) {
            xClique = tela_rato_x_clique();
            yClique = tela_rato_y_clique();
            clique = CliqueDoMouse(xClique, yClique);

            canhao->direcao.x = xClique - X_CANHAO;
            canhao->direcao.y = yClique - Y_CANHAO;

            if (controle->helpAberto == 1) {
                controle->helpAberto = 0;
            } else {
                switch (clique) {
                    case SAIR:
                        return;
                        break;
                    case HELP:
                        controle->helpAberto = 1;
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


        tela_termina_desenho();
    }

}

void inicializaCoresBolinhas(Hexagono *hexagono) {

    hexagono->corBolinhas[0].cor = amarelo;
    hexagono->corBolinhas[1].cor = verde;
    hexagono->corBolinhas[2].cor = marrom;
    hexagono->corBolinhas[3].cor = laranja;
    hexagono->corBolinhas[4].cor = rosa;
    hexagono->corBolinhas[5].cor = vermelho;
    //Alterar para zero após testar
    hexagono->corBolinhas[0].numBolinhas = 1;
    hexagono->corBolinhas[1].numBolinhas = 1;
    hexagono->corBolinhas[2].numBolinhas = 1;
    hexagono->corBolinhas[3].numBolinhas = 1;
    hexagono->corBolinhas[4].numBolinhas = 1;
    hexagono->corBolinhas[5].numBolinhas = 1;

    return;
}


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

void inicializaCanhao(Canhao *canhao, Hexagono *hexagono) {

    canhao->errosAtuais = 0;
    canhao->disparado = 0;
    canhao->direcao.x = 0;
    canhao->direcao.y = 0;

    Coordenadas posicaoBolaAtual = {X_CANHAO, Y_CANHAO};
    Coordenadas posicaoBolaSeguinte = {X_CANHAO, Y_CANHAO - (RAIO_BOLA * 2 * DESLOCAMENTO_BOLA_SEGUINTE)};
    do {
        canhao->bolaAtual = geraBola(posicaoBolaAtual, RAIO_BOLA, VELOCIDADE_BOLA, hexagono->corBolinhas);
        canhao->bolaSeguinte = geraBola(posicaoBolaSeguinte, RAIO_BOLA_SEGUINTE, VELOCIDADE_BOLA,
                                        hexagono->corBolinhas);

    } while (canhao->bolaAtual.estado != GERADA || canhao->bolaSeguinte.estado != GERADA);

}


void inicializaHexagono(Hexagono *hexagono) {

    inicializaCoresBolinhas(hexagono);

}


void disparaCanhao(Canhao *canhao) {
    canhao->disparado = 1;
    canhao->bolaAtual.estado = DISPARADA;
    Vetor direcao = {canhao->direcao.x, canhao->direcao.y};

    float varianca = (absFloat(direcao.x) + absFloat(direcao.y));
    direcao.x = direcao.x / varianca;
    direcao.y = direcao.y / varianca;
    canhao->bolaAtual.direcao = direcao;
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

int main() {
    srand(time(NULL));

    Controle controle;
    Hexagono hexagono;
    Canhao canhao;

    inicializaHexagono(&hexagono);
    inicializaCanhao(&canhao, &hexagono);
    tela_inicio(LARGURA_TELA, ALTURA_TELA, "BubbleSpinner");

    atualiza(&controle, &hexagono, &canhao);

}

