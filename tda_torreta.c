#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tda_torreta.h"


struct torreta {
  double posicion_x;
  double posicion_y;
  double angulo;
  bool alive;
};

struct torreta_diccionario{
  double posicion_x;
  double posicion_y;
  double angulo;
  char level[MAX_LVL];
};


const torreta_diccionario_t torretas[20] = {
  {916,75,-0.66,"NIVEL1NE"},
  {1425,159,0.66,"NIVEL1NE"},
  {423,195,-0.66,"NIVEL1SE"},
  {806,215,-0.33,"NIVEL1SE"},
  {1254,153,0.66,"NIVEL1SE"},
  {1587,223,2.23,"NIVEL1SE"},
  {70,46,0,"NIVEL1SW"},
  {506,12,0,"NIVEL1SW"},
  {952,12,0,"NIVEL1SW"},
  {1385,12,0,"NIVEL1SW"},
  {757,210,3.14,"NIVEL1SW"},
  {1161,210,3.14,"NIVEL1SW"},
  {257,440,0.66,"NIVEL1NW"},
  {719,674,2.23,"NIVEL1NW"},
  {985,565,0,"NIVEL1NW"},
  {1125,417,3.8,"NIVEL1NW"},
  {862,163,3.8,"NIVEL1NW"},
  {626,323,2.23,"NIVEL1NW"},
  {505,331,3.8,"NIVEL1NW"},
  {378,296,2.23,"NIVEL1NW"}
};

torreta_t *torreta_crear(double posx, double posy, double angulo){
  torreta_t *torreta=malloc(sizeof(torreta_t));
  if(torreta==NULL){
    return NULL;
  }
  torreta->posicion_x=posx;
  torreta->posicion_y=posy;
  torreta->angulo=angulo;
  torreta->alive=true;
  return torreta;
}

void torreta_destruir(torreta_t *torreta){
  free(torreta);
}

void torreta_matar(void *torreta){
  ((torreta_t *)torreta)->alive=false;
}

torreta_t **torretas_activar(char nivel[MAX_LVL], size_t *n){
  torreta_t **torretas_vector = malloc(sizeof(torreta_t*));
  if(torretas_vector == NULL) 
    return NULL;
  size_t cantidad = sizeof(torretas) / sizeof(torretas[0]);
  size_t j = 0;
  for(size_t i=0; i<cantidad; i++){
    if(!(strcmp(nivel,torretas[i].level))){
      torreta_t **aux = realloc(torretas_vector, (i+1)*sizeof(torreta_t*));
      if(aux == NULL) {
        torreta_vector_destruir(torretas_vector,i);
        return NULL;
      }
      torretas_vector = aux;
      torreta_t *t = torreta_crear(torretas[i].posicion_x,torretas[i].posicion_y,torretas[i].angulo);
      torretas_vector[j++] =t;

    }
  }
  *n = j;
  return torretas_vector;
}

void torreta_vector_destruir(torreta_t **t, size_t n) {
  for(size_t i=0; i<n; i++)
    torreta_destruir(t[i]);
  free(t);
}

float torreta_get_posx(torreta_t *t){
  return t->posicion_x;
}

float torreta_get_posy(torreta_t *t) {
  return t->posicion_y;
}

float torreta_get_angulo(torreta_t *t) {
  return t->angulo;
}