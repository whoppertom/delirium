#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include "definiciones.h"


enum TECLAS 
{
    KEY_W,
    KEY_S,
    KEY_A,
    KEY_D
};

typedef struct {
    float posx;
    float posy;
    float velocidad;
    float size;
    int frame_actual;
    int vida;
    int vida_maxima;
}jugador;


#endif 