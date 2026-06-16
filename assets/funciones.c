#include <stdio.h>
#include <allegro5/allegro.h>
#include "estructuras.h"
#include "funciones.h"




void inicializar_mapa(int mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    FILE* nivelprueba = fopen("assets/mapas/nivelprueba.txt", "r");
    if (nivelprueba == NULL)
    {
        fprintf(stderr, "no se pudo abrir el archivo de mapa\n");
        return;
    }

    int f,c;
    for(f=0;f<MAPA_FILAS;f++){
        for(c=0;c<MAPA_COLUMNAS;c++){
           fscanf(nivelprueba, "%d", &mapa[f][c]);
        }
    }
    fclose(nivelprueba);
}

void dibujar_mapa(int mapa[MAPA_FILAS][MAPA_COLUMNAS], ALLEGRO_BITMAP* img_piso, ALLEGRO_BITMAP* img_pared)
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
            else
            {
                al_draw_bitmap(img_piso,x_pantalla,y_pantalla,0);
            }
        }

    }
}

void actualizar_jugador(jugador*p,bool teclas[4],int mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    //aca guardamos la posicion anterior
    float x_anterior=p->x;
    float y_anterior=p->y;

    //
    if(teclas[KEY_W])p->y-=p->velocidad;
    if(teclas[KEY_S])p->y+=p->velocidad;
    if(teclas[KEY_A])p->x-=p->velocidad;
    if(teclas[KEY_D])p->x+=p->velocidad;
    

    int casilla_x=(p->x + p-> tamaño/2) / TILE_SIZE;
    int casilla_y=(p->y + p-> tamaño/2) / TILE_SIZE;
     
    if (mapa[casilla_y][casilla_x] == 1) {
        p->x = x_anterior;
        p->y = y_anterior;
    }
}