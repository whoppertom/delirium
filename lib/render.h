#ifndef RENDER_H
#define RENDER_H
#include <allegro5/allegro.h>
#include "jugador.h"
#include "estructuras.h"
#include "mapa.h"

void render_jugador(jugador* p, texturas_sprites* sprites, bool movimiento, int sprite_actual, float angulo);
void render_balas_jugador(jugador* p, texturas_sprites* sprites);

void render_enemigo(enemigo enemigos[], int cantidad, texturas_sprites* sprites);
void render_balas_enemigo(enemigo enemigos[], int cantidad, texturas_sprites* sprites);


#endif