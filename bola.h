

#include "hexa.h"
#include "helpers.h"

#ifndef bola_h
#define bola_h

typedef struct
{
    int cor;
    float velocidade;
    direcao _direcao;
    ponto _posicao;
    int raio;
    int _estado;
} bola;

//Modifica a posicao da bolinha se baseando na direcao e velocidade
void moveBolinha(float velocidade, direcao _direcao);

//Gera a bolinha com base no array de cores existentes no hexagono e inicializa alguns valores
void geraBolinha(corBolinhas _corBolinhas[], float velocidade, int tamanho);

//Modifica o estado atual da bolinha com base no enum estado
void estadoBolinha(int _estado);

//altera a direcao da bolinha com base na colis�o com a parede
void ricocheteiaBolinha();

//Checa a colisao da bolinha usando a velocidade e posicao atual e retorna o valor da colisao
void colisaoBolinha();

#endif // bola
