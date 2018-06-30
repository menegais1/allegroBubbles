


#ifndef bola_h
#define bola_h

#include "helpers.h"
#include "hexagono.h"

typedef struct {
    float velocidade;
    Vetor direcao;
    Coordenadas posicao;
    int cor;
    int raio;
    EstadoBolaEnum estado;
    int numColisoes;
} Bola;

Bola geraBola(Coordenadas posicao, int raio, float velocidade, CorBolinhas corBolinhas[]);

void moveBola(Bola *bola);

int colideBola(Coordenadas posicao, Bola *bola, Hexagono *hexagono);

Coordenadas atualizaPosicao(Bola *bola);

int atualizaBola(Bola *bola, Hexagono *hexagono);

#endif // bola
