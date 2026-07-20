#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "hud.h"

void dibujar_hud(jugador* p, ALLEGRO_BITMAP* img_puntero, ALLEGRO_BITMAP* img_barra_vida, ALLEGRO_BITMAP* img_barra_adren, int mouse_x, int mouse_y)
{
    ALLEGRO_TRANSFORM transformar_hud;
    al_identity_transform(&transformar_hud);
    al_use_transform(&transformar_hud);
                
    al_draw_bitmap(img_puntero, mouse_x - 16, mouse_y -16,0);

    //dibujar rectangulo barra de vida
    float barra_vida_posx = 25;
    float barra_vida_posy = 40;
    float barra_vida_ancho = 500;
    float barra_vida_alto = 140;

    //dibujar rectangulo de la barra de adrenalina
    float barra_adren_posx = 40;
    float barra_adren_posy = 102;
    float barra_adren_ancho = 400;
    float barra_adren_alto = 80;

    //dibujar fondo de barra de vida
    al_draw_filled_rectangle(100,85, 490, 125, al_map_rgb(50,50,50));

    float porcentaje_de_vida= (float)(p->vida)/(float)(p->vida_maxima);

    //dibujar porcentaje de vida
    al_draw_filled_rectangle(100,85, 100 + 390 * porcentaje_de_vida, 125, al_map_rgb(194,9,9));

    //dibujar fondo de barra de adrenalina
    al_draw_filled_rectangle(100, 125, 415, 152, al_map_rgb(50,50,50));

    float porcentaje_de_adren= (float)(p->adrenalina) / (float)(p->adren_maxima);

    //dibujar porcentaje de adrenalina
    al_draw_filled_rectangle(100, 125, 100 + 315 * porcentaje_de_adren, 152, al_map_rgb(106, 19, 168));

    al_draw_scaled_bitmap(
    img_barra_vida,
    0, 0,
    al_get_bitmap_width(img_barra_vida),
    al_get_bitmap_height(img_barra_vida),
    barra_vida_posx, barra_vida_posy,
    barra_vida_ancho, barra_vida_alto,
    0
    );
    al_draw_scaled_bitmap(
    img_barra_adren,
    0, 0,
    al_get_bitmap_width(img_barra_adren),
    al_get_bitmap_height(img_barra_adren),
    barra_adren_posx, barra_adren_posy,
    barra_adren_ancho, barra_adren_alto,
    0   
    );
    
}
