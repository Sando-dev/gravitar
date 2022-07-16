#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "encabezado.h"
#include "caracteres.h"

#define MAX_DIGITS 7
#define MAX_STRING 20

struct encabezado {
    int score;
    char score_number[MAX_DIGITS];
    char score_string[MAX_STRING];
    int fuel;
    char fuel_number[MAX_DIGITS];
    char fuel_string[MAX_STRING];
};

encabezado_t *encabezado_crear(void) {
    encabezado_t *e = malloc(sizeof(encabezado_t));
    if(e==NULL)
        return NULL;
    e->fuel = 10000;
    strcpy(e->fuel_number, "10000");
    strcpy(e->fuel_string, "fuel");
    e->score = 0;
    strcpy(e->score_number, "0");
    strcpy(e->score_string, "score");
    return e;
}

void encabezado_destruir(encabezado_t *e) {
    free(e);
}

void imprimir_matriz(float m[][2], size_t n);

void encabezado_graficar(encabezado_t *e, SDL_Renderer *renderer) {
    for(size_t i=0; e->fuel_string[i]; i++) {
        size_t posicion = caracter_posicion(e->fuel_string[i]);
        size_t tam = caracter_size(e->fuel_string[i]);
        polilinea_t *p = polilinea_crear(caracteres[posicion], tam, 0xAD,0xD8,0xE6);
        trasladar(p,(372.5+(15*i))/2.5,550/2.5);
        graficar_polilinea(renderer, p, 2.5);
        polilinea_destruir(p);
    }
    for(size_t i=0; e->score_string[i]; i++) {
        size_t posicion = caracter_posicion(e->score_string[i]);
        size_t tam = caracter_size(e->score_string[i]);
        polilinea_t *p = polilinea_crear(caracteres[posicion], tam, 0xAD,0xD8,0xE6);
        trasladar(p,(365+(15*i))/2.5,575/2.5);
        graficar_polilinea(renderer, p, 2.5);
        polilinea_destruir(p);
    }
    sprintf(e->fuel_number,"%d",e->fuel);
    for(size_t i=0; e->fuel_number[i]; i++) {
        size_t posicion = caracter_posicion(e->fuel_number[i]);
        size_t tam = caracter_size(e->fuel_number[i]);
        polilinea_t *p = polilinea_crear(caracteres[posicion], tam, 0x00,0xFF,0x00);
        trasladar(p,(150+(15*i))/2.5,550/2.5);
        graficar_polilinea(renderer, p, 2.5);
        polilinea_destruir(p);
    }
}

void encabezado_set_fuel(encabezado_t *e, int fuel) {
    e->fuel = fuel;
}
