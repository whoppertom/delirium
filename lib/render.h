#ifndef RENDER_H
#define RENDER_H
#include <allegro5/allegro.h>
#include "jugador.h"
#include "estructuras.h"
#include "mapa.h"

void render_jugador(jugador* p, ALLEGRO_BITMAP* sprite_idle, ALLEGRO_BITMAP* sprite_srun1, ALLEGRO_BITMAP* sprite_srun2, bool movimiento, int sprite_actual, float angulo);
void render_balas_jugador(jugador* p, ALLEGRO_BITMAP* sprite);

void render_enemigo(enemigo enemigos[], int cantidad, ALLEGRO_BITMAP* sprite);
void render_balas_enemigo(enemigo enemigos[], int cantidad, ALLEGRO_BITMAP* sprite);


#endif