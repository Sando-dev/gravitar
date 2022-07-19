#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "tda_fuel.h"


struct fuel {
    double posicion_x;
    double posicion_y;
    double angulo;
    bool taken;
};

struct fuel_diccionario {
    double posicion_x;
    double posicion_y;
    double angulo;
    char level[MAX_LVL];
};

const fuel_diccionario_t fuels[] = {
    {1064,13,0,"NIVEL1NE"},
    {1685,113,0,"NIVEL1NE"},
    {482,94,0,"NIVEL1SE"},
    {1751,247,0,"NIVEL1SE"},
    {820,46,0,"NIVEL1SW"},
    {1196,68,0,"NIVEL1SW"},
    {1602,46,0,"NIVEL1SW"},
    {188,429,0,"NIVEL1NW"},
    {667,600,0,"NIVEL1NW"},
    {1054,404,3.14,"NIVEL1NW"},
    {574,344,3.14,"NIVEL1NW"}
};

fuel_t *fuel_crear(double posx, double posy, double angulo){
  fuel_t *fuel=malloc(sizeof(fuel_t));
  if(fuel==NULL){
    return NULL;
  }
  fuel->posicion_x=posx;
  fuel->posicion_y=posy;
  fuel->angulo=angulo;
  fuel->taken=true;
  return fuel;
}

void fuel_destruir(fuel_t *fuel){
  free(fuel);
}


fuel_t **fuel_activar(char nivel[MAX_LVL], size_t *n){
  fuel_t **fuel_vector = malloc(sizeof(fuel_t*));
  if(fuel_vector == NULL) 
    return NULL;
  size_t cantidad = sizeof(fuels) / sizeof(fuels[0]);
  size_t j = 0;
  for(size_t i=0; i<cantidad; i++){
    if(!(strcmp(nivel,fuels[i].level))){
      fuel_t **aux = realloc(fuel_vector, (i+1)*sizeof(fuel_t*));
      if(aux == NULL) {
        fuel_vector_destruir(fuel_vector,i);
        return NULL;
      }
      fuel_vector = aux;
      fuel_t *f = fuel_crear(fuels[i].posicion_x,fuels[i].posicion_y,fuels[i].angulo);
      fuel_vector[j++] =f;

    }
  }
  *n = j;
  return fuel_vector;
}

void fuel_vector_destruir(fuel_t **t, size_t n) {
  for(size_t i=0; i<n; i++)
    fuel_destruir(t[i]);
  free(t);
}

float fuel_get_ang(fuel_t *f) {
    return f->angulo;
}

float fuel_get_posy(fuel_t *f) {
    return f->posicion_y;
}

float fuel_get_posx(fuel_t *f) {
    return f->posicion_x;
}