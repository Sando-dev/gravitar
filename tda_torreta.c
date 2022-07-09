#include <stdbool.h>
#include <stdlib.h>
#include "tda_torreta.h"

typedef struct torreta torreta_t;

struct torreta{
  double posx;
  double posy;
  double ang;
  bool activa; //?
  bool viva; //?
  //nivel??
};

typedef struct torreta torreta_t;

torreta_t *torreta_crear(double posx, double posy, double angulo){
  torreta_t *torreta=malloc(sizeof(torreta_t));
  if(torreta==NULL){
    return NULL;
  }
  torreta->posx=posx;
  torreta->posy=posy;
  torreta->ang=angulo;
  torreta->activa=false;
  torreta->viva=true;
  return torreta;
}

void torreta_destruir(torreta_t *torreta){
  free(torreta);
}

void torreta_activar(torreta_t *torreta){
  torreta->activa=true;
}

void torreta_desactivar(torreta_t *torreta){
  torreta->activa=false;
}

void torreta_matar(torreta_t *torreta){
  torreta->viva=false;
}
