#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "tda_fisicaymatematica.h"
#include "tda_nave.h"
#include "config.h"

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



nave_t *nave_crear(double px_inicial, double py_inicial){
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
  nave->angulo=NAVE_ANGULO_INICIAL;
  return nave;
}

void nave_destruir(nave_t *nave){
  free(nave);
}

void nave_matar(nave_t *nave, double px_inicial, double py_inicial){
  nave->vidas--;
  nave->chorro=false;
  nave->escudo=false;
  nave->vx=0;
  nave->vy=0;
  nave->posx=px_inicial;
  nave->posy=py_inicial;
  nave->angulo=NAVE_ANGULO_INICIAL;
}

void nave_trasladar(nave_t *nave, double px_inicial, double py_inicial,bool resetear){
  nave->chorro=false;
  nave->escudo=false;
  if(resetear){
    nave->chorro=false;
    nave->escudo=false;
    nave->vx=0;
    nave->vy=0;
    nave->angulo=NAVE_ANGULO_INICIAL;
  }
  nave->posx=px_inicial;
  nave->posy=py_inicial;
}

void nave_prender_chorro(nave_t *nave){
  nave->combustible-=JUEGO_COMBUSTIBLE_POT_X_SEG*((float)1/JUEGO_FPS);
  nave->chorro=true;
}

void nave_apagar_chorro(nave_t *nave){
  nave->chorro=false;
}

void nave_prender_escudo(nave_t *nave){
  nave->combustible-=JUEGO_COMBUSTIBLE_ESC_X_SEG*((float)1/JUEGO_FPS);
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

void nave_mover(nave_t *nave, double a, double angulo,double angulo_estrella){
  nave->angulo+=angulo;
  nave->vx=computar_velocidad(nave->vx,a*cos(nave->angulo)+G*cos(angulo_estrella),(float)1/JUEGO_FPS);
  nave->vy=computar_velocidad(nave->vy,a*sin(nave->angulo)+G*sin(angulo_estrella),(float)1/JUEGO_FPS);
  nave->posx=computar_posicion(nave->posx, nave->vx, (float)1/JUEGO_FPS);
  nave->posy=computar_posicion(nave->posy, nave->vy, (float)1/JUEGO_FPS);
}

void nave_rebotar_x(nave_t *nave){
  nave->vx=(-nave->vx);
}

void nave_rebotar_y(nave_t *nave){
  nave->vy=(-nave->vy);
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

int nave_get_vidas(nave_t *nave){
  return nave->vidas;
}
