#include <stdlib.h>

#include "tda_polilineas.h"
#include "tda_fisicaymatematica.h"
#include "tda_figuras.h"

struct nave{
  polilinea_t **polilineas;
  size_t cantpol;
  int vidas;
  int combustible;
  double posx;
  double posy;
  double angulo;
};

typedef struct nave nave_t;

void nave_destruir(nave_t nave, size_t i, void (*destruir)(polilinea_t*)){
  for(size_t j=0;j<i;j++){
    destruir(nave->polilineas[i]);
  }
  free(nave);
}

nave_t *nave_crear(polilinea_t **polilineas, size_t cant_pol){
  nave_t *nave=malloc(sizeof(nave_t));
  if(nave==NULL){
    return NULL;
  }
  nave->polilineas=malloc(cant_pol*sizeof(polilinea_t *));
  if(nave->polilineas==NULL){
    return NULL;
  }
  for(size_t i=0;i<cant_pol;i++){
    nave->polilineas[i]=polilinea_clonar(polilineas[i]);
    if(nave->polilineas[i]){
      nave_destruir();
      return NULL;
    }
  }
  return nave;
}

float *nave_mover(){

}

float *nave_matar(){

}
