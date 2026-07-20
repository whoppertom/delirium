#include <allegro5/allegro.h>
#include "render.h"
#include "jugador.h"

void render_jugador(jugador* p, ALLEGRO_BITMAP* sprite_idle, ALLEGRO_BITMAP* sprite_run1, ALLEGRO_BITMAP* sprite_run2, bool movimiento, int sprite_actual, float angulo)
{
    
    ALLEGRO_BITMAP* sprite_a_dibujar;

    if(!movimiento)
    {
        sprite_a_dibujar = sprite_idle;
    }
    else if(sprite_actual == 0)
    {
        sprite_a_dibujar = sprite_run1;
    }
    else if(sprite_actual == 1)
    {
        sprite_a_dibujar = sprite_run2;
    }
    float ancho = al_get_bitmap_width(sprite_a_dibujar);
    float alto = al_get_bitmap_height(sprite_a_dibujar);

        al_draw_scaled_rotated_bitmap(
        sprite_a_dibujar,
        ancho/2, alto/2,
        p->posx + p->size/2, p->posy + p->size/2,
        p->size/ancho, p->size/alto,
        angulo, 0
    );

}

void render_balas_jugador(jugador* p, ALLEGRO_BITMAP* sprite)
{
    float ancho_centro = al_get_bitmap_width(sprite)/2;
    float alto_centro = al_get_bitmap_height(sprite)/2;
    
    for(int i = 0; i < MAX_BALAS; i++)
    {
        if(p->balas[i].activa)
        {
            al_draw_rotated_bitmap(
                sprite,
                ancho_centro, alto_centro,
                p->balas[i].posx, p->balas[i].posy,
                p->balas[i].angulo, 0
            );
        }
    }
}

//----------------ENEMIGOS----------------//

void render_enemigo(enemigo enemigos[], int cantidad, ALLEGRO_BITMAP* sprite)
{
    float ancho_sprite = al_get_bitmap_width(sprite);
    float alto_sprite = al_get_bitmap_height(sprite);

    for (int i = 0; i < cantidad; i++)
    {
        if(enemigos[i].activa)
        {
            al_draw_scaled_rotated_bitmap(
            sprite,
            ancho_sprite / 2,
            alto_sprite / 2,
            enemigos[i].posx + enemigos[i].ancho / 2,
            enemigos[i].posy + enemigos[i].alto / 2,
            enemigos[i].ancho/ancho_sprite,
            enemigos[i].alto/alto_sprite,
            enemigos[i].angulo,
            0   
            );
        }     
    }
}

void render_balas_enemigo(enemigo enemigos[], int cantidad, ALLEGRO_BITMAP* sprite)
{
    float ancho_centro = al_get_bitmap_width(sprite)/2;
    float alto_centro = al_get_bitmap_height(sprite)/2;

    for (int i = 0; i < cantidad; i++)
    {
        if (enemigos[i].activa)
        {
            for(int j = 0; j < MAX_BALAS; j++)
            {
                if(enemigos[i].balas[j].activa)
                {
                    al_draw_rotated_bitmap(
                        sprite,
                        al_get_bitmap_width(sprite)/2,
                        al_get_bitmap_height(sprite)/2,
                        enemigos[i].balas[j].posx,
                        enemigos[i].balas[j].posy,
                        enemigos[i].balas[j].angulo,
                        0
                        );
                }
            }
        }
    }

}