#ifndef FUEL_H
#define FUEL_H

#include <stdio.h>

#define MAX_LVL 10

typedef struct fuel fuel_t;

typedef struct fuel_diccionario fuel_diccionario_t;

//PRE: recibe numeros flotantes de posicion inicial y angulo
//POST: crea fuel, devuelve NULL en caso de error
fuel_t *fuel_crear(double posx, double posy, double angulo);

fuel_t **fuel_activar(char nivel[MAX_LVL], size_t *n);

void fuel_vector_destruir(fuel_t **t, size_t n);


//PRE: fuel ya fue creado
//POST: devuelve posicion/angulo
float fuel_get_ang(fuel_t *f);
float fuel_get_posy(fuel_t *f);
float fuel_get_posx(fuel_t *f);

//PRE: fuel ya fue creado
//POST: devuelve su estado de vida
bool fuel_vive(fuel_t *fuel);

//PRE: fuel ya fue creado
//POST: cambia el estado de vivo a muerto
void fuel_matar(fuel_t *fuel);


#endif
