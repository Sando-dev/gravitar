#ifndef ENCABEZADO_H
#define ENCABEZADO_H

#include "tda_polilineas.h"

#define MAX_STRING 20

typedef struct encabezado encabezado_t; 

encabezado_t *encabezado_crear(void);

void encabezado_destruir(encabezado_t *e);

void encabezado_graficar(encabezado_t *e, SDL_Renderer *renderer);

void encabezado_set_fuel(encabezado_t *e, int fuel);

void encabezado_torreta_matada(encabezado_t *e);

void encabezado_nivel_completado(encabezado_t *e, char level[MAX_STRING]);

#endif