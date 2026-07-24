#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "hud.h"

void dibujar_hud(jugador* p, texturas_hud* hud, int mouse_x, int mouse_y, ALLEGRO_FONT* fuente)
{
    ALLEGRO_TRANSFORM transformar_hud;
    al_identity_transform(&transformar_hud);
    al_use_transform(&transformar_hud);
                
    al_draw_bitmap(hud->img_puntero, mouse_x - 16, mouse_y -16,0);

    //-------------VIDA--------------//
    //rectangulo barra de vida
    float barra_vida_posx = 25;
    float barra_vida_posy = 40;
    float barra_vida_ancho = 500;
    float barra_vida_alto = 140;

    //dibujar fondo de barra de vida
    al_draw_filled_rectangle(100,85, 490, 125, al_map_rgb(50,50,50));
    float porcentaje_de_vida= (float)(p->vida)/(float)(p->vida_maxima);

    //dibujar porcentaje de vida
    al_draw_filled_rectangle(100,85, 100 + 390 * porcentaje_de_vida, 125, al_map_rgb(194,9,9));
    
    al_draw_scaled_bitmap(
        hud->img_barra_vida,
        0, 0,
        al_get_bitmap_width(hud->img_barra_vida),
        al_get_bitmap_height(hud->img_barra_vida),
        barra_vida_posx, barra_vida_posy,
        barra_vida_ancho, barra_vida_alto,
        0
    );

    //----------ADRENALINA---------//
    //dibujar rectangulo de la barra de adrenalina
    float barra_adren_posx = 40;
    float barra_adren_posy = 102;
    float barra_adren_ancho = 400;
    float barra_adren_alto = 80;

    //dibujar fondo de barra de adrenalina
    al_draw_filled_rectangle(100, 125, 415, 152, al_map_rgb(50,50,50));
    float porcentaje_de_adren= (float)(p->adrenalina) / (float)(p->adren_maxima);

    //dibujar porcentaje de adrenalina
    al_draw_filled_rectangle(100, 125, 100 + 315 * porcentaje_de_adren, 152, al_map_rgb(106, 19, 168));

    al_draw_scaled_bitmap(
        hud->img_barra_adren,
        0, 0,
        al_get_bitmap_width(hud->img_barra_adren),
        al_get_bitmap_height(hud->img_barra_adren),
        barra_adren_posx, barra_adren_posy,
        barra_adren_ancho, barra_adren_alto,
        0   
    );

    //----------BALA---------//
    float bala_x = 45;
    float bala_y = 920;
    float bala_ancho = 150;
    float bala_alto = 150;
    
    al_draw_scaled_bitmap(
        hud->img_bala_hud,
        0,0,
        al_get_bitmap_width(hud->img_bala_hud),
        al_get_bitmap_height(hud->img_bala_hud),
        bala_x, bala_y,
        bala_ancho, bala_alto,
        0
    );

    if(p->arma_actual.recargando)
    {
        float centro_x = al_get_bitmap_width(hud->img_recarga)/2;
        float centro_y = al_get_bitmap_height(hud->img_recarga)/2;

        float angulo = -(float) p->arma_actual.tiempo_recarga_actual / p->arma_actual.tiempo_recarga_total * (2*ALLEGRO_PI);

        float size = 1.5;
        float posx = bala_x + bala_ancho;
        float posy = bala_y + 75;

        al_draw_scaled_rotated_bitmap(
            hud->img_recarga,
            centro_x, centro_y,
            posx, posy,
            size, size,
            angulo,
            0
        );
    }
    else 
    {
        al_draw_textf(fuente, al_map_rgb(255, 255, 255), bala_x + bala_ancho - 20, bala_y + 80, ALLEGRO_ALIGN_LEFT, "%d / %d", p->arma_actual.municion, p->arma_actual.reserva);
    }
}
