

#include "hexa.h"
#include "helpers.h"
#include "bola.h"

#ifndef hexagono_h
#define hexagono_h

typedef struct
{
    corBolinhas corBolinhas[6];
    float angulo;
    int quantidadeErrosMax;
    int quantidadeBolaAdicionais;
    bola _bolas[1000];
} hexagono;

//Gera N bolinhas que formam um hexagono na tela
void geraHexagono();

//Gira o hexagono a partir da direção em que ocorre a colisao da bolinha (x*direcao*angulo)
void giraHexagono();

 //Checa se há 3 bolas ou mais da mesma cor e destroi elas e as anexadas //Atribui 0 no array de bolas
void destroiBolas();

//Anexa bolas randomicamente ao redor do array de bolas
void adicionaBola();

//Chega se o hexagono colidiu com uma parede (há de chegar enquanto gira o hexagono)
int checaColisao();

#endif // hexagono
