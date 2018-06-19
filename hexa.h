// hexa.h
//
// funcoes para calcular posicoes na tela, espalhadas como em uma colmeia
//

#ifndef HEXA_H  // evita inclus�o m�ltipla
#define HEXA_H

// tipo de dados ponto
typedef struct {
  float x;
  float y;
} ponto;

// chame essa fun��o uma vez para inicializar o calculador de hexas
// dist_max � a maior dist�ncia necessaria entre o centro e algum hex�gono;
// dist_hexa � a dist�ncia entre centros de hexagonos;
// centro � o ponto onde fica o centro dos hex�gonos (eles giram em rela��o a esse ponto).
void hexa_inicio(int dist_max, float dist_hexa, int xcentro, int ycentro);

// n�mero de hex�gonos (eles s�o numerados de 0 a num_hexa()-1)
int num_hexa(void);

// o n;umero do hex�gono que est� no centro da cachopa
int hexa_centro(void);

// retorna a posicao do centro da hex�gono n�mero h, se o �ngulo da cachopa for a
ponto pos_hexa(int h, float a);

// retorna o n�mero do hex�gono que cont�m a posi��o p,
// se o �ngulo da cachopa for a
int hexa_pos(ponto p, float a);

// retorna o n�mero do hex�gono que � o i-�simo vizinho do hex�gono de n�mero h
// i pode ser entre 0 e 5
// pode retornar -1 se n�o houver o tal vizinho
int vizinho(int h, int i);

#endif // HEXA_H
