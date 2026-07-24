#ifndef ARMAS_H
#define ARMAS_H

#include <stdbool.h>

typedef enum {
    PISTOLA,
    CUCHILLO
}tipo_arma;

typedef struct {
    tipo_arma tipo;
    int municion;
    int capacidad_cargador;
    int reserva;
    bool recargando;
    int tiempo_recarga_actual;
    int tiempo_recarga_total;
}arma;



#endif