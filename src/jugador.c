#include <math.h>
#include <stdbool.h>
#include "jugador.h"
#include "mapa.h"


//-------------hitbox------------------//

bool hay_colision(jugador *p, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    //calcular las celdas que el jugador pisa

    int fila_sup = (p->posy+18)/ TILE_SIZE; 
    int fila_inf = (p->posy-18 + p->size-1)/ TILE_SIZE;
    int col_izq  = (p->posx+18)/ TILE_SIZE;
    int col_der  = (p->posx-18 + p->size-1)/ TILE_SIZE;
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
void recarga_arma(jugador* p, bool teclas[KEYS])
{
    if(p->arma_actual.recargando)
    {
        p->arma_actual.tiempo_recarga_actual++;

        if(p->arma_actual.tiempo_recarga_actual >= p->arma_actual.tiempo_recarga_total)
        {
            int balas_necesarias = p->arma_actual.capacidad_cargador - p->arma_actual.municion;
            
            if(p->arma_actual.reserva >= balas_necesarias)
            {
                p->arma_actual.municion += balas_necesarias;
                p->arma_actual.reserva -= balas_necesarias;
            }
            else
            {
                p->arma_actual.municion += p->arma_actual.reserva;
                p->arma_actual.reserva = 0;
            }

            p->arma_actual.recargando = false;
            p->arma_actual.tiempo_recarga_actual = 0;
        }
    }

    else if (teclas[KEY_R])
    {
        if(p->arma_actual.municion < p->arma_actual.capacidad_cargador && p->arma_actual.reserva > 0)
        {
            p->arma_actual.recargando = true;
            p->arma_actual.tiempo_recarga_actual = 0;
        }
    }
}

void actualizar_jugador(jugador *p, bool teclas[KEYS], char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    //guardar pos anterior
    float x_anterior = p->posx;
    float y_anterior = p->posy;

    if(teclas[KEY_A]) {p->posx -= p->velocidad;}
    if(teclas[KEY_D]) {p->posx += p->velocidad;}

    if(hay_colision(p, mapa)) 
    {
        p->posx = x_anterior;
    }

    if(teclas[KEY_W]) {p->posy -= p->velocidad;}
    if(teclas[KEY_S]) {p->posy += p->velocidad;}

    if(hay_colision(p, mapa)) 
    {
        p->posy = y_anterior;
    }

    recarga_arma(p,teclas);
    
}

void disparar_jugador(jugador* p, float angulo, float cam_x, float cam_y, int mouse_x, int mouse_y)
{
    if (p->arma_actual.municion <= 0 || p->arma_actual.recargando)
    {
        return ;
    }

    for (int i = 0; i < MAX_BALAS; i ++)
    {
        if (!p->balas[i].activa)
        {
            float centro_x = p->posx + p->size/2;
            float centro_y = p->posy + p->size/2;

            float distancia_pistola = 40;
            float pistola_x = centro_x + distancia_pistola * cos(angulo);
            float pistola_y = centro_y + distancia_pistola * sin(angulo);

            float mouse_mundo_x = mouse_x + cam_x;
            float mouse_mundo_y = mouse_y + cam_y;
            float direccionx = mouse_mundo_x - pistola_x;
            float direcciony = mouse_mundo_y - pistola_y;

            float distancia_mouse = sqrt(direccionx*direccionx + direcciony*direcciony);
            float velocidad_bala = 30;

                    
            p->balas[i].posx = pistola_x;
            p->balas[i].posy = pistola_y;
            p->balas[i].vel_x = (direccionx/ distancia_mouse)* velocidad_bala;
            p->balas[i].vel_y = (direcciony/ distancia_mouse)* velocidad_bala;
            p->balas[i].angulo = atan2(direcciony, direccionx);
            p->balas[i].activa = true; 
            p->balas[i].daño = 25;
            p->cooldown_disparo = 20; //frames a esperar para el prox disparo

            p->arma_actual.municion--;
            break;

        }
    }             
}

void actualizar_balas_jugador(jugador* p, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    for (int i = 0; i < MAX_BALAS; i++)
    {
        if(p->balas[i].activa)
        {
            p->balas[i].posx += p->balas[i].vel_x;
            p->balas[i].posy += p->balas[i].vel_y;

            if (p->balas[i].posx < 0 || p->balas[i].posx > MAPA_COLUMNAS * TILE_SIZE || p->balas[i].posy < 0 || p->balas[i].posy > MAPA_FILAS * TILE_SIZE)
            {
                p->balas[i].activa = false;
                continue;
            }

            int fila = (p->balas[i].posy / TILE_SIZE);
            int col = (p->balas[i].posx / TILE_SIZE);
            if(colision(mapa[fila][col]))
            {
                p->balas[i].activa = false;
            }
        }
    }
}
void inicializar_arma1(jugador* p)
{
    p->arma_actual.tipo = PISTOLA;
    p->arma_actual.capacidad_cargador = 12; //12 por cargador
    p->arma_actual.municion = 12;
    p->arma_actual.reserva = 24;
    p->arma_actual.recargando = false;
    p->arma_actual.tiempo_recarga_actual = 0;
    p->arma_actual.tiempo_recarga_total = 60;
}

void spawn(jugador* p, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
    for (int f = 0; f < MAPA_FILAS; f++)
    {
        for(int c = 0; c < MAPA_COLUMNAS; c++)
        {
            if(mapa[f][c] == 'S')
            {
                p->posx = c * TILE_SIZE;
                p->posy = f * TILE_SIZE;
            }
        }
    }
    inicializar_arma1(p);
}