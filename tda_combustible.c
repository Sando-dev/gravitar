#include <stdlib.h>
#include <stdbool.h>
#include "tda_combustible.h"

struct combustible{
  bool vive;
  bool activa;
  int combustible;
  double posx;
  double posy;
  double angulo;
};



combustible_t *combustible_crear(double posx, double posy, double ang){
  combustible_t *combustible=malloc(sizeof(combustible_t));
  if(combustible==NULL){
    return NULL;
  }
  combustible->vive=true;
  combustible->activa=false;
  combustible->combustible=3000;
  combustible->posx=posx;
  combustible->posy=posy;
  combustible->angulo=ang;
  return combustible;
}

void combustible_eliminar(combustible_t *comb){
  free(comb);
}

double combustible_posx(combustible_t *comb){
  return comb->posx;
}

double combustible_posy(combustible_t *comb){
  return comb->posy;
}

double combustible_angulo(combustible_t *comb){
  return comb->angulo;
}

void combustible_matar(combustible_t *comb){
  comb->vive=false;
  comb->combustible=0;
}
