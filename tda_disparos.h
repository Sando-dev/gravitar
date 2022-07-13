#ifndef DISPAROS_H
#define DISPAROS_H

typedef struct disparo disparo_t;

disparo_t *crear_disparo(double x, double y, double angulo);
void disparo_destruir(disparo_t *disparo);

bool disparo_mover(disparo_t *disparo, void *extra);

double disparo_get_posx(disparo_t *disparo);
double disparo_get_posy(disparo_t *disparo);
double disparo_get_angulo(disparo_t *disparo);
double disparo_tiempo(disparo_t *disparo);

int disparo_tiempo_comparar(disparo_t *disparo, double t);

#endif
