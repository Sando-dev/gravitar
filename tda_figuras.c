#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "tda_polilineas.h"
#include "tda_figuras.h"

#define TAMANIO_NOMBRE 20

#define MSK_INF 0x80

#define MSK_TIPO 0x0E
#define SHIFT_TIPO 1


struct figura{
  char nombre[TAMANIO_NOMBRE];
  figura_tipo_t *tipo;
  bool infinito;
  size_t cantidad_polilineas;
  polilinea_t **polilineas;
};

enum tipos{
  FIGURA_ICONO,
  FIGURA_NIVEL,
  FIGURA_SPRITE,
  FIGURA_PLANETA,
  FIGURA_BASE,
  FIGURA_COMBUSTIBLE,
  FIGURA_TORRETA,
  FIGURA_REACTOR,
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
  figura_t *figura=malloc(sizeof(figura_t));
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
  if(!leer_encabezado_figura(f,figura->nombre,figura->tipo,&(figura->infinito),&(figura->cantidad_polilineas))){
    figura_destruir(figura,0,polilinea_destruir);
    return NULL;
  }
  polilinea_t **polilineas=malloc(figura->cantidad_polilineas*(sizeof(polilinea_t*)));
  if(polilineas==NULL){
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
  free(figura->nombre);
  for(size_t j=0;j<i;i++){
    destruir(figura->polilineas[i]);
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
  *tipo=((caracteristicas)&MSK_TIPO)>>SHIFT_TIPO;
  *infinito=(caracteristicas)&MSK_INF;
  if(fread(cantidad_polilineas,sizeof(uint16_t),1,f)!=1){
    return false;
  }
  return true;
}

const char* figura_tipo_a_cadena(figura_tipo_t figura){
  return tipos_figuras[figura];
}


bool figura_leer_archivo(void){
  FILE *f = fopen("figuras.bin", "rb");
    if(f == NULL) {
        fprintf(stderr, "No pudo abrirse \"%s\"\n", "figuras.bin");
        return 1;
    }
  
  int figura = 0;
  while(1) {
      figura++;

      char nombre[20];
      bool infinito;
      figura_tipo_t tipo;
      size_t cantidad_polilineas;

      if(! leer_encabezado_figura(f, nombre, &tipo, &infinito, &cantidad_polilineas))
         break;


      printf("FIGURA \"%s\", TIPO: %s, INFINITO: %d, POLILINEAS: %zd\n", nombre, figura_tipo_a_cadena(tipo), infinito, cantidad_polilineas);

      for(size_t i = 0; i < cantidad_polilineas; i++) {
          polilinea_t *p = leer_polilinea(f);
          if(p == NULL) {
              fprintf(stderr, "Error en el archivo");
              fclose(f);
              return false;
          }
          polilinea_destruir(p);
        }
    }

  fclose(f);
  return true;
}