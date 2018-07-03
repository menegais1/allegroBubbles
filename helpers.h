
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

#define HEXA_CENTRO_X LARGURA_TELA / 2
#define HEXA_CENTRO_Y ALTURA_TELA / 1.75
#define DIST_HEXA_CENTRO LARGURA_TELA / 1.50

#define NUM_INICIAL_HEXA 5

#define MAX_DIST_NUM_INICIAL_HEXA_X HEXA_CENTRO_X + (RAIO_BOLA * 2 * NUM_INICIAL_HEXA )
#define MAX_DIST_NUM_INICIAL_HEXA_Y HEXA_CENTRO_Y + (RAIO_BOLA * 1.2 * NUM_INICIAL_HEXA )
#define MIN_DIST_NUM_INICIAL_HEXA_X HEXA_CENTRO_X - (RAIO_BOLA * 2 * NUM_INICIAL_HEXA )
#define MIN_DIST_NUM_INICIAL_HEXA_Y HEXA_CENTRO_Y - (RAIO_BOLA * 1.4 * NUM_INICIAL_HEXA )
#define TEMPO_DE_GIRO_HEXAGONO 40

#define BOLAS_ADICIONADAS 3
#define RODADAS_TOTAIS_PARA_ADICIONAR 10

typedef struct {
    float x;
    float y;
} Coordenadas;

//declarado como ponto para facilitar o codigo
typedef struct {
    int numHexa;
    int cor;
    char existe;
} BolaHexagono;

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
    SUPERIOR_DIREITA, SUPERIOR_ESQUERDA, INFERIOR_DIREITA, INFERIOR_ESQUERDA
} QuadranteHexagonoEnum;

typedef enum {
    CIMA, BAIXO, DIREITA, ESQUERDA, NENHUMA, HEXAGONO
} DirecaoColisaoEnum;


typedef enum {
    CANHAO,
    HELP,
    SAIR,
    RECORDE,
    JOGAR_NOVAMENTE,
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
