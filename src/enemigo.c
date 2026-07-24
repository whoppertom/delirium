#include "estructuras.h"
#include "enemigo.h"
#include "mapa.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "jugador.h"

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
                enemigos[*cantidad].tipo = 1;
                enemigos[*cantidad].posx = c * TILE_SIZE;
                enemigos[*cantidad].posy = f * TILE_SIZE;
                enemigos[*cantidad].ancho = 100;
                enemigos[*cantidad].alto = 100;
                enemigos[*cantidad].activa = true;
                enemigos[*cantidad].velocidad = VELOCIDAD_ENEMIGO;
                enemigos[*cantidad].angulo = 0;
                enemigos[*cantidad].estado = 0;
                enemigos[*cantidad].target_x = 0;
                enemigos[*cantidad].target_y = 0;
                enemigos[*cantidad].espera = 60;
                enemigos[*cantidad].cooldown_disparo = 0;
                enemigos[*cantidad].vida = 100;
                for (int b= 0; b<MAX_BALAS; b++)
                {
                    enemigos[*cantidad].balas[b].activa = false;
                }
                (*cantidad)++;
                mapa[f][c] = '.';
            }

            if(mapa[f][c] == '0' && *cantidad < MAX_ENEMIGOS)
            {
                enemigos[*cantidad].tipo = 2;
                enemigos[*cantidad].posx = c * TILE_SIZE;
                enemigos[*cantidad].posy = f * TILE_SIZE;
                enemigos[*cantidad].ancho = 100;
                enemigos[*cantidad].alto = 100;
                enemigos[*cantidad].activa = true;
                enemigos[*cantidad].velocidad = VELOCIDAD_ENEMIGO * 3;
                enemigos[*cantidad].angulo = 0;
                enemigos[*cantidad].estado = 0;
                enemigos[*cantidad].target_x = 0;
                enemigos[*cantidad].target_y = 0;
                enemigos[*cantidad].espera = 60;
                enemigos[*cantidad].cooldown_disparo = 0; //cooldown golpe
                enemigos[*cantidad].vida = 150;
                for (int b = 0; b<MAX_BALAS; b++)
                {
                    enemigos[*cantidad].balas[b].activa = false;
                }
                (*cantidad)++;
                mapa[f][c] = '.' ;
            }

            if(mapa[f][c] == 'x' && *cantidad < MAX_ENEMIGOS)
            {
                enemigos[*cantidad].tipo = 3;
                enemigos[*cantidad].posx = c * TILE_SIZE;
                enemigos[*cantidad].posy = f * TILE_SIZE;
                enemigos[*cantidad].ancho = 100;
                enemigos[*cantidad].alto = 100;
                enemigos[*cantidad].activa = true;
                enemigos[*cantidad].velocidad = 0;
                enemigos[*cantidad].angulo = 0;
                enemigos[*cantidad].estado = 0;
                enemigos[*cantidad].target_x = 0;
                enemigos[*cantidad].target_y = 0;
                enemigos[*cantidad].espera = 60;
                enemigos[*cantidad].cooldown_disparo = 0; //cooldown golpe
                enemigos[*cantidad].vida = 100;
                for (int b = 0; b<MAX_BALAS; b++)
                {
                    enemigos[*cantidad].balas[b].activa = false;
                }
                (*cantidad)++;
                mapa[f][c] = '.' ;
            }
        }
    }
}

void disparar_enemigo(enemigo* e, jugador* p, char mapa[MAPA_FILAS][MAPA_COLUMNAS])
{   
    if (e->tipo == 2) return;
    
    if (e->cooldown_disparo > 0)
    {
        e->cooldown_disparo--;
        return;
    }

    if(e->estado !=2)
    {
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

    //------------ENEMIGO 1-----------------//

    if (e->tipo == 1)
    {
        float velocidad_bala = 20;
        for(int i = 0; i < MAX_BALAS; i++)
        {
            if(!e->balas[i].activa)
            {
            e->balas[i].posx = centro_enemigox;
            e->balas[i].posy = centro_enemigoy;
            e->balas[i].vel_x = (direccionx/distancia)* velocidad_bala;
            e->balas[i].vel_y = (direcciony/distancia)* velocidad_bala;
            e->balas[i].angulo = atan2(direcciony,direccionx);
            e->balas[i].activa = true;
            e->cooldown_disparo = 45;
            e->balas[i].daño = 10;
            break;
            }

        }
    }

    //-------------ENEMIGO 3--------------//
    if(e->tipo == 3)
    {
        float velocidad_bala = 30;
        for(int i = 0; i < MAX_BALAS; i++)
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
            e->balas[i].daño = 30;
            break;
            }

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

        if (e->balas[i].posx < 0 || e->balas[i].posx > (MAPA_COLUMNAS * TILE_SIZE) || e->balas[i].posy < 0 || e->balas[i].posy > (MAPA_FILAS * TILE_SIZE))
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
        //---------------- ENEMIGO 1 ---------------//
        if (enemigos[i].tipo == 1)
        {
            for (int j = 0; j < MAX_BALAS; j++)
            {
                if(!enemigos[i].balas[j].activa)
                {
                    continue;
                }
                float bala_x = enemigos[i].balas[j].posx;
                float bala_y = enemigos[i].balas[j].posy;
                if(bala_x > p->posx && bala_x < p->posx + p->size && bala_y > p->posy && bala_y < p->posy + p->size)
                {
                    enemigos[i].balas[j].activa = false;
                    p->vida -= enemigos[i].balas[j].daño; 
                    if(p->vida < 0)
                    {
                        p->vida = 0;
                    }
                }
            }
        }
        //---------------- ENEMIGO 2  ---------------//
        else if(enemigos[i].tipo == 2)
        {
            if (enemigos[i].cooldown_disparo > 0)
            {
                enemigos[i].cooldown_disparo--;
            }
            float direccion_x = (enemigos[i].posx + enemigos[i].ancho/2) - (p->posx + p->size/2);
            float direccion_y = (enemigos[i].posy + enemigos[i].alto/2) - (p->posy + p->size/2);
            float distancia = sqrt(direccion_x*direccion_x + direccion_y*direccion_y);
            if(distancia < (enemigos[i].ancho/2 + p->size/2 - 20))
            {
                if(enemigos[i].cooldown_disparo <= 0)
                {
                    p->vida -= 15;
                    if(p->vida < 0)
                    {
                        p->vida = 0;
                    }
                    enemigos[i].cooldown_disparo = 60;
                }
            }
        }
        //---------------- ENEMIGO 3 ---------------//
        else if (enemigos[i].tipo == 3)
        {
            for (int j = 0; j < MAX_BALAS; j++)
            {
                if(!enemigos[i].balas[j].activa)
                {
                    continue;
                }
                float bala_x = enemigos[i].balas[j].posx;
                float bala_y = enemigos[i].balas[j].posy;
                if(bala_x > p->posx && bala_x < p->posx + p->size && bala_y > p->posy && bala_y < p->posy + p->size)
                {
                    enemigos[i].balas[j].activa = false;
                    p->vida -= enemigos[i].balas[j].daño; 
                    if(p->vida < 0)
                    {
                        p->vida = 0;
                    }
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

void actualizar_enemigo(enemigo* e, char mapa[MAPA_FILAS][MAPA_COLUMNAS], jugador* p)
{
    float centro_enemigox = e->posx + e->ancho/2;
    float centro_enemigoy = e->posy + e->alto/2;
    float centro_jugadorx = p->posx + p->size/2;
    float centro_jugadory = p->posy + p->size/2;

    float distanciax = centro_jugadorx - centro_enemigox;
    float distanciay = centro_jugadory - centro_enemigoy;
    float distancia_total = sqrt(distanciax*distanciax + distanciay*distanciay);

    bool ver_jugador = (distancia_total <= RANGO_VISION_ENEMIGO * TILE_SIZE) && linea_de_vision(e,p,mapa);


    //----------------ENEMIGO 1------------//
    if (e->tipo == 1)
    {
        if(ver_jugador)
        {
            e->estado = 2; //atacar
            e->target_x = centro_jugadorx;
            e->target_y = centro_jugadory;
        }
        else if (e->estado == 2)
        {
            e->estado = 3;
        }

        if(e-> estado == 0)
        {
            if(e->espera>0)
            {
                e->espera--;
            }

        else
        {
            bool objetivo = false;
            while (!objetivo)
            {
                int f = rand() % MAPA_FILAS;
                int c = rand() % MAPA_COLUMNAS;

                if(!colision(mapa[f][c]))
                {
                    e->target_x = c * TILE_SIZE;
                    e->target_y = f * TILE_SIZE;
                    e->estado = 1;
                    objetivo = true;
                }
            }
        }
        }

        else if(e->estado == 1 || e->estado == 3)
        {
            float vel_actual;
            if(e->estado == 3)
            {
                vel_actual = VELOCIDAD_BUSQUEDA;
            }
            else
            {
                vel_actual = e->velocidad;
            }
            float dir_x = e->target_x - e->posx;
            float dir_y = e->target_y - e->posy;
            float distancia_al_target = sqrt(dir_x*dir_x + dir_y*dir_y);

            if(distancia_al_target < vel_actual)
            {
                e->posx = e->target_x;
                e->posy = e->target_y;
                e->estado = 0;
                e->espera = 60;
                return;
            }

            float nueva_posx = e->posx + (dir_x / distancia_al_target) * vel_actual;
            float nueva_posy = e->posy + (dir_y / distancia_al_target) * vel_actual;

            e->angulo = atan2(dir_y, dir_x);

            int fila_sup = (nueva_posy + 10) / TILE_SIZE;
            int fila_inf = (nueva_posy + e->alto - 10) / TILE_SIZE;
            int col_izq = (nueva_posx + 10) / TILE_SIZE;
            int col_der = (nueva_posx + e->ancho - 10) / TILE_SIZE;
        
            bool chocar = false;
            for(int f = fila_sup; f <= fila_inf && !chocar; f++)
            {
                for(int c = col_izq; c<= col_der && !chocar; c++)
                {
                    if(f >= 0 && f < MAPA_FILAS && c >= 0 && c < MAPA_COLUMNAS)
                    {
                        if(colision(mapa[f][c]))
                        {
                            chocar = true;
                        }
                    }
                }
            }

            if(chocar)
            {
                e->estado = 0;
                e->espera = 60;
            }
            else
            {
                e->posx = nueva_posx;
                e->posy = nueva_posy;
            }
        }
        else if( e->estado == 2)
        {
            e->angulo = atan2(distanciay, distanciax);
        }    
    }

    //--------------ENEMIGO 2-----------//

    else if(e->tipo == 2)
    {
        if(ver_jugador)
        {
            e->estado = 2;
            e->target_x = centro_jugadorx;
            e->target_y = centro_jugadory;
        }
        else if (e->estado == 2)
        {
            e->estado = 3;
        }

        if(e-> estado == 0)
        {
            if(e->espera>0)
            {
                e->espera--;
            }

            else
            {
                bool objetivo = false;
                while (!objetivo)
                {
                    int f = rand() % MAPA_FILAS;
                    int c = rand() % MAPA_COLUMNAS;

                    if(!colision(mapa[f][c]))
                    {
                        e->target_x = c * TILE_SIZE;
                        e->target_y = f * TILE_SIZE;
                        e->estado = 1;
                        objetivo = true;
                    }
                }
            }   
        }

        else if(e->estado == 1 || e->estado == 2 || e->estado == 3)
        {
            float vel_actual;
            if(e->estado == 3)
            {
                vel_actual = VELOCIDAD_BUSQUEDA;
            }
            else
            {
                vel_actual = e->velocidad;
            }
            float dir_x = e->target_x - e->posx;
            float dir_y = e->target_y - e->posy;
            float distancia_al_target = sqrt(dir_x*dir_x + dir_y*dir_y);

            if(distancia_al_target < vel_actual)
            {
                e->posx = e->target_x;
                e->posy = e->target_y;
                e->estado = 0;
                e->espera = 60;
                return;
            }

            float nueva_posx = e->posx + (dir_x / distancia_al_target) * vel_actual;
            float nueva_posy = e->posy + (dir_y / distancia_al_target) * vel_actual;

            e->angulo = atan2(dir_y, dir_x);

            int fila_sup = (nueva_posy + 10) / TILE_SIZE;
            int fila_inf = (nueva_posy + e->alto - 10) / TILE_SIZE;
            int col_izq = (nueva_posx + 10) / TILE_SIZE;
            int col_der = (nueva_posx + e->ancho - 10) / TILE_SIZE;
        
            bool chocar = false;
            for(int f = fila_sup; f <= fila_inf && !chocar; f++)
            {
                for(int c = col_izq; c<= col_der && !chocar; c++)
                {
                    if(f >= 0 && f < MAPA_FILAS && c >= 0 && c < MAPA_COLUMNAS)
                    {
                        if(colision(mapa[f][c]))
                        {
                            chocar = true;
                        }
                    }
                }
            }

            if(chocar)
            {
                e->estado = 0;
                e->espera = 60;
            }
            else
            {
                e->posx = nueva_posx;
                e->posy = nueva_posy;
            }
        }
    }
    //----------------ENEMIGO 3--------------//
    else if(e->tipo == 3)
    {
        bool ver_jugador_camper = (distancia_total <= (RANGO_VISION_ENEMIGO * 3) * TILE_SIZE) && linea_de_vision(e,p,mapa);

        if(ver_jugador_camper)
        {
            e->estado =2;
            e->target_x= centro_jugadorx;
            e->target_y = centro_jugadory;
            e->angulo = atan2(distanciay, distanciax);
        }
        else
        {
            e->estado = 0;
        }
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