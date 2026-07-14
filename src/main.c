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
#include "funciones.h"
#include "estructuras.h"
#include "enemigo.h"




int main()
{

    if (!al_init()) {fprintf(stderr, "no se pudo inicializar allegro");return -1;}

    if (!al_init_image_addon()) {fprintf(stderr, "no se pudo inicializar imagenes");return -1;}

    if (!al_init_font_addon()) {fprintf(stderr, "no se pudo inicializar fuentes");return -1;}

    if (!al_init_ttf_addon()) {fprintf(stderr, "no se pudo inicializar ttf");return -1;}

    if (!al_install_keyboard()) {fprintf(stderr, "no se detecto el teclado");return -1;}

    if(!al_install_mouse()) {fprintf(stderr, "no se detecto el mouse");return -1;}

    if (!al_init_primitives_addon()) {fprintf(stderr, "no se pudo inicializar primitivas");return -1;}


    ALLEGRO_DISPLAY* ventana = al_create_display(pantalla_ancho, pantalla_alto );
    if (!ventana) {fprintf(stderr, "no se pudo crear la ventana");return -1;}

    ALLEGRO_FONT* fuente = al_create_builtin_font();

    // CARGAR SPRITES
    ALLEGRO_BITMAP* sprite_personaje1 = al_load_bitmap("sprites/sprite1.png");
    ALLEGRO_BITMAP* img_piso = al_load_bitmap("sprites/piso.png");
    ALLEGRO_BITMAP* img_pared = al_load_bitmap("sprites/pared.png");
    ALLEGRO_BITMAP* img_pared_izq = al_load_bitmap("sprites/pared_izq.png");
    ALLEGRO_BITMAP* img_barra_vida = al_load_bitmap("sprites/barra_vida.png");
    ALLEGRO_BITMAP* img_barra_adren = al_load_bitmap("sprites/barra_adrenalina.png");
    ALLEGRO_BITMAP* img_adrenalina = al_load_bitmap("sprites/adrenalina.png");
    ALLEGRO_BITMAP* img_titulo = al_load_bitmap("sprites/titulo.png");
    ALLEGRO_BITMAP* img_puntero = al_load_bitmap("sprites/puntero.png");
    ALLEGRO_BITMAP* img_bala = al_load_bitmap("sprites/bala.png");
    ALLEGRO_BITMAP* img_srun1 = al_load_bitmap("sprites/sprite1_run.png");
    ALLEGRO_BITMAP* img_srun2 = al_load_bitmap("sprites/sprite1_run2.png"); 
    ALLEGRO_BITMAP* img_enemigo1 = al_load_bitmap("sprites/enemigo1.png");
    ALLEGRO_BITMAP* img_bala_e1 = al_load_bitmap("sprites/bala_enemigo1.png");



    ALLEGRO_TIMER* temporizador = al_create_timer(1.0 / FPS);
    if (!temporizador) {fprintf(stderr, "no se pudo crear el temporizador");return -1;}

    ALLEGRO_EVENT_QUEUE* cola_eventos = al_create_event_queue();
    if (!cola_eventos) {fprintf(stderr, "no se pudo crear la cola de eventos");return -1;}

    // cambiar titulo de la ventana
    al_set_window_title(ventana, "DELIRIUM");

    int borde_ancho_pantalla=al_get_display_width(ventana);
    int borde_alto_pantalla=al_get_display_height(ventana);


    
    al_register_event_source(cola_eventos, al_get_display_event_source(ventana));
    al_register_event_source(cola_eventos, al_get_keyboard_event_source());
    al_register_event_source(cola_eventos, al_get_mouse_event_source());
    al_register_event_source(cola_eventos, al_get_timer_event_source(temporizador));

    srand(time(NULL));
    jugador pepe = {INICIO_POSX, INICIO_POSY, INICIO_VELOCIDAD, INICIO_SIZE, 0, 100, 100, 100, 100, {0}, 0};
    estado_juego estado = MENU;

    int mouse_x = 0;
    int mouse_y = 0;
     //------------balas------------//
    float angulo_personaje = 0;
    //------------------------//

    
    al_start_timer(temporizador);

    bool teclas[KEYS] = {false};
    bool ejecutar=true;
    bool redibujar=true;

    //------------mapa------------//
    char mapa[MAPA_FILAS][MAPA_COLUMNAS];
    inicializar_mapa(mapa);

    //------------enemigo1------------//
    enemigo enemigos[MAX_ENEMIGOS];
    int cantidad_enemigos = 0;
    inicializar_enemigos(mapa, enemigos, &cantidad_enemigos);



    int frame_animacion = 0;
    int sprite_actual = 0; // 0 = run1 ; 1 = run2
    bool movimiento = false;

    while(ejecutar) 
    {
        ALLEGRO_EVENT evento;
        //espera a que ocurra un evento
        al_wait_for_event(cola_eventos, &evento); 
        // cerrar la ventana exitosamente
        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            ejecutar = false;
        }
        //revisa si la tecla fue presionada en el teclado
        else if(evento.type==ALLEGRO_EVENT_KEY_DOWN)
        {
            //revisa que tecla fue presionada
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
                case ALLEGRO_KEY_ESCAPE:
                    ejecutar = false;
                    break;
            }
        }
        //revisa si la tecla fue soltada en el teclado
        else if(evento.type == ALLEGRO_EVENT_KEY_UP)
        {
            //revisa que tecla fue soltada
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
            }
        }
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
                    //---------disparar---------//
                    for (int i = 0; i < MAX_BALAS; i ++)
                    {
                        if (!pepe.balas[i].activa)
                        {
                        float centro_x = pepe.posx + pepe.size/2;
                        float centro_y = pepe.posy + pepe.size/2;

                        float distancia_pistola = 40;
                        float pistola_x = centro_x + distancia_pistola * cos(angulo_personaje);
                        float pistola_y = centro_y + distancia_pistola * sin(angulo_personaje);

                        float direccionx = mouse_x - pistola_x;
                        float direcciony = mouse_y - pistola_y;

                        float distancia_mouse = sqrt(direccionx*direccionx + direcciony*direcciony);
                        float velocidad_bala = 30;

                    
                        pepe.balas[i].posx = pistola_x;
                        pepe.balas[i].posy = pistola_y;
                        pepe.balas[i].vel_x = (direccionx/ distancia_mouse)* velocidad_bala;
                        pepe.balas[i].vel_y = (direcciony/ distancia_mouse)* velocidad_bala;
                        pepe.balas[i].angulo = atan2(direcciony, direccionx);
                        pepe.balas[i].activa = true; 
                        pepe.balas[i].daño = 25;
                        pepe.cooldown_disparo = 20; //frames a esperar para el prox disparo
                        break;

                        }
                    }
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
                        actualizar_enemigo(&enemigos[i], mapa);
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
                if(pepe.posx > borde_ancho_pantalla - pepe.size){pepe.posx = borde_ancho_pantalla - pepe.size;}
                if(pepe.posy > borde_alto_pantalla - pepe.size){pepe.posy = borde_alto_pantalla - pepe.size;}

                for (int i = 0; i < MAX_BALAS; i++)
                {
                    if (pepe.balas[i].activa)
                    {
                        pepe.balas[i].posx += pepe.balas[i].vel_x;
                        pepe.balas[i].posy += pepe.balas[i].vel_y;

                        if (pepe.balas[i].posx < 0 || pepe.balas[i].posx > pantalla_ancho || pepe.balas[i].posy < 0 || pepe.balas[i].posy > pantalla_alto)
                        {
                            pepe.balas[i].activa = false;
                            continue;
                        }
                        int fila = (pepe.balas[i].posy / TILE_SIZE);
                        int col = (pepe.balas[i].posx / TILE_SIZE);
                        if (colision(mapa[fila][col]))
                        {
                            pepe.balas[i].activa = false;
                        }
                    }
                }

                float centro_x = pepe.posx + pepe.size/ 2;
                float centro_y = pepe.posy + pepe.size/2;
                angulo_personaje = atan2(mouse_y - centro_y, mouse_x - centro_x) ;
                
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

                movimiento = teclas[KEY_W] || teclas[KEY_S] || teclas[KEY_A] || teclas[KEY_D];
                if (movimiento){
                    frame_animacion++;
                    if (frame_animacion >= 15 ) //cada 15frames cambia de sprite
                    {
                        frame_animacion = 0;
                        sprite_actual = 1 - sprite_actual;
                    }
                }
                else {
                    frame_animacion = 0;
                    sprite_actual = 0;
                }

                redibujar=true;
            }
        }
        //-------------------//

        //----------------DIBUJAR----------------//

        if (redibujar && al_is_event_queue_empty(cola_eventos))
        {

            redibujar=false;
            al_clear_to_color(al_map_rgb(120,110,110));


            if (estado == MENU)
            {
                al_draw_bitmap(img_titulo,545,90,0);
                //boton inicio
                al_draw_filled_rectangle(760,450,1160,530, al_map_rgb(255,255,255));
                al_draw_text(fuente, al_map_rgb(0,0,0), 960,482, ALLEGRO_ALIGN_CENTRE, "JUGAR");

                //boton salir
                al_draw_filled_rectangle(760,570,1160,650, al_map_rgb(255,255,255));
                al_draw_text(fuente, al_map_rgb(0,0,0), 960, 602, ALLEGRO_ALIGN_CENTRE, "SALIR");
            }

            else if (estado == JUEGO)
            {
                dibujar_mapa(mapa, img_piso, img_pared,img_pared_izq, img_adrenalina);
                al_draw_bitmap(img_puntero, mouse_x - 16, mouse_y -16,0);
                
                ALLEGRO_BITMAP* sprite_a_dibujar;
                if(!movimiento)
                {
                    sprite_a_dibujar = sprite_personaje1;
                }
                else if(sprite_actual == 0)
                {
                    sprite_a_dibujar = img_srun1;
                }
                else if(sprite_actual == 1)
                {
                    sprite_a_dibujar = img_srun2;
                }
                //dibujar jugador
                float ancho = al_get_bitmap_width(sprite_a_dibujar);
                float alto = al_get_bitmap_height(sprite_a_dibujar);

                //dibujar jugador
                al_draw_scaled_rotated_bitmap(
                    sprite_a_dibujar,
                    ancho / 2,   
                    alto / 2,    
                    pepe.posx + pepe.size / 2, 
                    pepe.posy + pepe.size / 2, 
                    pepe.size / ancho, 
                    pepe.size / alto,  
                    angulo_personaje,          
                    0
                );

                //dibujar enemigo
                for (int i = 0; i < cantidad_enemigos; i++)
                {
                    if(enemigos[i].activa)
                    {
                        float ancho_sprite = al_get_bitmap_width(img_enemigo1);
                        float alto_sprite = al_get_bitmap_height(img_enemigo1);

                        al_draw_scaled_rotated_bitmap(
                            img_enemigo1,
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

                //dibujar bala enemigo
                for (int i = 0; i < cantidad_enemigos; i++)
                {
                    if (enemigos[i].activa)
                    {
                        for(int j = 0; j < MAX_BALAS; j++)
                        {
                            if(enemigos[i].balas[j].activa)
                            {
                                al_draw_rotated_bitmap(
                                    img_bala_e1,
                                    al_get_bitmap_width(img_bala_e1)/2,
                                    al_get_bitmap_height(img_bala_e1)/2,
                                    enemigos[i].balas[j].posx,
                                    enemigos[i].balas[j].posy,
                                    enemigos[i].balas[j].angulo,
                                    0
                                );
                            }
                        }
                    }
                }

                //dibujar bala jugador
                for (int i = 0; i < MAX_BALAS; i++)
                {
                    if (pepe.balas[i].activa)
                    {
                        al_draw_rotated_bitmap(
                            img_bala,
                            al_get_bitmap_width(img_bala)/2,
                            al_get_bitmap_height(img_bala)/2,
                            pepe.balas[i].posx,
                            pepe.balas[i].posy,
                            pepe.balas[i].angulo,
                            0
                        );
                    }
                }

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

                float porcentaje_de_vida= (float)(pepe.vida)/(float)(pepe.vida_maxima);

                //dibujar porcentaje de vida
                al_draw_filled_rectangle(100,85, 100 + 390 * porcentaje_de_vida, 125, al_map_rgb(194,9,9));

                //dibujar fondo de barra de adrenalina
                al_draw_filled_rectangle(100, 125, 415, 152, al_map_rgb(50,50,50));

                float porcentaje_de_adren= (float)(pepe.adrenalina) / (float)(pepe.adren_maxima);

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

            al_flip_display();
        }
    }

    // Limpieza de recursos
    al_destroy_event_queue(cola_eventos);
    al_destroy_display(ventana);
    al_destroy_timer(temporizador);
    al_destroy_bitmap(sprite_personaje1);
    al_destroy_bitmap(img_piso);
    al_destroy_bitmap(img_pared);
    al_destroy_bitmap(img_pared_izq);
    al_destroy_bitmap(img_barra_adren);
    al_destroy_bitmap(img_barra_vida);
    al_destroy_bitmap(img_adrenalina);
    al_destroy_bitmap(img_titulo);
    al_destroy_font(fuente);
    al_destroy_bitmap(img_puntero);
    al_destroy_bitmap(img_bala);
    al_destroy_bitmap(img_srun1);
    al_destroy_bitmap(img_srun2);
    al_destroy_bitmap(img_enemigo1);
    al_destroy_bitmap(img_bala_e1);

    return 0;
}
