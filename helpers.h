
#ifndef helpers_h
#define helpers_h

#define CANHAO 1
#define HELP 2
#define SAIR 3

#define LARGURA_TELA 680
#define ALTURA_TELA 650

#define X_CANHAO LARGURA_TELA / 2
#define Y_CANHAO 100


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
