#ifndef ELEMENTOSNIVELES_H
#define ELEMENTOSNIVELES_H

typedef struct elementos_niveles elementos_niveles_t;

elementos_niveles_t *elementos_niveles_crear(double posx, double posy, double angulo);

void elementos_niveles_matar(void *elementos_niveles);
bool elementos_niveles_esta_vivo(void *elementos_niveles, void *extra);

bool elementos_niveles_es_torreta(void *elementos_niveles, void *extra);
bool elementos_niveles_es_combustible(void *elementos_niveles, void *extra);

double elementos_niveles_posx(elementos_niveles_t *elementos_niveles);
double elementos_niveles_posy(elementos_niveles_t *elementos_niveles);
double elementos_niveles_angulo(elementos_niveles_t *elementos_niveles);

#endif
