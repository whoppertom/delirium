#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <allegro5/allegro.h>
#include "estructuras.h"


void inicializar_mapa(int mapa[MAPA_FILAS][MAPA_COLUMNAS]);
void dibujar_mapa(int mapa[MAPA_FILAS][MAPA_COLUMNAS], ALLEGRO_BITMAP* img_piso, ALLEGRO_BITMAP* img_pared);
void actualizar_jugador(jugador*p,bool teclas[4],int mapa[MAPA_FILAS][MAPA_COLUMNAS]);

#endif  