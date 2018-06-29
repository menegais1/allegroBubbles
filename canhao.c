

#include "helpers.h"
#include "canhao.h"
#include "hexagono.h"
#include "bola.h"
#include "tela.h"

void atualizaCanhao(Canhao *canhao, Hexagono *hexagono) {

    Coordenadas posicaoBolaSeguinte = {X_CANHAO, Y_CANHAO - (RAIO_BOLA * 2 * DESLOCAMENTO_BOLA_SEGUINTE)};

    canhao->bolaAtual = canhao->bolaSeguinte;

    canhao->bolaAtual.raio = RAIO_BOLA;
    canhao->bolaAtual.posicao.x = X_CANHAO;
    canhao->bolaAtual.posicao.y = Y_CANHAO;

    do {
        canhao->bolaSeguinte = geraBola(posicaoBolaSeguinte, RAIO_BOLA_SEGUINTE, VELOCIDADE_BOLA,
                                        hexagono->corBolinhas);
    } while (canhao->bolaSeguinte.estado != GERADA);

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

void disparaCanhao(Canhao *canhao) {
    canhao->disparado = 1;
    canhao->bolaAtual.estado = DISPARADA;
    Vetor direcao = {canhao->direcao.x, canhao->direcao.y};

    float varianca = (absFloat(direcao.x) + absFloat(direcao.y));
    direcao.x = direcao.x / varianca;
    direcao.y = direcao.y / varianca;
    canhao->bolaAtual.direcao = direcao;
}
