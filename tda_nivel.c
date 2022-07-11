#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tda_nivel.h"

struct nivel{
  bool activo;
  int puntos;
};


nivel_t *crear_nivel(){
  nivel_t *nivel=malloc(sizeof(nivel_t));
  if(nivel==NULL){
    return NULL;
  }
  nivel->activo=false;
  //nivel->puntos=0;
  return nivel;
}

void nivel_destruir(nivel_t *nivel){
  free(nivel);
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
