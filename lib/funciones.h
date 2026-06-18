#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <allegro5/allegro.h>
#include "estructuras.h"


void inicializar_mapa(int mapa[MAPA_FILAS][MAPA_COLUMNAS]);
void dibujar_mapa(int mapa[MAPA_FILAS][MAPA_COLUMNAS], ALLEGRO_BITMAP* img_piso, ALLEGRO_BITMAP* img_pared,ALLEGRO_BITMAP* img_pared_izq);
void actualizar_jugador(jugador*p,bool teclas[KEYS],int mapa[MAPA_FILAS][MAPA_COLUMNAS]);

bool colision(int celda); 
bool hay_colision(jugador *p, int mapa[MAPA_FILAS][MAPA_COLUMNAS]);

#endif