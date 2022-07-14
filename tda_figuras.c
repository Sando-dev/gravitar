#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "tda_polilineas.h"
#include "tda_figuras.h"



struct figura{
  char nombre[TAMANIO_NOMBRE];
  figura_tipo_t tipo;
  bool infinito;
  size_t cantidad_polilineas;
  polilinea_t **polilineas;
};



const char *tipos_figuras[]={
  [FIGURA_ICONO]="Icono",
  [FIGURA_NIVEL]="Nivel",
  [FIGURA_SPRITE]="Sprite",
  [FIGURA_PLANETA]="Planeta",
  [FIGURA_BASE]="Base",
  [FIGURA_COMBUSTIBLE]="Combustible",
  [FIGURA_TORRETA]="Torreta",
  [FIGURA_REACTOR]="Reactor",
};

figura_t *crear_figura_vacia(){
  figura_t *figura=calloc(1,sizeof(figura_t));
  if(figura==NULL){
    return NULL;
  }
  return figura;
}


figura_t *figura_crear(FILE *f){
  figura_t *figura=crear_figura_vacia();
  if(figura==NULL){
    return NULL;
  }
  if(!leer_encabezado_figura(f,figura->nombre,&(figura->tipo),&(figura->infinito),&(figura->cantidad_polilineas))){
    figura_destruir(figura,0,polilinea_destruir);
    return NULL;
  }
  figura->polilineas=malloc(figura->cantidad_polilineas*(polilinea_sizeof()));
  if(figura->polilineas==NULL){
    figura_destruir(figura,0,polilinea_destruir);
    return NULL;
  }
  for(size_t i=0; i<figura->cantidad_polilineas; i++){
    polilinea_t *polilinea=leer_polilinea(f);
    if(polilinea==NULL){
      figura_destruir(figura,i,polilinea_destruir);
      return NULL;
    }
    figura->polilineas[i]=polilinea;
  }
  return figura;
}


void figura_destruir(figura_t *figura, size_t i, void (*destruir)(polilinea_t*)){
  for(size_t j=0;j<i;j++){
    destruir(figura->polilineas[j]);
  }
  free(figura->polilineas);
  free(figura);
}

bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas){
  if(fread(nombre,sizeof(char),20,f)!=20){
    return false;
  }
  uint8_t caracteristicas;
  if(fread(&caracteristicas,sizeof(uint8_t),1,f)!=1){
    return false;
  }

  *tipo = ((caracteristicas)&MSK_TIPO)>>SHIFT_TIPO;
  *infinito =(caracteristicas)&MSK_INF;
  if(fread(cantidad_polilineas,sizeof(uint16_t),1,f)!=1){
    return false;
  }
  return true;
}

const char* figura_tipo_a_cadena(figura_tipo_t figura){
  return tipos_figuras[figura];
}

const char* figura_return_tipo(figura_t *f){
  return figura_tipo_a_cadena(f->tipo);
}

size_t figura_cant_polilineas(figura_t *f) {
  return f->cantidad_polilineas;
}

figura_t **figura_leer_archivo(size_t *n){
  FILE *f = fopen("figuras.bin", "rb");
    if(f == NULL) {
        fprintf(stderr, "No pudo abrirse \"%s\"\n", "figuras.bin");
        return NULL;
    }
  figura_t **figura_vector = malloc((sizeof(figura_t*)));
  if(figura_vector == NULL)
    return NULL;


  size_t n_figura = 0;
  while(1) {
      n_figura++;

      figura_t **aux = realloc(figura_vector, (n_figura)*sizeof(figura_t *));
      if(aux==NULL) {
        break;
      }
      figura_vector = aux;
      figura_t *figura = figura_crear(f);
      if(figura==NULL)
        break;
      figura_vector[n_figura-1] = figura;
  }
  *n = n_figura-1;


  fclose(f);
  return figura_vector;
}

polilinea_t *figura_return_polilinea(figura_t *f, size_t i) {
  return f->polilineas[i];
}

char *figura_return_nombre(figura_t *f){
  return f->nombre;
}

bool figura_return_inf(figura_t *f) {
  return f->infinito;
}

size_t figura_buscar(figura_t **f_vector, size_t n_f, char nombre[TAMANIO_NOMBRE]){
  size_t n;
  for(size_t i=0; i<n_f; i++){
    if(!(strcmp(f_vector[i]->nombre,nombre)))
      n=i;
  }
  return n;
}