#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tda_torreta.h"
#include "config.h"


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
  bool alive;
  bool reactor;
  char level[MAX_LVL];
};

struct reactor {
  double posicion_x;
  double posicion_y;
  double angulo;
  bool alive;
  double tiempo;
};


torreta_diccionario_t torretas[] = {
  {916,75,-0.66,1,0,"NIVEL1NE"},
  {1425,159,0.66,1,0,"NIVEL1NE"},
  {423,195,-0.66,1,0,"NIVEL1SE"},
  {806,215,-0.33,1,0,"NIVEL1SE"},
  {1254,153,0.66,1,0,"NIVEL1SE"},
  {1587,223,2.23,1,0,"NIVEL1SE"},
  {70,46,0,1,0,"NIVEL1SW"},
  {506,12,0,1,0,"NIVEL1SW"},
  {952,12,0,1,0,"NIVEL1SW"},
  {1385,12,0,1,0,"NIVEL1SW"},
  {757,210,3.14,1,0,"NIVEL1SW"},
  {1161,210,3.14,1,0,"NIVEL1SW"},
  {257,440,0.66,1,0,"NIVEL1NW"},
  {719,674,2.23,1,0,"NIVEL1NW"},
  {985,565,0,1,0,"NIVEL1NW"},
  {1125,417,3.8,1,0,"NIVEL1NW"},
  {862,163,3.8,1,0,"NIVEL1NW"},
  {626,323,2.23,1,0,"NIVEL1NW"},
  {505,331,3.8,1,0,"NIVEL1NW"},
  {378,296,2.23,1,0,"NIVEL1NW"},
  {815,309,0,1,1,"NIVEL1R"}
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
    if((!(strcmp(nivel,torretas[i].level))) && torretas[i].alive && (!(torretas[i].reactor))){
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

bool torreta_vive(torreta_t *torreta){
  return torreta->alive;
}


void torreta_diccionario_matar(float posicion_x, float posicion_y, char nivel[MAX_LVL]){
  size_t cantidad = sizeof(torretas) / sizeof(torretas[0]);
  for(size_t i=0; i<cantidad; i++){
    if(posicion_x == torretas[i].posicion_x && posicion_y == torretas[i].posicion_y && !strcmp(nivel, torretas[i].level)){
      torretas[i].alive = 0;
      break;
    } 
  }
}

reactor_t **reactor_activar(char nivel[MAX_LVL], size_t *n) {
  reactor_t **reactores_vector = malloc(sizeof(reactor_t*));
  if(reactores_vector == NULL) 
    return NULL;
  size_t cantidad = sizeof(torretas) / sizeof(torretas[0]);
  size_t j = 0;
  for(size_t i=0; i<cantidad; i++){
    if((!(strcmp(nivel,torretas[i].level))) && torretas[i].alive && torretas[i].reactor){
      reactor_t **aux = realloc(reactores_vector, (i+1)*sizeof(reactor_t*));
      if(aux == NULL) {
        reactor_vector_destruir(reactores_vector,i);
        return NULL;
      }
      reactores_vector = aux;
      reactor_t *t = reactor_crear(torretas[i].posicion_x,torretas[i].posicion_y,torretas[i].angulo);
      reactores_vector[j++] =t;

    }
  }
  *n = j;
  return reactores_vector;
}

reactor_t *reactor_crear(double posx, double posy, double angulo){
  reactor_t *reactor=malloc(sizeof(reactor_t));
  if(reactor==NULL){
    return NULL;
  }
  reactor->posicion_x=posx;
  reactor->posicion_y=posy;
  reactor->angulo=angulo;
  reactor->alive=true;
  reactor->tiempo = 0;
  return reactor;
}

bool reactor_explotar(reactor_t *r) {
  if(r->tiempo >= 25)
    return true;
  return false;
}

void reactor_pasa_tiempo(reactor_t *r) {
  r->tiempo +=(float)1/JUEGO_FPS;
}

void reactor_vector_destruir(reactor_t **r, size_t n) {
  for(size_t i=0; i<n; i++)
    free(r[i]);
  free(r);
}

bool reactor_get_alive(reactor_t *r) {
  return r->alive;
}

float reactor_get_posy(reactor_t *r) {
  return r->posicion_x;
}

float reactor_get_posx(reactor_t *r) {
  return r->posicion_y;
}

float reactor_get_angulo(reactor_t *r) {
  return r->angulo;
}