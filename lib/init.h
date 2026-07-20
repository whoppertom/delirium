#ifndef INIT_H
#define INIT_H

#include <allegro5/allegro.h>
#include <stdbool.h>
#include "estructuras.h"

bool inicializar_allegro();
void cargar_texturas_mapa(texturas_mapa* texturas);
void destruir_texturas(texturas_mapa* texturas);

#endif