#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "polilinea.h"

struct polilinea {
    float (*puntos)[2];
    size_t n;
};

void polilinea_destruir(polilinea_t *polilinea){
  free(polilinea->puntos);
  free(polilinea);
}

polilinea_t *polilinea_crear_vacia(size_t n){
  polilinea_t *polilinea=malloc(sizeof(polilinea_t));
  if(polilinea==NULL){
    return NULL;
  }
  polilinea->n=n;
  polilinea->puntos=malloc(n*sizeof(float [2]));
  if(polilinea->puntos==NULL){
    free(polilinea);
    return NULL;
  }
  return polilinea;
}

polilinea_t *polilinea_crear(const float puntos[][2], size_t n){
  polilinea_t *polilinea=polilinea_crear_vacia(n);
  if(polilinea==NULL){
    return NULL;
  }
  memcpy(polilinea->puntos,puntos,n*sizeof(float[2]));
  return polilinea;
}

size_t polilinea_cantidad_puntos(const polilinea_t *polilinea){
  return polilinea->n;
}

bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y){
  if(pos>((polilinea->n)-1)){
    return false;
  }
  *x=polilinea->puntos[pos][0];
  *y=polilinea->puntos[pos][1];
  return true;
}

bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y){
  if(pos>((polilinea->n)-1)){
    return false;
  }
  polilinea->puntos[pos][0]=x;
  polilinea->puntos[pos][1]=y;
  return true;
}

polilinea_t *polilinea_clonar(const polilinea_t *polilinea){
  return polilinea_crear((const float (*)[2])polilinea->puntos,polilinea->n);
}


/* double distancia_punto_a_polilinea(const float polilinea[][2], size_t n, float px, float py){
  //double dist[n-1];
  double distmin=1000;
  for(int i=0;i<n-1;i++){
    double dist;
    double alf=alfa(px,py,polilinea[i][0],polilinea[i][1],polilinea[i+1][0],polilinea[i+1][1]);
    if(alf<=0){
      //dist[i]=norma(px-polilinea[i][0],py-polilinea[i][1]);
      dist=norma(px-polilinea[i][0],py-polilinea[i][1]);
    }
    else if(alf>=1){
      //dist[i]=norma(px-polilinea[i+1][0],py-polilinea[i+1][1]);
      dist=norma(px-polilinea[i+1][0],py-polilinea[i+1][1]);
    }
    else{
      double cx=punto_del_segmento(polilinea[i][0],polilinea[i+1][0],alf);
      double cy=punto_del_segmento(polilinea[i][1],polilinea[i+1][1],alf);
      //dist[i]=norma(px-cx,py-cy);
      dist=norma(px-cx,py-cy);
    }
    if(dist<=distmin){
      distmin=dist;
    }
  }
  //return distancia_minima(dist,n-1);
  return distmin;
}*/

void trasladar(float polilinea[][2], size_t n, float dx, float dy){
  for(int i=0;i<n;i++){
    polilinea[i][0]+=dx;
    polilinea[i][1]+=dy;
  }
}

void rotar(float polilinea[][2], size_t n, double rad){
  double co=cos(rad);
  double si=sin(rad);
  for(int i=0;i<n;i++){
    float xp=polilinea[i][0]*co-polilinea[i][1]*si;
    float yp=polilinea[i][0]*si+polilinea[i][1]*co;
    polilinea[i][0]=xp;
    polilinea[i][1]=yp;
  }
}
