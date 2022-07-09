#ifndef NAVE_H
#define NAVE_H

typedef struct nave nave_t;

nave_t *nave_crear(double px_inicial, double py_inicial);
void nave_destruir(nave_t *nave);

void nave_matar(nave_t *nave, double px_inicial, double py_inicial);

void nave_mover(nave_t *nave, double ax,double ay, double angulo);

void nave_prender_chorro(nave_t *nave);
void nave_apagar_chorro(nave_t *nave);
void nave_prender_escudo(nave_t *nave);
void nave_apagar_escudo(nave_t *nave);

bool nave_chorro_esta_prendido(nave_t *nave);
bool nave_escudo_esta_prendido(nave_t *nave);

double nave_get_posx(nave_t *nave);
double nave_get_posy(nave_t *nave);
double nave_get_angulo(nave_t *nave);


#endif
