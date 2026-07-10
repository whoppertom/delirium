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
typedef struct{
    float posx;
    float posy;
    float vel_x;
    float vel_y;
    float angulo;
    bool activa;
}bala;

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
    bala balas[MAX_BALAS];
    int cooldown_disparo;
}jugador;

typedef struct {
    float posx;
    float posy;
    float ancho;
    float alto;
    bool activa;
    bala balas[MAX_BALAS];
    int cooldown_disparo;
}enemigo;

typedef enum {
    MENU, // 0
    JUEGO, // 1 
} estado_juego;




#endif 