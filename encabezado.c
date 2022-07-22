#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "encabezado.h"
#include "caracteres.h"

#define MAX_DIGITS 7

#define TURRET_SCORE 250

struct encabezado {
    int score;
    char score_number[MAX_DIGITS];
    char score_string[MAX_STRING];
    int fuel;
    char fuel_number[MAX_DIGITS];
    char fuel_string[MAX_STRING];
    int timer;
    char timer_number[MAX_DIGITS];
    bool lvl_completed;
    char lvl_completed_string[MAX_STRING];
};

typedef struct niveles_points {
    char lvl[MAX_STRING];
    int points;
}lvl_point_t;

lvl_point_t niveles_points[] = {
    {"NIVEL1NE", 2000},
    {"NIVEL1SE", 4000},
    {"NIVEL1SW", 6000},
    {"NIVEL1NW", 8000},
    {"NIVEL1R", 9000}
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
    e->timer = 0;
    e->lvl_completed = false;
    strcpy(e->lvl_completed_string,"level completed");
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
        polilinea_t *p = polilinea_crear(caracteres[posicion], tam, 0x00,0xFF,0xFF);
        trasladar(p,(372.5+(15*i))/2.5,550/2.5);
        graficar_polilinea(renderer, p, 2.5);
        polilinea_destruir(p);
    }
    for(size_t i=0; e->score_string[i]; i++) {
        size_t posicion = caracter_posicion(e->score_string[i]);
        size_t tam = caracter_size(e->score_string[i]);
        polilinea_t *p = polilinea_crear(caracteres[posicion], tam, 0x00,0xFF,0xFF);
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
    sprintf(e->score_number,"%d",e->score);
    for(size_t i=0; e->score_number[i]; i++) {
        size_t posicion = caracter_posicion(e->score_number[i]);
        size_t tam = caracter_size(e->score_number[i]);
        polilinea_t *p = polilinea_crear(caracteres[posicion], tam, 0x00,0xFF,0x00);
        trasladar(p,(675+(15*i))/2.5,575/2.5);
        graficar_polilinea(renderer, p, 2.5);
        polilinea_destruir(p);
    }
    if(e->timer) {
        sprintf(e->timer_number,"%d",e->timer);
        for(size_t i=0; e->timer_number[i]; i++) {
            size_t posicion = caracter_posicion(e->timer_number[i]);
            size_t tam = caracter_size(e->timer_number[i]);
            polilinea_t *p = polilinea_crear(caracteres[posicion], tam, 0xFF,0x00,0x00);
            trasladar(p,(300+(32*i))/6,200/6);
            graficar_polilinea(renderer, p, 6);
            polilinea_destruir(p);
        }
    }
    if(e->lvl_completed){
        for(size_t i=0; e->lvl_completed_string[i]; i++) {
            size_t posicion = caracter_posicion(e->lvl_completed_string[i]);
            size_t tam = caracter_size(e->lvl_completed_string[i]);
            polilinea_t *p = polilinea_crear(caracteres[posicion], tam, 0x00,0xFF,0xFF);
            trasladar(p,(300+(15*i))/2.5,350/2.5);
            graficar_polilinea(renderer, p, 2.5);
            polilinea_destruir(p);
        }
    }
}

void encabezado_set_fuel(encabezado_t *e, int fuel) {
    e->fuel = fuel;
}

void encabezado_torreta_matada(encabezado_t *e) {
    e->score += TURRET_SCORE;
}


void encabezado_nivel_completado(encabezado_t *e, char level[MAX_STRING]) {
    size_t cantidad = sizeof(niveles_points) / sizeof(niveles_points[0]);
    for(size_t i=0; i<cantidad; i++) {
        if(!strcmp(level,niveles_points[i].lvl)){
            e->score += niveles_points[i].points;
            niveles_points[i].points = 0;
        }
    }
}
int encabezado_get_score(encabezado_t *e){
  return e->score;
}


void encabezado_activar_timer(encabezado_t *e, bool hay_reactor) {
    if(hay_reactor)
        e->timer = 25;
}

void encabezado_set_timer(encabezado_t *e, int time) {
    e->timer = time;
}

void encabezado_set_lvl_completed(encabezado_t *e, bool lvl_state) {
    e->lvl_completed = lvl_state;
}