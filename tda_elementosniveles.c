#include <stdbool.h>
#include <stdlib.h>
#include "tda_elementosniveles.h"


struct elementos_niveles{
  double posx;
  double posy;
  double ang;
  bool viva;
  bool torreta;
  bool combustible;
};



elementos_niveles_t *elementos_niveles_crear(double posx, double posy, double angulo){
  elementos_niveles_t *elementos_niveles=malloc(sizeof(elementos_niveles_t));
  if(elementos_niveles==NULL){
    return NULL;
  }
  elementos_niveles->posx=posx;
  elementos_niveles->posy=posy;
  elementos_niveles->ang=angulo;
  elementos_niveles->viva=true;
  return elementos_niveles;
}

void elementos_niveles_matar(void *elementos_niveles){
  ((elementos_niveles_t *)elementos_niveles)->viva=false;
}

bool elementos_niveles_esta_vivo(void *elementos_niveles, void *extra){
  return ((elementos_niveles_t *)elementos_niveles)->viva;
}

bool elementos_niveles_es_torreta(void *elementos_niveles, void *extra){
  return ((elementos_niveles_t *)elementos_niveles)->torreta;
}

bool elementos_niveles_es_combustible(void *elementos_niveles, void *extra){
  return ((elementos_niveles_t *)elementos_niveles)->combustible;
}

double elementos_niveles_posx(elementos_niveles_t *elementos_niveles){
  return elementos_niveles->posx;
}

double elementos_niveles_posy(elementos_niveles_t *elementos_niveles){
  return elementos_niveles->posy;
}

double elementos_niveles_angulo(elementos_niveles_t *elementos_niveles){
  return elementos_niveles->ang;
}
