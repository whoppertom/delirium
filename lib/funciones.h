#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <allegro5/allegro.h>
#include "estructuras.h"


void inicializar_mapa(char mapa[MAPA_FILAS][MAPA_COLUMNAS], const char* ruta);
void dibujar_mapa(char mapa[MAPA_FILAS][MAPA_COLUMNAS], ALLEGRO_BITMAP* img_piso, ALLEGRO_BITMAP* img_pared,ALLEGRO_BITMAP* img_pared_izq, ALLEGRO_BITMAP* img_adrenalina, ALLEGRO_BITMAP* img_pared_interior);
void actualizar_jugador(jugador*p,bool teclas[KEYS],char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

bool colision(char celda); 
bool hay_colision(jugador *p, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

#endif