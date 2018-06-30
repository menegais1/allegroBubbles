

#include "hexa.h"
#include "helpers.h"
#include "bola.h"

#ifndef hexagono_h
#define hexagono_h

typedef struct {
    CorBolinhas corBolinhas[6];
    float raioHexagono;
    float angulo;
    BolaHexagono *bolaHexagonos;
} Hexagono;

void inicializaCoresBolinhas(Hexagono *hexagono);

void inicializaHexagono(Hexagono *hexagono);

#endif // hexagono
