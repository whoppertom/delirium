#ifndef JUGADOR_H
#define JUGADOR_H
#include "estructuras.h"
#include "definiciones.h"
#include <stdbool.h>


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
}jugador; //pepe

void actualizar_jugador(jugador*p,bool teclas[KEYS],char mapa[MAPA_FILAS][MAPA_COLUMNAS]);
bool hay_colision(jugador *p, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);
void disparar_jugador(jugador* p, float angulo, float cam_x, float cam_y, int mouse_x, int mouse_y);
void actualizar_balas_jugador(jugador* p, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

#endif