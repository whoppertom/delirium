#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define MAPA_FILAS 17
#define MAPA_COLUMNAS 30
#define TILE_SIZE 64 //ancho y alto de cada bloque en pixeles

enum TECLAS 
{
    KEY_W,
    KEY_S,
    KEY_A,
    KEY_D
};

typedef struct {
    float x;
    float y;
    float velocidad;
    float tamaño;
}jugador;


#endif 