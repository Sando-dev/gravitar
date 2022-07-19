#ifndef TORRETA_H
#define TORRETA_H

#define MAX_LVL 10


typedef struct torreta torreta_t;

typedef struct torreta_diccionario torreta_diccionario_t;

torreta_t *torreta_crear(double posx, double posy, double angulo);
void torreta_destruir(torreta_t *torreta);

void torreta_matar(void *torreta);

torreta_t **torretas_activar(char nivel[MAX_LVL], size_t *n);

void torreta_vector_destruir(torreta_t **t, size_t n);

float torreta_get_posx(torreta_t *t);

float torreta_get_posy(torreta_t *t);

float torreta_get_angulo(torreta_t *t);

#endif
