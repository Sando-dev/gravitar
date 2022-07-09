#ifndef FIGURAS_H
#define FIGURAS_H

nave_t nave_crear(double px_inicial, double py_inicial, double angulo_inicial);
void nave_destruir(nave_t *nave);

void nave_matar(nave_t *nave, double px_inicial, double py_inicial, double angulo_inicial);

void nave_prender_chorro(nave_t *nave, double gasto);
void nave_apagar_chorro(nave_t *nave);
void nave_prender_escudo(nave_t *nave, double gasto);
void nave_prender_escudo(nave_t *nave);

bool nave_chorro_esta_prendido(nave_t *nave);
bool nave_escudo_esta_prendido(nave_t *nave);

double nave_get_posx(nave_t *nave);
double nave_get_posy(nave_t *nave);
double nave_get_angulo(nave_t *nave);


#endif
