

#ifndef helpers_h
#define helpers_h

typedef struct
{
    int x;
    int y;
} direcao;

typedef struct
{
    int cor;
    int numBolinhas;
} corBolinhas;

enum estado
{
    DISPARADA,
    GERADA,
    DESTRUIDA,
    INCORPORADA
};

enum colisao
{
    PAREDE,
    HEXA,
    NULA
};
#endif // canhao
