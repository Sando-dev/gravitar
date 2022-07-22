#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "tda_nivel.h"
#include "config.h"

struct nivel{
  char nombre[TAMANIO_NOMBRE];
  bool activo;
  bool infinito;
  float escala_inicial;
};


nivel_t *nivel_crear(char nombre[], bool inf){
  nivel_t *nivel=malloc(sizeof(nivel_t));
  if(nivel==NULL){
    return NULL;
  }
  strcpy(nivel->nombre,nombre);
  nivel->activo=false;
  nivel->infinito = inf;
  return nivel;
}

void nivel_destruir(nivel_t *nivel){
  free(nivel);
}

char *nivel_nombre(nivel_t *nivel){
  return nivel->nombre;
}

size_t nivel_buscar(nivel_t **n_vector, size_t n_n, char nombre[TAMANIO_NOMBRE]){
  size_t n;
  for(size_t i=0; i<n_n; i++){
    if(!(strcmp(n_vector[i]->nombre,nombre)))
      n=i;
  }
  return n;
}

void nivel_activar(nivel_t *nivel){
  nivel->activo=true;
}

void nivel_desactivar(nivel_t *nivel){
  nivel->activo=false;
}

bool nivel_esta_activo(nivel_t *nivel){
  return nivel->activo;
}

bool nivel_return_inf(nivel_t *nivel) {
  return nivel->infinito;
}

void nivel_set_escala_inicial(nivel_t *nivel, float f) {
  nivel->escala_inicial = f;
}

float nivel_return_escala_inicial(nivel_t *nivel) {
  return nivel->escala_inicial;
}

float nivel_calcular_escala(polilinea_t **p, size_t n, bool inf, float nave_pos_y,double *ancho){
  float f = 1;
  float x_max = 0;
  float y_max = 0;
  float x_min = VENTANA_ANCHO*100;
  for(size_t i=0; i<n; i++){
    if(x_max < polilinea_buscar_xmax(p[i]))
      x_max = polilinea_buscar_xmax(p[i]);
    if(x_min > polilinea_buscar_xmin(p[i]))
      x_min = polilinea_buscar_xmin(p[i]);
    if(y_max < polilinea_buscar_ymax(p[i]))
      y_max = polilinea_buscar_ymax(p[i]);
  }
  *ancho=x_max-x_min;
  if(inf) {
    if(nave_pos_y > VENTANA_ALTO * MARGEN_ALTURA)
      f = VENTANA_ALTO * MARGEN_ALTURA / nave_pos_y;
    if(f < ESCALA_MINIMA)
      f = ESCALA_MINIMA;
  }
  else{
    f = VENTANA_ALTO / y_max;
    if(VENTANA_ANCHO / (x_max + x_min) < f)
      f = VENTANA_ANCHO / (x_max + x_min);
  }
  return f;
}
