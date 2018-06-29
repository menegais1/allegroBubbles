

#include "hexa.h"
#include "helpers.h"

#ifndef bola_h
#define bola_h

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

int colideBola(Coordenadas posicao, Bola *bola);

#endif // bola
