#include <stdbool.h>
#include <stdlib.h>
#include "tda_fisicaymatematica.h"


struct nave{
  bool chorro;
  bool escudo;
  int vidas;
  int combustible;
  double posx;
  double posy;
  double vx;
  double vy;
  double angulo;
};

typedef struct nave nave_t;

nave_t *nave_crear(double px_inicial, double py_inicial, double angulo_inicial){
  nave_t *nave=malloc(sizeof(nave_t));
  if(nave==NULL){
    return NULL;
  }
  nave->chorro=false;
  nave->escudo=false;
  nave->vidas=3;
  nave->combustible=10000;
  nave->vx=0;
  nave->vy=0;
  nave->posx=px_inicial;
  nave->posy=py_inicial;
  nave->angulo=angulo_inicial;
  return nave;
}

void nave_destruir(nave_t *nave){
  free(nave);
}

void nave_matar(nave_t *nave, double px_inicial, double py_inicial, double angulo_inicial){
  nave->vidas--;
  nave->chorro=false;
  nave->escudo=false;
  nave->vx=0;
  nave->vy=0;
  nave->posx=px_inicial;
  nave->posy=py_inicial;
  nave->angulo=angulo_inicial;
}

void nave_prender_chorro(nave_t *nave, double gasto){
  nave->combustible-=gasto;
  nave->chorro=true;
}

void nave_apagar_chorro(nave_t *nave){
  nave->chorro=false;
}

void nave_prender_escudo(nave_t *nave, double gasto){
  nave->combustible-=gasto;
  nave->escudo=true;
}

void nave_apagar_escudo(nave_t *nave){
  nave->escudo=false;
}

bool nave_chorro_esta_prendido(nave_t *nave){
  return nave->chorro;
}

bool nave_escudo_esta_prendido(nave_t *nave){
  return nave->escudo;
}

void nave_mover(nave_t *nave, double ax,double ay, double dt, double angulo){
  nave->vx=computar_velocidad(nave->vx,ax,dt);
  nave->vy=computar_velocidad(nave->vx,ax,dt);
  nave->posx=computar_posicion(nave->posx, nave->vx, dt);
  nave->posy=computar_posicion(nave->posy, nave->vy, dt);
  nave->angulo+=angulo;
}


double nave_get_posx(nave_t *nave){
  return nave->posx;
}

double nave_get_posy(nave_t *nave){
  return nave->posy;
}

double nave_get_angulo(nave_t *nave){
  return nave->angulo;
}
