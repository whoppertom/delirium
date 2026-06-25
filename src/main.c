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

    // CARGAR SPRITES
    ALLEGRO_BITMAP* sprite_personaje1 = al_load_bitmap("sprites/sprite1.png");
    ALLEGRO_BITMAP* img_piso = al_load_bitmap("sprites/piso.png");
    ALLEGRO_BITMAP* img_pared = al_load_bitmap("sprites/pared.png");
    ALLEGRO_BITMAP* img_pared_izq = al_load_bitmap("sprites/pared_izq.png");
    ALLEGRO_BITMAP* img_barra_vida = al_load_bitmap("sprites/barra_vida.png");
    ALLEGRO_BITMAP* img_adrenalina = al_load_bitmap("sprites/adrenalina.png");

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
    al_register_event_source(cola_eventos, al_get_timer_event_source(temporizador));


    jugador pepe = {INICIO_POSX, INICIO_POSY, INICIO_VELOCIDAD, INICIO_SIZE, 0, 100, 100};

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

        else if(evento.type == ALLEGRO_EVENT_TIMER)
        {
            actualizar_jugador(&pepe, teclas, mapa);
            
            //bordes
            if(pepe.posx < 0){pepe.posx = 0;}
            if(pepe.posy < 0){pepe.posy = 0;}
            if(pepe.posx > borde_ancho_pantalla - pepe.size){pepe.posx = borde_ancho_pantalla - pepe.size;}
            if(pepe.posy > borde_alto_pantalla - pepe.size){pepe.posy = borde_alto_pantalla - pepe.size;}

            //no resetea en cada frame
            static int contador_vida = 0;
            contador_vida++;
            if(contador_vida >= 8)
            {
                contador_vida = 0;
                if(pepe.vida > 0)
                {
                    pepe.vida--;
                }
            }

            int centro_fila_jug = (pepe.posy + pepe.size /2) / TILE_SIZE;
            int centro_columna_jug = (pepe.posx + pepe.size /2) / TILE_SIZE;

            if(mapa[centro_fila_jug][centro_columna_jug] == 'A')
            {
                pepe.vida += 16;
                if(pepe.vida > pepe.vida_maxima)
                {
                    pepe.vida = pepe.vida_maxima;
                }
                mapa[centro_fila_jug][centro_columna_jug] = '.';
            }

            redibujar=true;
        }
        if (redibujar && al_is_event_queue_empty(cola_eventos))
        {

            redibujar=false;
            al_clear_to_color(al_map_rgb(0,0,0));
            dibujar_mapa(mapa, img_piso, img_pared,img_pared_izq, img_adrenalina);


            al_draw_scaled_bitmap(
                sprite_personaje1,
                0,0, //posicion en el sprite
                corte_ancho_sprite, corte_alto_sprite, //tamaño del recorte
                pepe.posx, pepe.posy,
                pepe.size, pepe.size,
                0
            );

            //dibujar barra de vida
            float barra_posx = 20;
            float barra_posy = 20;
            float barra_ancho = 500;
            float barra_alto = 200;



            //dibujar fondo de barra de vida
            al_draw_filled_rectangle(100, 84, 485, 142, al_map_rgb(50,50,50));

            float porcentaje_de_vida = (float)(pepe.vida) / (float)(pepe.vida_maxima);
            //dibujar porcentaje de vida
            al_draw_filled_rectangle(100, 84, 100 + 385 * porcentaje_de_vida, 142, al_map_rgb(100, 0, 180));

            al_draw_scaled_bitmap(
                img_barra_vida,
                0, 0,
                al_get_bitmap_width(img_barra_vida),
                al_get_bitmap_height(img_barra_vida),
                barra_posx, barra_posy,
                barra_ancho, barra_alto,
                0
                
            );

        
        
            

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
    al_destroy_bitmap(img_barra_vida);
    al_destroy_bitmap(img_adrenalina);

    return 0;
}
