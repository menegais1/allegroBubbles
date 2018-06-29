
#include "helpers.h"

float absFloat(float number) {
    return number < 0 ? number * -1 : number;
}

int absInt(int number) {
    return number < 0 ? number * -1 : number;
}


void inicializaParedes(){
    paredeCima.pontoInicial.x = 10;
    paredeCima.pontoInicial.y = 100;
    paredeCima.pontoFinal.x = 670;
    paredeCima.pontoFinal.y = 100;

    paredeBaixo.pontoInicial.x = 10;
    paredeBaixo.pontoInicial.y = 640;
    paredeBaixo.pontoFinal.x = 670;
    paredeBaixo.pontoFinal.y = 640;

    paredeDireita.pontoInicial.x = 670;
    paredeDireita.pontoInicial.y = 100;
    paredeDireita.pontoFinal.x = 670;
    paredeDireita.pontoFinal.y = 640;

    paredeEsquerda.pontoInicial.x = 10;
    paredeEsquerda.pontoInicial.y = 100;
    paredeEsquerda.pontoFinal.x = 10;
    paredeEsquerda.pontoFinal.y = 640;

}
