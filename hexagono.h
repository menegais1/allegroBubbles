


#ifndef hexagono_h
#define hexagono_h

#include "helpers.h"

typedef struct {
    CorBolinhas corBolinhas[6];
    float raioHexagono;
    float angulo;
    BolaHexagono *bolaHexagonos;
} Hexagono;

void inicializaCoresBolinhas(Hexagono *hexagono);

void inicializaHexagono(Hexagono *hexagono);

#endif // hexagono
