#ifndef DISPAROS_H
#define DISPAROS_H

typedef struct disparo disparo_t;

disparo_t *crear_disparo(double x, double y, double angulo);


bool disparo_mover(void *disparo, void *extra);

double disparo_get_posx(disparo_t *disparo);
double disparo_get_posy(disparo_t *disparo);
double disparo_get_angulo(disparo_t *disparo);
double disparo_tiempo(disparo_t *disparo);

bool disparo_expiro(disparo_t *disparo, void *extra);

#endif
