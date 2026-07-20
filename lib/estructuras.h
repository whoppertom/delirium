#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
#include "definiciones.h"
#include <stdbool.h>
#include <allegro5/allegro.h>


enum TECLAS 
{
    KEY_W,
    KEY_S,
    KEY_A,
    KEY_D
};
typedef struct{
    float posx;
    float posy;
    float vel_x;
    float vel_y;
    float angulo;
    bool activa;
    int daño;
}bala;


typedef struct {
    float posx;
    float posy;
    float ancho;
    float alto;
    bool activa;
    bala balas[MAX_BALAS];
    int cooldown_disparo;
    float velocidad;
    float angulo;
    int modo_patrulla; // 0 = horizontal ; 1 = vertical
    int direccion; //1 = derecha/abajo ; -1 = izquierda/arriba
    int espera;
    int vida;
}enemigo;

typedef enum {
    MENU, // 0
    JUEGO, // 1 
} estado_juego;

typedef struct {
    ALLEGRO_BITMAP* img_piso;
    ALLEGRO_BITMAP* img_pared;
    ALLEGRO_BITMAP* img_pared_izq;
    ALLEGRO_BITMAP* img_adrenalina;
    ALLEGRO_BITMAP* img_pared_interior;
    ALLEGRO_BITMAP* img_esquina_sup_izq;
    ALLEGRO_BITMAP* img_esquina_sup_der;
    ALLEGRO_BITMAP* img_pared_der;
    ALLEGRO_BITMAP* img_pared_abajo;
    ALLEGRO_BITMAP* img_esquina_inf_izq;
    ALLEGRO_BITMAP* img_esquina_inf_der;
    ALLEGRO_BITMAP* img_borde1;   
    ALLEGRO_BITMAP* img_borde2;
    ALLEGRO_BITMAP* img_borde3;
    ALLEGRO_BITMAP* img_borde4;
    ALLEGRO_BITMAP* img_negro;
    ALLEGRO_BITMAP* img_piso_som;
    ALLEGRO_BITMAP* img_piso_lat_som;
    ALLEGRO_BITMAP* img_piso_esq_som;
} texturas_mapa;



#endif 