#include <stdio.h>

#include "tela.h"
#include "hexagono.h"
#include "controle.h"
#include "desenha.h"

#include "canhao.h"
#include "bola.h"
#include "helpers.h"


//ARRUMAR OS DEFINES
int cliqueDoMouse(int x, int y, Controle *controle) {
    int lugarDoClique = NENHUM;


    if (controle->telaGameOver == 1) {
        if (y >= 355 && y <= 405 && x >= 210 && x <= 330) {
            lugarDoClique = RECORDE;
        } else if (y >= 355 && y <= 405 && x >= 350 && x <= 470) {
            lugarDoClique = SAIR;
        } else if (y >= 425 && y <= 475 && x >= 210 && x <= 470) {
            lugarDoClique = JOGAR_NOVAMENTE;
            controle->telaGameOver = 0;
        }
    } else {
        if (y >= 5 && y <= 25 && x >= 625 && x <= 675) {
            lugarDoClique = SAIR;
        } else if (y >= 45 && y <= 75 && x >= 550 && x <= 630) {
            lugarDoClique = HELP;
        } else if (y >= 45 && y <= 75 && x >= 420 && x <= 540) {
            lugarDoClique = RECORDE;
        } else if (y > 100) {
            lugarDoClique = CANHAO;
        }
    }

    return lugarDoClique;
}


int atualiza(Controle *controle, Hexagono *hexagono, Canhao *canhao) {
    int xClique, yClique, clique, i, pontuacaoAntiga;
    while (1) {
        if (checaColisaoParedeHexagono(hexagono) == 1) {
            controle->telaGameOver = 1;
            atribuiRecordes(controle);
        }

        if (canhao->disparado) {
            atualizaBola(&canhao->bolaAtual, hexagono);
            switch (canhao->bolaAtual.estado) {
                case DISPARADA:
                    moveBola(&canhao->bolaAtual);
                    break;
                case DESTRUIDA:
                    canhao->disparado = 0;
                    atualizaCanhao(canhao, hexagono);
                    controle->pontuacao -= 3;
                    break;
                case INCORPORADA:
                    canhao->disparado = 0;
                    inicializaGiro(canhao->bolaAtual.posicao, canhao->bolaAtual.direcao, hexagono);
                    pontuacaoAntiga=controle->pontuacao;
                    controle->pontuacao += incorporaBolaHexagono(canhao->bolaAtual.posicao, canhao->bolaAtual.cor,
                                                                 hexagono);
                    for (i = 0; i < 6; i++) {
                        if (hexagono->corBolinhas[i].cor == canhao->bolaAtual.cor) {
                            hexagono->corBolinhas[i].numBolinhas++;
                            break;
                        }
                    }
                    if (somaDasBolas(hexagono) <= 0) {
                        controle->pontuacao = controle->pontuacao + 10 * controle->faseAtual;
                        controle->faseAtual++;
                        return 0;
                    }
                    atualizaCanhao(canhao, hexagono);

                    if(controle->pontuacao<=pontuacaoAntiga){
                        controle->rodadasRestantesParaAdicionar--;
                    }

                    break;
            }
        }
        if(controle->rodadasRestantesParaAdicionar == 0){
            adicionaBolas(hexagono, controle);
            controle->rodadasRestantesParaAdicionar = RODADAS_TOTAIS_PARA_ADICIONAR - controle->faseAtual;
        }

        if (hexagono->girando == 1) {
            giraHexagono(hexagono);
        }


        if (tela_rato_clicado() == 1) {
            xClique = tela_rato_x_clique();
            yClique = tela_rato_y_clique();
            clique = cliqueDoMouse(xClique, yClique, controle);

            canhao->direcao.x = xClique - X_CANHAO;
            canhao->direcao.y = yClique - Y_CANHAO;
            if (controle->helpAberto == 1) {
                controle->helpAberto = 0;
            } else if (controle->recordesAberto == 1) {
                controle->recordesAberto = 0;
            } else {
                switch (clique) {
                    case SAIR:
                        atribuiRecordes(controle);
                        return 1;
                        break;
                    case HELP:
                        controle->helpAberto = 1;
                        break;
                    case RECORDE:
                        controle->recordesAberto = 1;
                        break;
                    case CANHAO:
                        if (canhao->disparado == 0)
                            disparaCanhao(canhao);
                        break;
                    case JOGAR_NOVAMENTE:
                        controle->faseAtual=0;
                        controle->pontuacao=0;
                        return 0;
                    default:
                        break;

                }
            }
        }


        desenha(canhao, hexagono, controle);
    }

    return 1;
}
void adicionaBolas(Hexagono *hexagono, Controle *controle){
    int j, k, numVizinhos[6], existeVizinho, cor, aux;
    printf("\n\n");
    for(int i=0;i<BOLAS_ADICIONADAS + controle->faseAtual; i++){
        existeVizinho=0, cor = -1;
        while(existeVizinho == 0){
            j = rand() % num_hexa();
            if(hexagono->bolaHexagonos[j].existe == 0){
                for(k=0; k<6; k++){
                    numVizinhos[k] = vizinho(j,k);
                    if(numVizinhos[k] != -1){
                        if(hexagono->bolaHexagonos[numVizinhos[k]].existe == 1){
                            existeVizinho=1;
                        }
                    }
                }
            }
        }
        hexagono->bolaHexagonos[j].existe = 1;
        while(cor == -1){
            aux = rand() % 6;
            if(hexagono->corBolinhas[aux].numBolinhas>0){
                cor = aux;
            }
        }

        hexagono->corBolinhas[cor].numBolinhas++;
        hexagono->bolaHexagonos[j].cor = hexagono->corBolinhas[cor].cor;
    }
}

void atribuiRecordes(Controle *controle){
    int i, j;
    if(controle->recordeGravado == 0){
        for(i=0;i<TOTAL_RECORDES;i++){
            if(controle->pontuacao > controle->recordes[i].pontuacao){
                for(j=i;j<TOTAL_RECORDES - 1;j++){
                    controle->recordes[i+1].pontuacao = controle->recordes[i].pontuacao;
                }
                controle->recordes[i].pontuacao = controle->pontuacao;
                controle->recordeGravado=1;
                break;

            }
        }

    }

}


void inicializaRecordes(Controle *controle){
    int i=0;
    for(i=0;i<TOTAL_RECORDES;i++){
        controle->recordes[i].pontuacao=0;
    }

}

int lerArquivo(Controle *controle){

    FILE* arquivo;

    arquivo = fopen("Recordes.bin","rb");

    if(arquivo == NULL){
        return 0;
    }
    fread(controle->recordes,sizeof(Recorde),TOTAL_RECORDES,arquivo);

    fclose(arquivo);

    return 1;
}

int escreveArquivo(Controle *controle){

    FILE* arquivo;

    arquivo = fopen("Recordes.bin","wb");
    if(arquivo == NULL){
        printf("N�o foi Possivel Carregar o arquivo do disco, as informacoes nao serao salvas");
        return 0;
    }

    fwrite(controle->recordes,sizeof(Recorde),TOTAL_RECORDES,arquivo);
    fclose(arquivo);


    return 1;


}
