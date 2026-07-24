#include <allegro5/allegro.h>
#include "render.h"
#include "jugador.h"

void render_jugador(jugador* p, texturas_sprites* sprites, bool movimiento, int sprite_actual, float angulo)
{
    
    ALLEGRO_BITMAP* sprite_a_dibujar;

    if(!movimiento)
    {
        sprite_a_dibujar = sprites->sprite_personaje1;
    }
    else if(sprite_actual == 0)
    {
        sprite_a_dibujar = sprites->img_srun1;
    }
    else if(sprite_actual == 1)
    {
        sprite_a_dibujar = sprites->img_srun2;
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

void render_balas_jugador(jugador* p, texturas_sprites* sprites)
{
    float ancho_centro = al_get_bitmap_width(sprites->img_bala)/2;
    float alto_centro = al_get_bitmap_height(sprites->img_bala)/2;
    
    for(int i = 0; i < MAX_BALAS; i++)
    {
        if(p->balas[i].activa)
        {
            al_draw_rotated_bitmap(
                sprites->img_bala,
                ancho_centro, alto_centro,
                p->balas[i].posx, p->balas[i].posy,
                p->balas[i].angulo, 0
            );
        }
    }
}

//----------------ENEMIGOS----------------//

void render_enemigo(enemigo enemigos[], int cantidad, texturas_sprites* sprites)
{

    for (int i = 0; i < cantidad; i++)
    {
        if(enemigos[i].activa)
        {
            if(enemigos[i].tipo == 1)
            {
                float ancho_sprite = al_get_bitmap_width(sprites->img_enemigo1);
                float alto_sprite = al_get_bitmap_height(sprites->img_enemigo1);

                al_draw_scaled_rotated_bitmap(
                sprites->img_enemigo1,
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

            if(enemigos[i].tipo == 2)
            {
                float ancho_sprite2 = al_get_bitmap_width(sprites->img_enemigo2);
                float alto_sprite2 = al_get_bitmap_height(sprites->img_enemigo2);

                al_draw_scaled_rotated_bitmap(
                    sprites->img_enemigo2,
                    ancho_sprite2/2,
                    alto_sprite2/2,
                    enemigos[i].posx + enemigos[i].ancho/2,
                    enemigos[i].posy + enemigos[i].alto/2,
                    enemigos[i].ancho/ancho_sprite2,
                    enemigos[i].alto/alto_sprite2,
                    enemigos[i].angulo,
                    0
                );
            }

            if(enemigos[i].tipo == 3)
            {
                float ancho_sprite3 = al_get_bitmap_width(sprites->img_enemigo3);
                float alto_sprite3 = al_get_bitmap_height(sprites->img_enemigo3);
                
                al_draw_scaled_rotated_bitmap(
                    sprites->img_enemigo3,
                    ancho_sprite3/2,
                    alto_sprite3/2,
                    enemigos[i].posx + enemigos[i].ancho/2,
                    enemigos[i].posy + enemigos[i].alto/2,
                    enemigos[i].ancho/ancho_sprite3,
                    enemigos[i].alto/alto_sprite3,
                    enemigos[i].angulo,
                    0
                );
            }
        }  
    }
}

void render_balas_enemigo(enemigo enemigos[], int cantidad, texturas_sprites* sprites)
{
    float ancho_centro = al_get_bitmap_width(sprites->img_bala_e1)/2;
    float alto_centro = al_get_bitmap_height(sprites->img_bala_e1)/2;

    for (int i = 0; i < cantidad; i++)
    {
        if (enemigos[i].activa)
        {
            //---------------ENEMIGO 1---------------//

            if(enemigos[i].tipo == 1)
            {
                for(int j = 0; j < MAX_BALAS; j++)
                {
                    if(enemigos[i].balas[j].activa)
                    {
                        al_draw_rotated_bitmap(
                            sprites->img_bala_e1,
                            al_get_bitmap_width(sprites->img_bala_e1)/2,
                            al_get_bitmap_height(sprites->img_bala_e1)/2,
                            enemigos[i].balas[j].posx,
                            enemigos[i].balas[j].posy,
                            enemigos[i].balas[j].angulo,
                            0
                        );
                    }
                }
            }

            //--------------- ENEMIGO 3 -----------//

            else if(enemigos[i].tipo == 3)
            {
                for(int j = 0; j < MAX_BALAS; j++)
                {
                    if(enemigos[i].balas[j].activa)
                    {
                        al_draw_rotated_bitmap(
                            sprites->img_bala_e3,
                            al_get_bitmap_width(sprites->img_bala_e3)/2,
                            al_get_bitmap_height(sprites->img_bala_e3)/2,
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

}