#ifndef NIVEL_H
#define NIVEL_H

#include "tda_polilineas.h"

typedef struct nivel nivel_t;

#define TAMANIO_NOMBRE 20

nivel_t *nivel_crear(char *nombre, bool inf);
void nivel_destruir(nivel_t *nivel);

char *nivel_nombre(nivel_t *nivel);
size_t nivel_buscar(nivel_t **n_vector, size_t n_n, char nombre[TAMANIO_NOMBRE]);

void nivel_activar(nivel_t *nivel);
void nivel_desactivar(nivel_t *nivel);

bool nivel_esta_activo(nivel_t *nivel);

bool nivel_return_inf(nivel_t *nivel);

void nivel_set_escala_inicial(nivel_t *nivel, float f);

float nivel_return_escala_inicial(nivel_t *nivel);

float nivel_calcular_escala(polilinea_t **p, size_t n, bool inf, float nave_pos_y,double *ancho);

#endif
