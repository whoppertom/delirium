#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "estructuras.h"
#include "mapa.h"
#include "jugador.h"



void inicializar_mapa(char mapa[MAPA_FILAS][MAPA_COLUMNAS], const char* ruta)
{
    FILE* nivel_1 = fopen(ruta, "r");

    int f,c;
    for(f=0;f<MAPA_FILAS;f++){
        for(c=0;c<MAPA_COLUMNAS;c++)
        {
           fscanf(nivel_1, " %c", &mapa[f][c]);
        }
    }
    fclose(nivel_1);
}

void dibujar_mapa(char mapa[MAPA_FILAS][MAPA_COLUMNAS], texturas_mapa* texturas)
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
            if(mapa[f_dibujada][c_dibujada] == '#')
            {
                al_draw_bitmap(texturas->img_pared,x_pantalla,y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '.')
            {
                al_draw_bitmap(texturas->img_piso,x_pantalla,y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '$')
            {
                al_draw_bitmap(texturas->img_pared_izq,x_pantalla,y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '!')
            {
                al_draw_bitmap(texturas->img_pared_interior, x_pantalla,y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '1')
            {
                al_draw_bitmap(texturas->img_esquina_sup_izq, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '2')
            {
                al_draw_bitmap(texturas->img_esquina_sup_der, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '3')
            {
                al_draw_bitmap(texturas-> img_esquina_inf_izq, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '4')
            {
                al_draw_bitmap(texturas-> img_esquina_inf_der, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '5')
            {
                al_draw_bitmap(texturas-> img_borde1, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '6')
            {
                al_draw_bitmap(texturas-> img_borde2, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '7')
            {
                al_draw_bitmap(texturas-> img_borde3, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '8')
            {
                al_draw_bitmap(texturas-> img_borde4, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == 'N')
            {
                al_draw_bitmap(texturas-> img_negro, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == ',')
            {
                al_draw_bitmap(texturas-> img_piso_som, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == ';')
            {
                al_draw_bitmap(texturas-> img_piso_lat_som, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == 'e')
            {
                al_draw_bitmap(texturas->img_piso_esq_som, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '/')
            {
                al_draw_bitmap(texturas->img_pared_der, x_pantalla, y_pantalla,0);
            }
            else if(mapa[f_dibujada][c_dibujada] == '-')
            {
                al_draw_bitmap(texturas->img_pared_abajo, x_pantalla, y_pantalla,0);
            }

            //--------------INTERACTUABLES--------------//
            else if(mapa[f_dibujada][c_dibujada]== 'S')
            {
                al_draw_bitmap(texturas->img_piso, x_pantalla, y_pantalla,0);
            }
            
            else if (mapa[f_dibujada][c_dibujada] == 'F')
            {
                al_draw_bitmap(texturas->img_piso,x_pantalla,y_pantalla,0);
                al_draw_filled_rectangle(x_pantalla,y_pantalla,x_pantalla + TILE_SIZE, y_pantalla + TILE_SIZE, al_map_rgba(0, 255, 0, 100));
            }
            
            else if(mapa[f_dibujada][c_dibujada] == 'A')
            {
                al_draw_bitmap(texturas->img_piso, x_pantalla, y_pantalla, 0);
                al_draw_scaled_bitmap(texturas->img_adrenalina,
                    0,0,
                    al_get_bitmap_width(texturas->img_adrenalina),
                    al_get_bitmap_height(texturas->img_adrenalina),
                    x_pantalla, y_pantalla,
                    TILE_SIZE, TILE_SIZE,
                    0
                );
            }

            else if(mapa[f_dibujada][c_dibujada] == 'V')
            {
                al_draw_bitmap(texturas->img_piso,x_pantalla,y_pantalla, 0);
                al_draw_scaled_bitmap(texturas->img_vida,
                    0,0,
                    al_get_bitmap_width(texturas->img_vida),
                    al_get_bitmap_height(texturas->img_vida),
                    x_pantalla,y_pantalla,
                    TILE_SIZE, TILE_SIZE,
                    0
                );
            }


        }

    }
}


bool colision(char celda)
{
    return celda == '#' ||
           celda == '$' ||
           celda == '!' ||
           celda == '/' ||
           celda == '-' ||
           celda == '5' ||
           celda == '6' ||
           celda == '7' ||
           celda == '8' ;
}



