#include <stdio.h>
#include <allegro5/allegro.h>
#include "estructuras.h"
#include "funciones.h"




void inicializar_mapa(int mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    FILE* nivelprueba = fopen("assets/mapas/nivelprueba.txt", "r");

    int f,c;
    for(f=0;f<MAPA_FILAS;f++){
        for(c=0;c<MAPA_COLUMNAS;c++){
           fscanf(nivelprueba, "%d", &mapa[f][c]);
        }
    }
    fclose(nivelprueba);
}

void dibujar_mapa(int mapa[MAPA_FILAS][MAPA_COLUMNAS], ALLEGRO_BITMAP* img_piso, ALLEGRO_BITMAP* img_pared, ALLEGRO_BITMAP* img_pared_izq)
{
    int f_dibujada, c_dibujada;
    for(f_dibujada=0;f_dibujada<MAPA_FILAS;f_dibujada++)
    {
        for(c_dibujada=0;c_dibujada<MAPA_COLUMNAS;c_dibujada++)
        {
            //encontrar la coordenada exacta donde se ubicara la pared/piso
            float x_pantalla=c_dibujada*TILE_SIZE;
            float y_pantalla=f_dibujada*TILE_SIZE;

            //si hay un 1 colocamos sprite de pared
            if(mapa[f_dibujada][c_dibujada]==1)
            {
                al_draw_bitmap(img_pared,x_pantalla,y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada]==0)
            {
                al_draw_bitmap(img_piso,x_pantalla,y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada]==2)
            {
                al_draw_bitmap(img_pared_izq,x_pantalla,y_pantalla,0);
            }
        }

    }
}

//-------determinar colision para bloques-------//

bool colision(int celda)
{
    return celda == 1 ||
           celda == 2;
}

//-------------hitbox------------------//

bool hay_colision(jugador *p, int mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    //calcular las celdas que el jugador pisa

    int fila_sup = (p->posy)/ TILE_SIZE; 
    int fila_inf = (p->posy + p->size-1)/ TILE_SIZE;
    int col_izq  = (p->posx)/ TILE_SIZE;
    int col_der  = (p->posx + p->size-1)/ TILE_SIZE;
    int f, c;

    //recorrer todas las celdas
    for(f = fila_sup; f <= fila_inf; f++)
    {
        for(c = col_izq; c <= col_der; c++)
        {
            if(colision(mapa[f][c])) 
            //retornamos true = si hay colision
            return true;
        }
    }

    //retornamos false = no hay colision
    return false;
}

void actualizar_jugador(jugador *p, bool teclas[KEYS], int mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    //guardar pos anterior
    float x_anterior = p->posx;
    float y_anterior = p->posy;

    if(teclas[KEY_A]) {p->posx -= p->velocidad;}
    if(teclas[KEY_D]) {p->posx += p->velocidad;}

    if(hay_colision(p, mapa)) {p->posx = x_anterior;}

    if(teclas[KEY_W]) {p->posy -= p->velocidad;}
    if(teclas[KEY_S]) {p->posy += p->velocidad;}

    if(hay_colision(p, mapa)) {p->posy = y_anterior;}
}
