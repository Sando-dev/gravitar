#include <stdbool.h>
#include <stdlib.h>
#include "tda_disparos.h"
#include "tda_fisicaymatematica.h"
#include "config.h"

struct disparo{
  bool vive;
  double tiempo;
  double posx;
  double posy;
  double vx;
  double vy;
  double angulo;
};

typedef struct disparo disparo_t;

disparo_t *crear_disparo(double x, double y, double vx, double vy, double angulo){
  disparo_t *disparo=malloc(sizeof(disparo_t));
  if(disparo==NULL){
    return NULL;
  }
  disparo->vive=true;
  disparo->tiempo=0;
  disparo->posx=x;
  disparo->posy=y;
  disparo->vx=vx;
  disparo->vy=vy;
  disparo->angulo=angulo;
  return disparo;
}

void disparo_destruir(disparo_t *disparo){
  free(disparo);
}

void disparo_mover(disparo_t *disparo){
  disparo->posx=computar_posicion(disparo->posx, disparo->vx, (float)1/JUEGO_FPS);
  disparo->posy=computar_posicion(disparo->posy, disparo->vy, (float)1/JUEGO_FPS);
  disparo->tiempo+=(float)1/JUEGO_FPS;
}

double disparo_get_posx(disparo_t *disparo){
  return disparo->posx;
}

double disparo_get_posy(disparo_t *disparo){
  return disparo->posy;
}

double disparo_get_angulo(disparo_t *disparo){
  return disparo->angulo;
}

double disparo_tiempo(disparo_t *disparo){
  return disparo->tiempo;
}
