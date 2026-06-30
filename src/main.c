#include <stdio.h>
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "funciones.h"
#include "estructuras.h"




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

    //if (!sprite_personaje1 || !img_piso || !img_pared || !img_pared_izq) {fprintf(stderr, "error al cargar sprites");return -1;}

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


    jugador pepe = {INICIO_POSX, INICIO_POSY, INICIO_VELOCIDAD, INICIO_SIZE, 0, 100, 100, 100, 100};
    estado_juego estado = MENU;

    al_start_timer(temporizador);

    bool teclas[KEYS] = {false};
    bool ejecutar=true;
    bool redibujar=true;
    
    char mapa[MAPA_FILAS][MAPA_COLUMNAS];
    inicializar_mapa(mapa);



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
        else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if (estado == MENU)
            {
                int pos_mousex = evento.mouse.x;
                int pos_mousey = evento.mouse.y;

                if (pos_mousex >= 760 && pos_mousex <= 1160 && pos_mousey >= 450 && pos_mousey <= 530)
                {
                    estado = JUEGO;
                }
                
                if (pos_mousex >= 760 && pos_mousex <= 1160 && pos_mousey >= 570 && pos_mousey <= 650)
                {
                    ejecutar = false;
                }
            }
        }

        else if(evento.type == ALLEGRO_EVENT_TIMER)
        {
            if (estado == JUEGO)
            {
                actualizar_jugador(&pepe, teclas, mapa);

                //bordes
                if(pepe.posx < 0){pepe.posx = 0;}
                if(pepe.posy < 0){pepe.posy = 0;}
                if(pepe.posx > borde_ancho_pantalla - pepe.size){pepe.posx = borde_ancho_pantalla - pepe.size;}
                if(pepe.posy > borde_alto_pantalla - pepe.size){pepe.posy = borde_alto_pantalla - pepe.size;}

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
                redibujar=true;
            }
        }

        if (redibujar && al_is_event_queue_empty(cola_eventos))
        {

            redibujar=false;
            al_clear_to_color(al_map_rgb(0,0,0));

            if (estado == MENU)
            {
                al_draw_bitmap(img_titulo,400,80,0);
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

                al_draw_scaled_bitmap(
                    sprite_personaje1,
                    0,0, //posicion en el sprite
                    corte_ancho_sprite, corte_alto_sprite, //tamaño del recorte
                    pepe.posx, pepe.posy,
                    pepe.size, pepe.size,
                    0
                );
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

    return 0;
}
