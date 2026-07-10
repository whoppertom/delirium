#include "estructuras.h"
#include "enemigo.h"
#include "funciones.h"
#include <math.h>

void inicializar_enemigos(char mapa[MAPA_FILAS][MAPA_COLUMNAS], enemigo enemigos[], int* cantidad)
{
    *cantidad = 0;
    int f,c;

    for (f = 0; f < MAPA_FILAS; f++)
    {
        for (c = 0; c < MAPA_COLUMNAS; c++)
        {
            if (mapa[f][c] == '@' && *cantidad < MAX_ENEMIGOS)
            {
                enemigos[*cantidad].posx = c * TILE_SIZE;
                enemigos[*cantidad].posy = f * TILE_SIZE;
                enemigos[*cantidad].ancho = 64;
                enemigos[*cantidad].alto = 64;
                enemigos[*cantidad].activa = true;
                enemigos[*cantidad].cooldown_disparo = 0;
                for (int b= 0; b<MAX_BALAS; b++)
                {
                    enemigos[*cantidad].balas[b].activa = false;
                }
                (*cantidad)++;
                mapa[f][c] = '.';
            }
        }
    }
}

void disparar_enemigo(enemigo* e, jugador* p)
{
    if (e->cooldown_disparo > 0)
    {
        e->cooldown_disparo--;
        return;
    }
    //centro de enemigo y jugador
    float centro_enemigox = e->posx + e->ancho / 2;
    float centro_enemigoy = e->posy + e->alto / 2;
    float centro_jugadorx = p->posx + p->size / 2;
    float centro_jugadory = p->posy + p->size / 2;

    float direccionx = centro_jugadorx - centro_enemigox;
    float direcciony = centro_jugadory - centro_enemigoy;
    float distancia = sqrt(direccionx*direccionx + direcciony*direcciony);

    float velocidad_bala = 8;
    for (int i = 0; i < MAX_BALAS; i++)
    {
        if(!e->balas[i].activa)
        {
            e->balas[i].posx = centro_enemigox;
            e->balas[i].posy = centro_enemigoy;
            e->balas[i].vel_x = (direccionx/distancia)* velocidad_bala;
            e->balas[i].vel_y = (direcciony/distancia)* velocidad_bala;
            e->balas[i].angulo = atan2(direcciony,direccionx);
            e->balas[i].activa = true;
            e->cooldown_disparo = 90;
            break;
        }
    }

}

void actualizar_balas_enemigo(enemigo* e, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    int i;
    for (i=0; i < MAX_BALAS; i++)
    {
        if (!e->balas[i].activa)
        {
            continue;
        }
        
        e->balas[i].posx += e->balas[i].vel_x;
        e->balas[i].posy += e->balas[i].vel_y;

        if (e->balas[i].posx < 0 || e->balas[i].posx > pantalla_ancho || e->balas[i].posy < 0 || e->balas[i].posy > pantalla_alto)
        {
            e->balas[i].activa = false;
            continue;
        }

        int fila = e->balas[i].posy / TILE_SIZE;
        int col = e->balas[i].posx / TILE_SIZE;
        if(colision(mapa[fila][col]))
        {
            e->balas[i].activa = false;
        }
    }
}

void daño_jugador(enemigo enemigos[], int cantidad, jugador* p)
{
    for (int i = 0; i < cantidad; i++)
    {
        if(!enemigos[i].activa)
        {
            continue;
        }

        for (int j = 0; j < MAX_BALAS; j++)
        {
            if(!enemigos[i].balas[j].activa)
            {
                continue;
            }

            float balax = enemigos[i].balas[j].posx;
            float balay = enemigos[i].balas[j].posy;

            //hitbox con el jugador
            if(balax > p->posx && balax < p->posx + p->size && balay > p->posy && balay < p->posy + p->size)
            {
                enemigos[i].balas[j].activa = false;
                p->vida -= 10;
                if(p->vida < 0)
                {
                    p->vida = 0;
                }
            }
        }
    }

}
