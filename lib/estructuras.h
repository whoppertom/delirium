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
    int adrenalina;
    int adren_maxima;
    int vida;
    int vida_maxima;
}jugador;

typedef enum {
    MENU, // 0
    JUEGO, // 1 
} estado_juego;


#endif 