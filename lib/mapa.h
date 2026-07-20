#ifndef MAPA_H
#define MAPA_H
#include <allegro5/allegro.h>
#include "estructuras.h"

void inicializar_mapa(char mapa[MAPA_FILAS][MAPA_COLUMNAS], const char* ruta);

void dibujar_mapa(char mapa[MAPA_FILAS][MAPA_COLUMNAS], texturas_mapa* texturas);

bool colision(char celda); 


#endif