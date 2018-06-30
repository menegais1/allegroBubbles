


#ifndef hexagono_h
#define hexagono_h

#include "helpers.h"

typedef struct {
    CorBolinhas corBolinhas[6];
    float raioHexagono;
    float angulo;
    float velocidade;
    char girando;
    BolaHexagono *bolaHexagonos;
} Hexagono;

void inicializaCoresBolinhas(Hexagono *hexagono);

void inicializaHexagono(Hexagono *hexagono);

void giraHexagono(float direcao, Hexagono *hexagono);

#endif // hexagono
