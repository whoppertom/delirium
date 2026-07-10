#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "estructuras.h"

void inicializar_enemigos(char mapa[MAPA_FILAS][MAPA_COLUMNAS], enemigo enemigos[], int* cantidad);
//donde se encuentra el jugador
void disparar_enemigo(enemigo* e, jugador* p);
//colision con el mapa
void actualizar_balas_enemigo( enemigo* e, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

void daño_jugador(enemigo enemigos[], int cantidad, jugador* p);
#endif
