#ifndef DEFINICIONES_H
#define DEFINICIONES_H



//---------MAPA---------

#define MAPA_FILAS 17
#define MAPA_COLUMNAS 30
#define TILE_SIZE 64 //ancho y alto de cada bloque en pixeles

//---------PANTALLA---------

#define FPS 60
#define pantalla_ancho (MAPA_COLUMNAS * TILE_SIZE)
#define pantalla_alto (MAPA_FILAS * TILE_SIZE)

//---------JUGADOR---------

#define INICIO_POSX 100
#define INICIO_POSY 100
#define INICIO_VELOCIDAD 10
#define INICIO_SIZE 128
#define KEYS 4
#define corte_ancho_sprite 64
#define corte_alto_sprite 64

#define MAX_BALAS 20

//--------enemigo-------
#define MAX_ENEMIGOS 10
#define RANGO_VISION_ENEMIGO 8
#define VELOCIDAD_ENEMIGO 3
#define ESPERA_DE_PATRULLA 60


#endif
