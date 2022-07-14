#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tda_nivel.h"

struct nivel{
  char nombre[TAMANIO_NOMBRE];
  bool activo;
  bool infinito;
  int puntos;
};


nivel_t *nivel_crear(char nombre[], bool inf){
  nivel_t *nivel=malloc(sizeof(nivel_t));
  if(nivel==NULL){
    return NULL;
  }
  strcpy(nivel->nombre,nombre);
  nivel->activo=false;
  nivel->infinito = inf;
  //nivel->puntos=0;
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