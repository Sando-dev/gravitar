#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
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



disparo_t *crear_disparo(double x, double y, double angulo){
  disparo_t *disparo=malloc(sizeof(disparo_t));
  if(disparo==NULL){
    return NULL;
  }
  disparo->vive=true;
  disparo->tiempo=0;
  disparo->posx=x;
  disparo->posy=y;
  disparo->vx=5*cos(angulo);
  disparo->vx=5*sin(angulo);
  disparo->angulo=angulo;
  return disparo;
}



bool disparo_mover(void *disparo, void *extra){
  ((disparo_t*)disparo)->posx=computar_posicion(((disparo_t*)disparo)->posx, ((disparo_t*)disparo)->vx, (float)1/JUEGO_FPS);
  ((disparo_t*)disparo)->posy=computar_posicion(((disparo_t*)disparo)->posy, ((disparo_t*)disparo)->vy, (float)1/JUEGO_FPS);
  ((disparo_t*)disparo)->tiempo+=(float)1/JUEGO_FPS;
  return true;
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

double disparo_tiempo_comparar(void *disparo, double t){
  return ((disparo_t*)disparo)->tiempo - t;
}
