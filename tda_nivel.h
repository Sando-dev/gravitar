#ifndef NIVEL_H
#define NIVEL_H

#include "tda_polilineas.h"

typedef struct nivel nivel_t;

#define TAMANIO_NOMBRE 20

//PRE: recibe nombre del nivel y un booleano si es infinito
//POST: crea nivel, devuelve NULL en caso de error
nivel_t *nivel_crear(char *nombre, bool inf);

//destruye nivel
void nivel_destruir(nivel_t *nivel);


char *nivel_nombre(nivel_t *nivel);
size_t nivel_buscar(nivel_t **n_vector, size_t n_n, char nombre[TAMANIO_NOMBRE]);

//PRE: nivel ya fue creado
//POST: activa o desactiva el estado del nivel
void nivel_activar(nivel_t *nivel);
void nivel_desactivar(nivel_t *nivel);

//PRE: nivel ya fue creado
//POST: devuelve booleano si el nivel esta activo o no
bool nivel_esta_activo(nivel_t *nivel);

//PRE: nivel ya fue creado
//POST: devuelve booleano si el nivel es infinito o no
bool nivel_return_inf(nivel_t *nivel);

void nivel_set_escala_inicial(nivel_t *nivel, float f);

float nivel_return_escala_inicial(nivel_t *nivel);

float nivel_calcular_escala(polilinea_t **p, size_t n, bool inf, float nave_pos_y,double *ancho);

#endif
