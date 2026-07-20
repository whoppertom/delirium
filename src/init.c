#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "init.h"

bool inicializar_allegro()
{
    if (!al_init()) {fprintf(stderr, "no se pudo inicializar allegro");return -1;}

    if (!al_init_image_addon()) {fprintf(stderr, "no se pudo inicializar imagenes");return -1;}

    if (!al_init_font_addon()) {fprintf(stderr, "no se pudo inicializar fuentes");return -1;}

    if (!al_init_ttf_addon()) {fprintf(stderr, "no se pudo inicializar ttf");return -1;}

    if (!al_install_keyboard()) {fprintf(stderr, "no se detecto el teclado");return -1;}

    if(!al_install_mouse()) {fprintf(stderr, "no se detecto el mouse");return -1;}

    if (!al_init_primitives_addon()) {fprintf(stderr, "no se pudo inicializar primitivas");return -1;}
    return true;
}

void cargar_texturas_mapa(texturas_mapa* texturas)
{
    texturas->img_piso = al_load_bitmap("sprites/piso.png");
    texturas->img_pared = al_load_bitmap("sprites/pared.png");
    texturas->img_pared_izq = al_load_bitmap("sprites/pared_izq.png");
    texturas->img_pared_interior = al_load_bitmap("sprites/pared_interior.png");
    texturas->img_adrenalina = al_load_bitmap("sprites/adrenalina.png");
    texturas->img_esquina_sup_izq = al_load_bitmap("sprites/esquina_sup_izq.png");
    texturas->img_esquina_sup_der = al_load_bitmap("sprites/esquina_sup_der.png");
    texturas->img_pared_der = al_load_bitmap("sprites/pared_der.png");
    texturas->img_pared_abajo = al_load_bitmap("sprites/pared_abajo.png");
    texturas->img_esquina_inf_izq = al_load_bitmap("sprites/esquina_inf_izq.png");
    texturas->img_esquina_inf_der = al_load_bitmap("sprites/esquina_inf_der.png");
    texturas->img_borde1 = al_load_bitmap("sprites/borde1.png");
    texturas->img_borde2 = al_load_bitmap("sprites/borde2.png");
    texturas->img_borde3 = al_load_bitmap("sprites/borde3.png");
    texturas->img_borde4 = al_load_bitmap("sprites/borde4.png");
    texturas->img_negro = al_load_bitmap("sprites/negro.png");
    texturas->img_piso_som = al_load_bitmap("sprites/piso_sombra.png");
    texturas->img_piso_lat_som = al_load_bitmap("sprites/piso_lat_som.png");
    texturas->img_piso_esq_som = al_load_bitmap("sprites/piso_esq_som.png");

}

void destruir_texturas(texturas_mapa* texturas)
{
    al_destroy_bitmap(texturas->img_piso);
    al_destroy_bitmap(texturas->img_pared);
    al_destroy_bitmap(texturas->img_pared_izq);
    al_destroy_bitmap(texturas->img_adrenalina);
    al_destroy_bitmap(texturas->img_pared_interior);
    al_destroy_bitmap(texturas->img_esquina_sup_izq);
    al_destroy_bitmap(texturas->img_esquina_sup_der);
    al_destroy_bitmap(texturas->img_pared_der);
    al_destroy_bitmap(texturas->img_pared_abajo);
    al_destroy_bitmap(texturas->img_esquina_inf_izq);
    al_destroy_bitmap(texturas->img_esquina_inf_der);
    al_destroy_bitmap(texturas->img_borde1);
    al_destroy_bitmap(texturas->img_borde2);
    al_destroy_bitmap(texturas->img_borde3);
    al_destroy_bitmap(texturas->img_borde4);
    al_destroy_bitmap(texturas->img_negro);
    al_destroy_bitmap(texturas->img_piso_som);
    al_destroy_bitmap(texturas->img_piso_lat_som);
    al_destroy_bitmap(texturas->img_piso_esq_som);
}