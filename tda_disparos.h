#ifndef DISPAROS_H
#define DISPAROS_H

typedef struct disparo disparo_t;

disparo_t *crear_disparo(double x, double y, double vx, double vy, double angulo);
void disparo_destruir(disparo_t *disparo);

void disparo_mover(disparo_t *disparo);

double disparo_get_posx(disparo_t *disparo);
double disparo_get_posy(disparo_t *disparo);
double disparo_get_angulo(disparo_t *disparo);
double disparo_tiempo(disparo_t *disparo);

#endif
