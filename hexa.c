#include "hexa.h"

#include <math.h>

// valores auxiliares para determinar os hexágonos
//   o número de hexágonos tem uma boa folga, para garantir que em qualquer ângulo 
//   se consiga encher a tela.
// Os hexágonos são numeradas de 0 a max_hexa-1.
// 
// Os hexágonos estão organizados em linhas e colunas, e numerados
// conforme o desenho (considerando linhas com 7 hexas):
//   _/ 0\__/ 1\__/ 2\_
//    \__/ 7\__/ 8\__/
//   _/14\__/15\__/16\_
//    \__/21\__/22\__/
// a primeira linha tem os hexágonos 0-6, a segunda linha 7-13, etc

// numero de linhas de hexágonos (tem uma linha a cada dist_hexa/2)
int n_lin;
// numero de colunas de hexágonos (tem uma coluna a cada 1,6 dist_hexa +-)
int n_col;

// qual a linha e coluna do hexágono do centro
#define LIN_CENTRO (n_lin/2)
#define COL_CENTRO (n_col/2)

// onde fica o centro da cachopa
//   você pode alterar esses valores caso a cachopa deva ficar um pouco fora
//   do centro da janela.
ponto pos_centro;

// distancia entre centros de hexágonos vizinhos na cachopa
float dist_hexa;

// chame essa função uma vez para inicializar o calculador de hexas
// dist_max é a maior distância necessaria entre o centro e algum hexágono;
// dist_hexa é a distância entre centros de hexagonos;
// centro é o ponto onde fica o centro dos hexágonos (eles giram em relação a esse ponto).
void hexa_inicio(int dist_max, float dh, int xcentro, int ycentro)
{
  pos_centro.x = xcentro;
  pos_centro.y = ycentro;
  dist_hexa = dh;
  n_lin = (dist_max*3/dist_hexa);
  n_col = (n_lin/3);
}

// número de hexágonos (eles são numerados de 0 a num_hexa()-1)
int num_hexa(void)
{
  return n_lin*n_col;
}

// número do hexágono que está no centro
int hexa_centro(void)
{
  return LIN_CENTRO*n_col + COL_CENTRO;
}


// retorna a posição do centro do hexágono número h, se o ângulo da cachopa for a
ponto pos_hexa(int h, float a)
{
  // linha e coluna da bola (em hexágonos) em relacao a bola 0
  int l, c;
  l = h / n_col;
  c = h % n_col;
  // coordenadas x e y em relacao a bola 0, sem rodar
  float x0, y0;
  x0 = c * sqrt(3)*dist_hexa + (l&1)*sqrt(3)/2*dist_hexa;
  y0 = l * dist_hexa/2;
  // coordenadas do centro en relacao a bola 0, sem rodar
  float xc0, yc0;
  xc0 = COL_CENTRO * sqrt(3)*dist_hexa + (LIN_CENTRO&1)*sqrt(3)/2*dist_hexa;
  yc0 = LIN_CENTRO * dist_hexa/2;
  // coordenadas x e y em relacao ao centro, sem rodar
  float x, y;
  x = x0 - xc0;
  y = y0 - yc0;
  // coordenadas em relacao ao centro, apos a rotacao
  float xr, yr;
  xr = x*cos(a) - y*sin(a);
  yr = x*sin(a) + y*cos(a);
  // coordenadas em relacao à janela
  ponto pos;
  pos.x = xr + pos_centro.x;
  pos.y = yr + pos_centro.y;

  return pos;
}

// retorna o número do hexágono que contém a posição p,
// se o ângulo da cachopa for a
int hexa_pos(ponto p, float a)
{
  // coordenadas em relação ao centro da cachopa
  float xr, yr;
  xr = p.x - pos_centro.x;
  yr = p.y - pos_centro.y;
  // coordenadas em relação à cachopa não girada
  float x, y;
  x = xr*cos(-a) - yr*sin(-a);
  y = xr*sin(-a) + yr*cos(-a);
  // coordenadas em relação à janela
  float xj, yj;
  xj = x + pos_centro.x;
  yj = y + pos_centro.y;
  // coordenadas em relação ao hexágono 0
  float x0, y0;
  ponto pos0 = pos_hexa(0, 0);
  x0 = xj - pos0.x;
  y0 = yj - pos0.y;
  // linha e coluna em float, int e a dif
  float cf, lf;
  int l, c;
  float dl, dc;
  lf = y0 / (dist_hexa/2);
  l = floor(lf);
  cf = (x0 - (l&1)*sqrt(3)/2*dist_hexa) / (sqrt(3)*dist_hexa);
  c = floor(cf);
  dl = lf - l;
  dc = cf - c;
  // dl e dc vão de 0 a <1
  //   dl=dc=0 é o ponto de cima a esquerda na fig abaixo
  //   dl=0 e dc=1 é o ponto da direita. dl=1 é a parte de baixo da figura.
  // Tem que corrigir l e c de acordo com a posição na figura:
  //   A - l e c estão OK
  //   C - l OK, tem que incrementar c
  //   B - incrementa l, e se a linha era ímpar incrementa c
  //      .    ____    .
  //      | A /    \ C |
  //      |__/  B   \__|
  //
  if ((dc + dl/6) < 1.0/3) {
    // OK
  } else if ((dc - dl/6) >= 2.0/3) {
    c++;
  } else {
    c += l&1;
    l++;
  }
  return l*n_col + c;
}

// retorna o número do hexágono que é o i-ésimo vizinho do hexágono de número h
// i pode ser entre 0 e 5
// pode retornar -1 se não houver o tal vizinho
int vizinho(int h, int i)
{
  // linha e coluna do hexágono h (em hexágonos) em relação ao hexágono 0
  int l, c;
  l = h / n_col;
  c = h % n_col;

  switch (i) {
    case 0: // vizinho de cima
      if (l <= 1) return -1;
      return h - 2*n_col;
    case 1: // vizinho de baixo
      if (l >= n_lin-2) return -1;
      return h + 2*n_col;
    case 2: // vizinho da esquerda no alto
      if (l <= 0) return -1;
      if (l%2 == 0) {
        if (c <= 0) return -1;
        return h - n_col - 1;
      } else {
        if (c < 0) return -1;
        return h - n_col;
      }
    case 3: // vizinho da esquerda embaixo
      if (l >= n_lin-1) return -1;
      if (l%2 == 0) {
        if (c <= 0) return -1;
        return h + n_col - 1;
      } else {
        if (c < 0) return -1;
        return h + n_col;
      }
    case 4: // vizinho da direita no alto
      if (l <= 0) return -1;
      if (l%2 == 0) {
        if (c >= n_col) return -1;
        return h - n_col;
      } else {
        if (c >= n_col-1) return -1;
        return h - n_col + 1;
      }
    case 5: // vizinho da direita embaixo
      if (l >= n_lin-1) return -1;
      if (l%2 == 0) {
        if (c >= n_col) return -1;
        return h + n_col;
      } else {
        if (c >= n_col-1) return -1;
        return h + n_col + 1;
      }
  }
  return -1;
}
