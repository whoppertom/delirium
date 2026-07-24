#ifndef HUD_H
#define HUD_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "jugador.h"

void dibujar_hud(jugador* p, texturas_hud* hud, int mouse_x, int mouse_y, ALLEGRO_FONT* fuente);

#endif