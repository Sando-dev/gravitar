#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "tda_polilineas.h"
#include "config.h"
#include "tda_fisicaymatematica.h"

#define MSK_ROJO 0x04
#define MSK_VERDE 0x02
#define MSK_AZUL 0x01
#define SHIFT_ROJO 2
#define SHIFT_VERDE 1
#define SHIFT_COLOR 13

#define MSK_CANT_PUNTOS 0x3FF

struct polilinea{
  float (*puntos)[2];
  size_t n;
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

uint8_t polilinea_get_red(polilinea_t *p) {
  return p->r;
}

uint8_t polilinea_get_green(polilinea_t *p) {
  return p->g;
}

uint8_t polilinea_get_blue(polilinea_t *p) {
  return p->b;
}



/*libera la memoria de la polilina*/
void polilinea_destruir(polilinea_t *polilinea){
  free(polilinea->puntos);
  free(polilinea);
}

/*recibe entero positivo n y crea una polilinea
vacia de tamaño n. NULL si hay error en la memoria*/
static polilinea_t *polilinea_crear_vacia(size_t n){
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

/*recibe matriz dinamica y tamaño, crea completa la polilinea*/
polilinea_t *polilinea_crear(const float puntos[][2], size_t n, uint8_t r, uint8_t g, uint8_t b){
  polilinea_t *polilinea=polilinea_crear_vacia(n);
  if(polilinea==NULL){
    return NULL;
  }
  memcpy(polilinea->puntos,puntos,n*sizeof(float[2]));
  polilinea->r=r;
  polilinea->g=g;
  polilinea->b=b;
  return polilinea;
}
/*recibe polilinea, devuelve n*/
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
  return polilinea_crear((const float (*)[2])polilinea->puntos,polilinea->n,polilinea->r,polilinea->g,polilinea->b);
}


static color_t color_crear(bool r, bool g, bool b){
  return (r<<SHIFT_ROJO) | (g<<SHIFT_VERDE) | b;
}

static void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b){
  *r= ((c&MSK_ROJO)>>SHIFT_ROJO)*255;
  *g= ((c&MSK_VERDE)>>SHIFT_VERDE)*255;
  *b= (c&MSK_AZUL)*255;
}


bool polilinea_setear_color(polilinea_t *polilinea, color_t color) {
    color_a_rgb(color, &(polilinea->r), &(polilinea->g), &(polilinea->b));
    return true;
}

polilinea_t *leer_polilinea(FILE *f){
  uint16_t encabezado;
  if(fread(&encabezado,sizeof(uint16_t),1,f)!=1){
    return NULL;
  }

  size_t cant_puntos=(encabezado)&MSK_CANT_PUNTOS;
  polilinea_t *p=polilinea_crear_vacia(cant_puntos);
  if(p==NULL){
    return NULL;
  }

  color_t color=color_crear((encabezado)&(MSK_ROJO<<SHIFT_COLOR),(encabezado)&(MSK_VERDE<<SHIFT_COLOR),(encabezado)&(MSK_AZUL<<SHIFT_COLOR));
  polilinea_setear_color(p,color);

  for(size_t i=0;i<cant_puntos;i++){
    float v[2];

    if(fread(v,sizeof(float),2,f)!=2){
      polilinea_destruir(p);
      return NULL;
    }
    polilinea_setear_punto(p,i,v[0],v[1]);
  }
  return p;
}

double distancia_punto_a_polilinea(polilinea_t *polilinea, float px, float py){
  //double dist[n-1];
  double distmin=1000;
  for(int i=0;i<polilinea->n-1;i++){
    double dist;
    double alf=alfa(px,py,polilinea->puntos[i][0],polilinea->puntos[i][1],polilinea->puntos[i+1][0],polilinea->puntos[i+1][1]);
    if(alf<=0){
      //dist[i]=norma(px-polilinea[i][0],py-polilinea[i][1]);
      dist=norma(px-polilinea->puntos[i][0],py-polilinea->puntos[i][1]);
    }
    else if(alf>=1){
      //dist[i]=norma(px-polilinea[i+1][0],py-polilinea[i+1][1]);
      dist=norma(px-polilinea->puntos[i+1][0],py-polilinea->puntos[i+1][1]);
    }
    else{
      double cx=punto_del_segmento(polilinea->puntos[i][0],polilinea->puntos[i+1][0],alf);
      double cy=punto_del_segmento(polilinea->puntos[i][1],polilinea->puntos[i+1][1],alf);
      //dist[i]=norma(px-cx,py-cy);
      dist=norma(px-cx,py-cy);
    }
    if(dist<=distmin){
      distmin=dist;
    }
  }
  //return distancia_minima(dist,n-1);
  return distmin;
}

void trasladar(polilinea_t *polilinea, float dx, float dy){
  for(int i=0;i<polilinea->n;i++){
    polilinea->puntos[i][0]+=dx;
    polilinea->puntos[i][1]+=dy;
    /*
    polilinea[i][0]+=dx;
    polilinea[i][1]+=dy;
    */
  }
}

void rotar(polilinea_t *polilinea, double rad){
  double co=cos(rad);
  double si=sin(rad);
  for(int i=0;i<polilinea->n;i++){
    float xp=polilinea->puntos[i][0]*co-polilinea->puntos[i][1]*si;
    float yp=polilinea->puntos[i][0]*si+polilinea->puntos[i][1]*co;
    polilinea->puntos[i][0]=xp;
    polilinea->puntos[i][1]=yp;
  }
}


size_t polilinea_sizeof(void) {
  return sizeof(polilinea_t);
}

float polilinea_buscar_xmax(polilinea_t *p) {
  float max = 0;
  for(size_t i=0; i<p->n; i++){
    if(max < p->puntos[i][0])
      max = p->puntos[i][0];
  }
  return max;
}

float polilinea_buscar_xmin(polilinea_t *p) {
  float min = VENTANA_ALTO;
  for(size_t i=0; i<p->n; i++){
    if(min > p->puntos[i][0])
      min = p->puntos[i][0];
  }
  return min;
}

float polilinea_buscar_ymax(polilinea_t *p) {
  float max = 0;
  for(size_t i=0; i<p->n; i++){
    if(max < p->puntos[i][1])
      max = p->puntos[i][1];
  }
  return max;
}

void polilinea_agrandar(polilinea_t *p, float a) {
  for(size_t i=0; i<p->n; i++){
    p->puntos[i][0]*=a;
    p->puntos[i][1]*=a;
  }
}


void graficar_polilinea(SDL_Renderer *renderer, polilinea_t *p, float f){
    SDL_SetRenderDrawColor(renderer, polilinea_get_red(p), polilinea_get_green(p), polilinea_get_blue(p), 0x00);
    float x1,x2,y1,y2;
    for(int i = 0; i < polilinea_cantidad_puntos(p)-1; i++) {
        polilinea_obtener_punto(p,i,&x1,&y1);
        polilinea_obtener_punto(p,i+1,&x2,&y2);
        SDL_RenderDrawLine(
            renderer,
            x1 * f,
            VENTANA_ALTO-(y1 * f),
            x2 * f,
            VENTANA_ALTO-(y2 * f)
        );
    }
}