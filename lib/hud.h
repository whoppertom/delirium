#ifndef HUD_H
#define HUD_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "jugador.h"

void dibujar_hud(jugador* p, ALLEGRO_BITMAP* img_puntero, ALLEGRO_BITMAP* img_barra_vida, ALLEGRO_BITMAP* img_barra_adren, int mouse_x, int mouse_y);

#endif