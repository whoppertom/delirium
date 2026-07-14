#include "estructuras.h"
#include "enemigo.h"
#include "funciones.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

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
                enemigos[*cantidad].ancho = 128;
                enemigos[*cantidad].alto = 128;
                enemigos[*cantidad].activa = true;
                enemigos[*cantidad].velocidad = VELOCIDAD_ENEMIGO;
                enemigos[*cantidad].angulo = 0;
                enemigos[*cantidad].modo_patrulla = rand()%2; // 0 = horizontal ; 1 = vertical
                enemigos[*cantidad].direccion = 1; // 1 = derecha/abajo ; -1 = izquierda/arriba
                enemigos[*cantidad].espera = 0;
                enemigos[*cantidad].cooldown_disparo = 0;
                enemigos[*cantidad].vida = 100;
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

void disparar_enemigo(enemigo* e, jugador* p, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
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


    if (distancia > RANGO_VISION_ENEMIGO * TILE_SIZE)
    {
        return;
    }

    //hay bloque entre medio
    if(!linea_de_vision(e,p,mapa))
    {
        return;
    }

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

bool linea_de_vision(enemigo* e, jugador* p, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{
//centro de enemigo y jugador
    float centro_enemigox = e->posx + e->ancho / 2;
    float centro_enemigoy = e->posy + e->alto / 2;
    float centro_jugadorx = p->posx + p->size / 2;
    float centro_jugadory = p->posy + p->size / 2;

    float direccionx = centro_jugadorx - centro_enemigox;
    float direcciony = centro_jugadory - centro_enemigoy;
    float distancia = sqrt(direccionx*direccionx + direcciony*direcciony);

    int bloques = distancia/10;

    for(int i = 1; i < bloques; i++)
    {
        float x = centro_enemigox + (direccionx/bloques)* i;
        float y = centro_enemigoy + (direcciony/bloques)* i;

        int fila = y/TILE_SIZE;
        int col = x/TILE_SIZE;

        if(fila >= 0 && fila < MAPA_FILAS && col >= 0 && col < MAPA_COLUMNAS)
        {
            if(colision(mapa[fila][col]))
            {
                return false;
            }
        }
    }
    return true;
}

void actualizar_enemigo(enemigo* e, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{

    if (e->espera>0)
    {
        e->espera--;
        return;
    }

    float nueva_posx = e->posx;
    float nueva_posy = e->posy;

    //horizontal
    if(e->modo_patrulla == 0) 
    {
        nueva_posx += e->velocidad * e->direccion;
        
        if(e->direccion == 1) //derecha
        {
            e->angulo = 0;
        }
        else //izquierda
        {
            e->angulo = M_PI;
        }
    }

    //vertical
    else 
    {
        nueva_posy += e->velocidad * e->direccion;

        if(e->direccion == 1) //abajo
        {
            e->angulo = M_PI / 2;
        }
        else //arriba
        {
            e->angulo = -M_PI /2;
        }
    }

    //chocar con colision
    int fila_sup =(nueva_posy + 10) / TILE_SIZE;
    int fila_inf =(nueva_posy + e->alto - 10) / TILE_SIZE;
    int col_izq =(nueva_posx + 10) / TILE_SIZE;
    int col_der =(nueva_posx + e->ancho - 10) / TILE_SIZE;

    bool chocar = false;
    for (int f = fila_sup; f <= fila_inf && !chocar; f++)
    {
        for(int c = col_izq; c <= col_der && !chocar; c++)
        {
            if (f >= 0 && f < MAPA_FILAS && c >= 0 && c < MAPA_COLUMNAS)
            {
                if(colision(mapa[f][c]))
                {
                    chocar=true;
                }
            }
        } 
    }

    if(chocar)
    {
        e->direccion = -e->direccion;
        e->espera = ESPERA_DE_PATRULLA;
    }
    else
    {
        e->posx = nueva_posx;
        e->posy = nueva_posy;
    }
}


void daño_enemigo(enemigo enemigos[], int cantidad, jugador* p)
{
    for (int i=0; i < MAX_BALAS; i++)
    {

        if(!p->balas[i].activa)
        {
            continue;
        }

        float bala_posx = p->balas[i].posx;
        float bala_posy = p->balas[i].posy;

        for(int j = 0; j < cantidad; j++)
        {
            if(!enemigos[j].activa)
            {
                continue;
            }
            if(bala_posx > enemigos[j].posx && bala_posx < enemigos[j].posx + enemigos[j].ancho && bala_posy > enemigos[j].posy && bala_posy < enemigos[j].posy + enemigos[j].alto)
            {
                p->balas[i].activa = false; //bala desaparece al impactar con el enemigo
                enemigos[j].vida -= p->balas[i].daño;
            
                if (enemigos[j].vida <= 0)
                {
                    enemigos[j].activa = false;
                }
                break;
            }
        }


    }
}