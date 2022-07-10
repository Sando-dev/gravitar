#ifndef COMBUSTIBLE_H
#define COMBUSTIBLE_H

typedef struct combustible combustible_t;

combustible_t *combustible_crear(double posx, double posy, double ang);
void combustible_eliminar(combustible_t *comb);

double combustible_posx(combustible_t *comb);
double combustible_posy(combustible_t *comb);
double combustible_angulo(combustible_t *comb);

void combustible_matar(combustible_t *comb);

#endif
