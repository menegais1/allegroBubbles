


#ifndef hexagono_h
#define hexagono_h

#include "helpers.h"

typedef struct {
    CorBolinhas corBolinhas[6];
    float raioHexagono;
    float angulo;
    float velocidade;
    int direcao;
    char girando;
    BolaHexagono *bolaHexagonos;
} Hexagono;

void inicializaCoresBolinhas(Hexagono *hexagono);

void inicializaHexagono(Hexagono *hexagono);

void inicializaGiro(Coordenadas coordenadas, Vetor direcao,Hexagono *hexagono);

void giraHexagono(Hexagono *hexagono);

#endif // hexagono
