// hexa.h
//
// funcoes para calcular posicoes na tela, espalhadas como em uma colmeia
//

#ifndef HEXA_H  // evita inclusão múltipla
#define HEXA_H

// tipo de dados ponto
typedef struct {
  float x;
  float y;
} ponto;

// chame essa função uma vez para inicializar o calculador de hexas
// dist_max é a maior distância necessaria entre o centro e algum hexágono;
// dist_hexa é a distância entre centros de hexagonos;
// centro é o ponto onde fica o centro dos hexágonos (eles giram em relação a esse ponto).
void hexa_inicio(int dist_max, float dist_hexa, int xcentro, int ycentro);

// número de hexágonos (eles são numerados de 0 a num_hexa()-1)
int num_hexa(void);

// o n;umero do hexágono que está no centro da cachopa
int hexa_centro(void);

// retorna a posicao do centro da hexágono número h, se o ângulo da cachopa for a
ponto pos_hexa(int h, float a);

// retorna o número do hexágono que contém a posição p,
// se o ângulo da cachopa for a
int hexa_pos(ponto p, float a);

// retorna o número do hexágono que é o i-ésimo vizinho do hexágono de número h
// i pode ser entre 0 e 5
// pode retornar -1 se não houver o tal vizinho
int vizinho(int h, int i);

#endif // HEXA_H
