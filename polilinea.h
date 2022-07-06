#ifndef POLILINEA_H
#define POLILINEA_H

#include <stdio.h>
#include <stdbool.h>

typedef struct polilinea polilinea_t;

// Ejercicio 3
polilinea_t *polilinea_crear_vacia(size_t n);
polilinea_t *polilinea_crear(const float puntos[][2], size_t n);
void polilinea_destruir(polilinea_t *polilinea);
polilinea_t *polilinea_clonar(const polilinea_t *polilinea);

size_t polilinea_cantidad_puntos(const polilinea_t *polilinea);
bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y);
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);


// Ejercicio 2 - no usan el dato polilinea_t
double distancia_punto_a_polilinea(const float polilinea[][2], size_t n, float px, float py);
void rotar(float polilinea[][2], size_t n, double rad);
void trasladar(float polilinea[][2], size_t n, float dx, float dy);


#endif