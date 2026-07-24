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
    texturas->img_vida = al_load_bitmap("sprites/vida.png");
}
void cargar_texturas_sprites(texturas_sprites* sprites)
{
    sprites->sprite_personaje1 = al_load_bitmap("sprites/sprite1.png");
    sprites->img_srun1 = al_load_bitmap("sprites/sprite1_run.png");
    sprites->img_srun2 = al_load_bitmap("sprites/sprite1_run2.png");
    sprites->img_bala = al_load_bitmap("sprites/bala.png");
    sprites->img_enemigo1 = al_load_bitmap("sprites/enemigo1.png");
    sprites->img_bala_e1 = al_load_bitmap("sprites/bala_enemigo1.png");
    sprites->img_adrenalina = al_load_bitmap("sprites/adrenalina.png");
    sprites->img_enemigo2 = al_load_bitmap("sprites/enemigo2.png");
    sprites->img_enemigo3 = al_load_bitmap("sprites/enemigo3.png");
    sprites->img_bala_e3 = al_load_bitmap("sprites/bala_enemigo3.png");
}

void cargar_texturas_hud(texturas_hud* hud)
{
    hud->img_puntero = al_load_bitmap("sprites/puntero.png");
    hud->img_barra_vida = al_load_bitmap("sprites/barra_vida.png");
    hud->img_barra_adren = al_load_bitmap("sprites/barra_adrenalina.png");
    hud->img_titulo = al_load_bitmap("sprites/titulo.png");
    hud->img_bala_hud = al_load_bitmap("sprites/bala_hud.png");
    hud->img_recarga = al_load_bitmap("sprites/recarga.png");
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