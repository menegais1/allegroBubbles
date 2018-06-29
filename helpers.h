
#ifndef helpers_h
#define helpers_h

#define LARGURA_TELA 680
#define ALTURA_TELA 650

#define X_CANHAO LARGURA_TELA / 2
#define Y_CANHAO 100

#define RAIO_BOLA 15
#define BOLA_COLISAO_RAIO RAIO_BOLA * 0.75f
#define VELOCIDADE_BOLA 10.0f
#define RAIO_BOLA_SEGUINTE RAIO_BOLA * 0.75f
#define DESLOCAMENTO_BOLA_SEGUINTE 1.15f
#define TOTAL_RECORDES 10
#define DESLOCAMENTO_RECORDES 17
#define NUM_MAX_COLISOES 6


typedef struct {
    float x;
    float y;
} Coordenadas;

typedef struct {
    float x;
    float y;
} Vetor;

typedef struct {
    Coordenadas pontoInicial;
    Coordenadas pontoFinal;
} Parede;


typedef struct {
    int cor;
    int numBolinhas;
} CorBolinhas;

typedef enum {
    NAO_GERADA,
    DISPARADA,
    GERADA,
    DESTRUIDA,
    INCORPORADA
} EstadoBolaEnum;

typedef enum {
    CIMA, BAIXO, DIREITA, ESQUERDA, NENHUMA
} DirecaoColisaoEnum;

typedef enum {
    CANHAO,
    HELP,
    SAIR,
    RECORDE,
    NENHUM
} CliqueMouseEnum;

 Parede paredeCima;
 Parede paredeBaixo;
 Parede paredeEsquerda;
 Parede paredeDireita;


float absFloat(float number);

int absInt(int number);

void inicializaParedes();

#endif // helpers
