#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "mapa.h"
#include "estructuras.h"
#include "enemigo.h"
#include "jugador.h"
#include "hud.h"
#include "render.h"
#include "init.h"




int main()
{
    if(!inicializar_allegro())
    {
        return -1;
    }
    ALLEGRO_DISPLAY* ventana = al_create_display(pantalla_ancho, pantalla_alto );
    if (!ventana) {fprintf(stderr, "no se pudo crear la ventana");return -1;}

    
    ALLEGRO_FONT* fuente = al_create_builtin_font();

    //CARGAR TEXTURAS
    texturas_mapa texturas_del_juego;
    cargar_texturas_mapa(&texturas_del_juego);
    // CARGAR SPRITES
    texturas_sprites los_sprites;
    cargar_texturas_sprites(&los_sprites);
    //CARGAR HUD
    texturas_hud hud;
    cargar_texturas_hud(&hud);

  

    ALLEGRO_TIMER* temporizador = al_create_timer(1.0 / FPS);
    ALLEGRO_EVENT_QUEUE* cola_eventos = al_create_event_queue();

    // cambiar titulo de la ventana
    al_set_window_title(ventana, "DELIRIUM");

    int borde_ancho_pantalla=al_get_display_width(ventana);
    int borde_alto_pantalla=al_get_display_height(ventana);


    al_register_event_source(cola_eventos, al_get_display_event_source(ventana));
    al_register_event_source(cola_eventos, al_get_keyboard_event_source());
    al_register_event_source(cola_eventos, al_get_mouse_event_source());
    al_register_event_source(cola_eventos, al_get_timer_event_source(temporizador));

    srand(time(NULL));
    estado_juego estado = MENU;

    //---------jugador--------//
    jugador pepe = {0, 0, INICIO_VELOCIDAD, INICIO_SIZE, 0, 100, 100, 100, 100, {0}, 0};
    int mouse_x = 0;
    int mouse_y = 0;
    float cam_x = 0;
    float cam_y = 0;
    int frame_animacion = 0;
    int sprite_actual = 0; // 0 = run1 ; 1 = run2
    bool movimiento = false;
    bool teclas[KEYS] = {false};

    //------------balas------------//
    float angulo_personaje = 0;
    //------------------------//


    //------------mapa------------//
    char mapa[MAPA_FILAS][MAPA_COLUMNAS];
    inicializar_mapa(mapa, "assets/mapas/nivelprueba.txt");
    spawn(&pepe, mapa);

    //------------enemigo1------------//
    enemigo enemigos[MAX_ENEMIGOS];
    int cantidad_enemigos = 0;
    inicializar_enemigos(mapa, enemigos, &cantidad_enemigos);


    al_start_timer(temporizador);
    bool ejecutar=true;
    bool redibujar=true;

    while(ejecutar) 
    {
        ALLEGRO_EVENT evento;
        //espera a que ocurra un evento
        al_wait_for_event(cola_eventos, &evento); 

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            ejecutar = false;
        }

        //--------teclado----------//
        else if(evento.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (evento.keyboard.keycode)
            {
                case ALLEGRO_KEY_W:
                    teclas[KEY_W] = true;
                    break;
                case ALLEGRO_KEY_S:
                    teclas[KEY_S] = true;
                    break;
                case ALLEGRO_KEY_A:
                    teclas[KEY_A] = true;
                    break;
                case ALLEGRO_KEY_D:
                    teclas[KEY_D] = true;
                    break;
                case ALLEGRO_KEY_R:
                    teclas[KEY_R] = true;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    ejecutar = false;
                    break;
            }
        }
        else if(evento.type == ALLEGRO_EVENT_KEY_UP)
        {
            switch(evento.keyboard.keycode)
            {
                case ALLEGRO_KEY_W:
                    teclas[KEY_W] = false;
                    break;
                case ALLEGRO_KEY_S:
                    teclas[KEY_S] = false;
                    break;
                case ALLEGRO_KEY_A:
                    teclas[KEY_A] = false;
                    break;
                case ALLEGRO_KEY_D:
                    teclas[KEY_D] = false;
                    break;
                case ALLEGRO_KEY_R:
                    teclas[KEY_R] = false;
                    break;
            }
        }

        //-------------MOUSE-------------//
        else if (evento.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            mouse_x = evento.mouse.x;
            mouse_y = evento.mouse.y;
        }


        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {

            if (estado == MENU)
            {
                
                int pos_mousex = evento.mouse.x;
                int pos_mousey = evento.mouse.y;

                if (pos_mousex >= 760 && pos_mousex <= 1160 && pos_mousey >= 450 && pos_mousey <= 530)
                {
                    estado = JUEGO;
                    al_hide_mouse_cursor(ventana);
                }
                
                if (pos_mousex >= 760 && pos_mousex <= 1160 && pos_mousey >= 570 && pos_mousey <= 650)
                {
                    ejecutar = false;
                }

            }

            else if(estado == JUEGO)
            {
                if(evento.mouse.button == 1 && pepe.cooldown_disparo == 0)
                {
                    disparar_jugador(&pepe, angulo_personaje, cam_x, cam_y, mouse_x, mouse_y);
                }
            }
            
        }

        //----------TIMER----------//
        else if(evento.type == ALLEGRO_EVENT_TIMER)
        {
            if (estado == JUEGO)
            {
                if (pepe.vida > 0)
                {
                    actualizar_jugador(&pepe, teclas, mapa);
                }

                for(int i = 0; i < cantidad_enemigos; i++)
                {
                    if(enemigos[i].activa)
                    {
                        actualizar_enemigo(&enemigos[i], mapa, &pepe);
                        disparar_enemigo(&enemigos[i], &pepe, mapa);
                        actualizar_balas_enemigo(&enemigos[i], mapa);
                    }
                }

                daño_jugador(enemigos, cantidad_enemigos, &pepe);
                daño_enemigo(enemigos, cantidad_enemigos, &pepe);

                if (pepe.cooldown_disparo > 0) {pepe.cooldown_disparo--;}

                //bordes
                if(pepe.posx < 0){pepe.posx = 0;}
                if(pepe.posy < 0){pepe.posy = 0;}
                if(pepe.posx > (MAPA_COLUMNAS* TILE_SIZE) - pepe.size){pepe.posx = (MAPA_COLUMNAS * TILE_SIZE) - pepe.size;}
                if(pepe.posy > (MAPA_FILAS * TILE_SIZE) - pepe.size){pepe.posy = (MAPA_FILAS * TILE_SIZE) - pepe.size;}

                actualizar_balas_jugador(&pepe, mapa); 
                
                //----------------SCROLL---------------//
                cam_x = (pepe.posx + pepe.size/2) - pantalla_ancho/2;
                cam_y = (pepe.posy + pepe.size/2) - pantalla_alto/2;
                
                float max_cam_x = (MAPA_COLUMNAS * TILE_SIZE) - pantalla_ancho;
                float max_cam_y = (MAPA_FILAS * TILE_SIZE) - pantalla_alto;
                
                if (cam_x < 0) cam_x = 0;
                if (cam_y < 0) cam_y = 0;
                if (cam_x > max_cam_x) cam_x = max_cam_x;
                if (cam_y > max_cam_y) cam_y = max_cam_y;


                float mouse_mundo_x = mouse_x + cam_x;
                float mouse_mundo_y = mouse_y + cam_y;

                float centro_x = pepe.posx + pepe.size/ 2;
                float centro_y = pepe.posy + pepe.size/2;
                angulo_personaje = atan2(mouse_mundo_y - centro_y, mouse_mundo_x - centro_x) ;
                
                //no resetea en cada frame
                static int contador_adren = 0;
                contador_adren++;
                if(contador_adren >=8)
                {
                    contador_adren = 0;
                    if(pepe.adrenalina > 0)
                    {
                        pepe.adrenalina--;
                    }
                }

                int centro_fila_jug = (pepe.posy + pepe.size /2) / TILE_SIZE;
                int centro_columna_jug = (pepe.posx + pepe.size /2) / TILE_SIZE;

                if(mapa[centro_fila_jug][centro_columna_jug] == 'A')
                {
                    pepe.adrenalina += 16;
                    if(pepe.adrenalina > pepe.adren_maxima)
                    {
                        pepe.adrenalina = pepe.adren_maxima;
                    }
                    mapa[centro_fila_jug][centro_columna_jug] = '.';
                }

                //----------CAMBIO DE NIVEL-----------//
                else if(mapa[centro_fila_jug][centro_columna_jug] == 'F')
                {
                    inicializar_mapa(mapa, "assets/mapas/nivel_2.txt");
                    int i;
                    for(i = 0; i < MAX_BALAS; i++)
                    {
                        pepe.balas[i].activa = false;
                    }

                    cantidad_enemigos = 0;
                    inicializar_enemigos(mapa, enemigos, &cantidad_enemigos);
                    spawn(&pepe,mapa);
                }

                //------------ANIMACION JUGADOR-----------//
                movimiento = teclas[KEY_W] || teclas[KEY_S] || teclas[KEY_A] || teclas[KEY_D];
                if (movimiento)
                {
                    frame_animacion++;
                    if (frame_animacion >= 20 ) //cada 15 frames cambia de sprite
                    {
                        frame_animacion = 0;
                        sprite_actual = 1 - sprite_actual;
                    }
                }
            }
        redibujar=true;
        }
   

        //----------------DIBUJAR----------------//

        if (redibujar && al_is_event_queue_empty(cola_eventos))
        {

            redibujar=false;
            al_clear_to_color(al_map_rgb(120,110,110));


            if (estado == MENU)
            {
                //titulo
                al_draw_bitmap(hud.img_titulo,545,90,0);

                //boton jugar
                al_draw_filled_rectangle(760,450,1160,530, al_map_rgb(255,255,255));
                al_draw_text(fuente, al_map_rgb(0,0,0), 960,482, ALLEGRO_ALIGN_CENTRE, "JUGAR");

                //boton salir
                al_draw_filled_rectangle(760,570,1160,650, al_map_rgb(255,255,255));
                al_draw_text(fuente, al_map_rgb(0,0,0), 960, 602, ALLEGRO_ALIGN_CENTRE, "SALIR");

            }

            else if (estado == JUEGO)
            {

                ALLEGRO_TRANSFORM camara_transform;
                al_identity_transform(&camara_transform);
                al_translate_transform(&camara_transform, -cam_x, -cam_y);
                al_use_transform(&camara_transform);


                dibujar_mapa(mapa, &texturas_del_juego);

                
                render_jugador(&pepe, &los_sprites, movimiento, sprite_actual, angulo_personaje);
                render_balas_jugador(&pepe, &los_sprites);

                render_enemigo(enemigos, cantidad_enemigos, &los_sprites);
                render_balas_enemigo(enemigos, cantidad_enemigos, &los_sprites);

            
                dibujar_hud(&pepe, &hud, mouse_x, mouse_y, fuente);

            }


            al_flip_display();
        }
    }

    // Limpieza de recursos

    //texturas mapa
    al_destroy_bitmap(texturas_del_juego.img_piso);
    al_destroy_bitmap(texturas_del_juego.img_pared);
    al_destroy_bitmap(texturas_del_juego.img_pared_izq);
    al_destroy_bitmap(texturas_del_juego.img_adrenalina);
    al_destroy_bitmap(texturas_del_juego.img_pared_interior);
    al_destroy_bitmap(texturas_del_juego.img_esquina_sup_izq);
    al_destroy_bitmap(texturas_del_juego.img_esquina_sup_der);
    al_destroy_bitmap(texturas_del_juego.img_pared_der);

    al_destroy_bitmap(los_sprites.sprite_personaje1);
    al_destroy_bitmap(los_sprites.img_srun1);
    al_destroy_bitmap(los_sprites.img_srun2);
    al_destroy_bitmap(los_sprites.img_bala);
    al_destroy_bitmap(los_sprites.img_enemigo1);
    al_destroy_bitmap(los_sprites.img_bala_e1);
    al_destroy_bitmap(los_sprites.img_adrenalina);

    al_destroy_bitmap(hud.img_puntero);
    al_destroy_bitmap(hud.img_barra_vida);
    al_destroy_bitmap(hud.img_barra_adren);
    al_destroy_bitmap(hud.img_titulo);

    al_destroy_event_queue(cola_eventos);
    al_destroy_display(ventana);
    al_destroy_timer(temporizador);

    
    return 0;
}
