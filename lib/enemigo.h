#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "jugador.h"
#include "estructuras.h"

void inicializar_enemigos(char mapa[MAPA_FILAS][MAPA_COLUMNAS], enemigo enemigos[], int* cantidad);
//donde se encuentra el jugador
void disparar_enemigo(enemigo* e, jugador* p, char mapa [MAPA_FILAS][MAPA_COLUMNAS]);
//colision con el mapa
void actualizar_balas_enemigo( enemigo* e, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

void daño_jugador(enemigo enemigos[], int cantidad, jugador* p);

//encontrar colision entre jugador y enemigo
bool linea_de_vision(enemigo* e, jugador* p, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

void actualizar_enemigo(enemigo* e, char mapa[MAPA_FILAS][MAPA_COLUMNAS]);

void daño_enemigo(enemigo enemigos[], int cantidad, jugador* p);
#endif
