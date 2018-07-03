

#include <stdio.h>
#include <stdlib.h>

#include "tela.h"
#include "hexa.h"

#include "controle.h"
#include "hexagono.h"
#include "bola.h"
#include "canhao.h"
#include "helpers.h"


void desenhaLayout(Controle *controle) {
    char pontosTexto[13], faseTexto[5];

    //fundo branco
    tela_retangulo(0, 0, LARGURA_TELA, ALTURA_TELA, 0, 0, branco);

    //layout de cima
    tela_retangulo(0, 0, LARGURA_TELA, 100, 5, preto, azul);

    //Sair
    tela_retangulo(625, 5, 675, 25, 0, 0, vermelho);
    tela_texto(650, 15, 18, branco, "Sair");

    //Canhao
    tela_circulo(LARGURA_TELA / 2, 100, 60, 0, 0, branco);

    //Pontuacao
    tela_retangulo(100, 45, 270, 75, 2, preto, verde);
    tela_texto_esq(200, 50, 18, preto, "Pontuacao:");

    sprintf(pontosTexto, "%d", controle->pontuacao);
    tela_texto(235, 61, 18, preto, pontosTexto);

    //Fase
    tela_retangulo(10, 45, 90, 75, 2, preto, verde);
    tela_texto_esq(60, 50, 18, preto, "Fase:");

    sprintf(faseTexto, "%d", controle->faseAtual);
    tela_texto(75,60,18,preto,faseTexto);

    //help
    tela_retangulo(550, 45, 630, 75, 2, preto, verde);
    tela_texto(585, 60, 18, preto, "Help");

    //recordes
    tela_retangulo(420, 45, 540, 75, 2, preto, verde);
    tela_texto(475, 60, 18, preto, "Recordes");

    //linhas de colisao
    tela_linha(paredeBaixo.pontoInicial.x, paredeBaixo.pontoInicial.y, paredeBaixo.pontoFinal.x,
               paredeBaixo.pontoFinal.y,
               0, preto);

    tela_linha(paredeEsquerda.pontoInicial.x, paredeEsquerda.pontoInicial.y, paredeEsquerda.pontoFinal.x,
               paredeEsquerda.pontoFinal.y, 0, preto);
    tela_linha(paredeDireita.pontoInicial.x, paredeDireita.pontoInicial.y, paredeDireita.pontoFinal.x,
               paredeDireita.pontoFinal.y, 0, preto);
}

void desenhaHelp() {
    tela_retangulo(90, 120, 610, 520, 0, 0, azul);
    tela_texto(350, 140, 30, preto, "Como jogar:");

    tela_texto_dir(130, 170, 15, branco, "Faça o maximo de pontuação possivel destruindo as bolas!");
    tela_texto_dir(130, 185, 15, branco, "Para pontuar é muito simples, combinar três bolas ou mais");
    tela_texto_dir(130, 200, 15, branco, "da mesma cor ao disparar o canhão. O jogador recebe uma  ");
    tela_texto_dir(130, 215, 15, branco, "igual a quantidade de bolas destruidas ao disparar. Para");
    tela_texto_dir(130, 230, 15, branco, "disparar é ainda mais simples, basta posicionar o cursor");
    tela_texto_dir(130, 245, 15, branco, "na direção que deseja disparar.");
    tela_texto_dir(130, 275, 15, branco, "O jogador deve tomar cuidado, pois conforme faz jogadas ");
    tela_texto_dir(130, 290, 15, branco, "que nao resultam em destruição de bolas, irão ser adicio-");
    tela_texto_dir(130, 305, 15, branco, "nadas novas bolinhas ao conjunto. Caso a bola seja destrui-");
    tela_texto_dir(130, 320, 15, branco, "da sem acertar o conjunto, o jogador perde 3 pontos.");

    tela_texto_dir(130, 350, 15, branco, "Se alguma bolinha do conjunto encostar em uma das pare-");
    tela_texto_dir(130, 365, 15, branco, "des o jogador perde.");


    tela_texto_dir(130, 380, 15, branco, "O jogador deve eliminar todas as bolas da tela para passar");
    tela_texto_dir(130, 395, 15, branco, "de fase. A cada fase completada, o jogador recebe 10 ve-");
    tela_texto_dir(130, 410, 15, branco, "zes o numero da fase que completou.");
    tela_texto_dir(130, 425, 15, branco, "Sempre que o jogador avançar uma fase, a das proximas ");
    tela_texto_dir(130, 440, 15, branco, "fases serão cada vez maiores");
    tela_texto(350, 500, 10, branco, "Clique na tela para voltar ao jogo");


}
void desenhaRato(){
    tela_circulo(tela_rato_x(), tela_rato_y(), 5, 2, preto, branco);
}

void desenhaRecordes(Controle *controle) {

    tela_retangulo(50, 120, 630, 520, 0, 0, azul);
    tela_texto(350, 140, 30, preto, "Recordes:");

    int i;
    char pontuacao[13], indice[3];

    for (i = 0; i < TOTAL_RECORDES; i++) {
        sprintf(pontuacao, "%d", controle->recordes[i].pontuacao);
        sprintf(indice, "%d", i+1);
        tela_texto_esq(130, 170 + (i * DESLOCAMENTO_RECORDES), 15, branco, indice);
        tela_texto_dir(200, 170 + (i * DESLOCAMENTO_RECORDES), 10, branco, pontuacao);
    }

    tela_texto(LARGURA_TELA/2, 490, 15, branco, "Clique na tela para fechar os recordes");

}


void desenhaJogo(Canhao *canhao, Hexagono *hexagono, Controle *controle) {

    Bola bolaAtual = canhao->bolaAtual;
    Bola bolaSeguinte = canhao->bolaSeguinte;

    desenhaHexagono(hexagono);

    tela_circulo(bolaAtual.posicao.x, bolaAtual.posicao.y, bolaAtual.raio, 1, preto, bolaAtual.cor);


    tela_circulo(bolaSeguinte.posicao.x, bolaSeguinte.posicao.y, bolaSeguinte.raio, 1, preto, bolaSeguinte.cor);

    char rodadasRestantes[2];
    int bolasAdicionadas[2];

    sprintf(rodadasRestantes, "%d", controle->rodadasRestantesParaAdicionar);
    sprintf(bolasAdicionadas, "%d", BOLAS_ADICIONADAS + controle->faseAtual);

    tela_texto_dir(20,ALTURA_TELA-50,10,preto,"Rodadas restantes:");
    tela_texto_dir(130,ALTURA_TELA-50,10,preto,rodadasRestantes);

    tela_texto_dir(20,ALTURA_TELA-40,10,preto,"Bolas a adicionar:");
    tela_texto_dir(130,ALTURA_TELA-40,10,preto,bolasAdicionadas);
}

void desenhaVitoria(){
    tela_retangulo(0,0,LARGURA_TELA,ALTURA_TELA,0,0,branco);
    tela_texto(LARGURA_TELA/2,ALTURA_TELA/2,100,vermelho,"Voce avançou de fase");
    tela_texto(LARGURA_TELA/2,ALTURA_TELA/2+100, 20, vermelho, "Clique na tela para avançar");

}

void desenhaGameOver(){
    tela_retangulo(0, 0, LARGURA_TELA, ALTURA_TELA, 0, 0, preto);
    tela_texto(LARGURA_TELA/2, ALTURA_TELA/2 - 100, 100, branco, "Game Over");

    //Recordes
    tela_retangulo(LARGURA_TELA/2 - 130, ALTURA_TELA/2 + 80, LARGURA_TELA/2 - 10, ALTURA_TELA/2 + 30, 0, 0, vermelho);
    tela_texto(LARGURA_TELA/2 - 70, ALTURA_TELA/2 + 55, 20, branco, "Recordes");

    //Sair
    tela_retangulo(LARGURA_TELA/2 + 10 , ALTURA_TELA/2 + 80, LARGURA_TELA/2 + 130, ALTURA_TELA/2 + 30, 0, 0, vermelho);
    tela_texto(LARGURA_TELA/2 + 70, ALTURA_TELA/2 + 55, 20, branco, "Sair");

    //Jogar novamente
    tela_retangulo(LARGURA_TELA/2 - 130 , ALTURA_TELA/2 + 100, LARGURA_TELA/2 + 130, ALTURA_TELA/2 + 150, 0, 0, vermelho);
    tela_texto(LARGURA_TELA/2, ALTURA_TELA/2 + 125, 20, branco, "Jogar novamente");
}

void desenhaHexagono(Hexagono *hexagono) {
    int i;
    ponto posHexa;
    for (i = 0; i <= num_hexa(); i++) {
        if (hexagono->bolaHexagonos[i].existe == 1) {
            posHexa = pos_hexa(i, hexagono->angulo);
            tela_circulo(posHexa.x, posHexa.y, hexagono->raioHexagono, 1, preto, hexagono->bolaHexagonos[i].cor);
        }
    }
}

void desenha(Canhao *canhao, Hexagono *hexagono, Controle *controle) {

    tela_inicia_desenho();

    if(controle->telaGameOver == 1){
        desenhaGameOver();
    }else{
        desenhaLayout(controle);
        desenhaJogo(canhao, hexagono, controle);
    }

    if (controle->helpAberto == 1)
        desenhaHelp();
    else if (controle->recordesAberto == 1){
        desenhaRecordes(controle);
    }

    desenhaRato();
    tela_termina_desenho();
}

