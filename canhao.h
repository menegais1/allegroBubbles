

#include "hexa.h"
#include "bola.h"
#include "hexagono.h"
#include "helpers.h"

#ifndef canhao_h
#define canhao_h

typedef struct
{
    bola _bolaAtual;
    bola _proxBola;
    int quantidadeErrosAtual;
    int disparado;
    direcao _direcao;
} canhao;

//Dispara a bolinha atual do canhao, usando a posicao x e y do mouse para definir a direcao
void disparaCanhao(direcao _direcao);

//Inicializa o canhao com a bolinha atual e a proxima bolinha
void inicializaCanhao(canhao *_canhao, hexagono *_hexagono);

//Atualiza o estado do canhao e checa o estado da bolinha atual
void atualizaCanhao();

#endif // canhao
