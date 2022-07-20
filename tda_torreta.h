#ifndef TORRETA_H
#define TORRETA_H

#define MAX_LVL 10


typedef struct torreta torreta_t;

typedef struct torreta_diccionario torreta_diccionario_t;

//PRE: recibe numeros flotantes de posicion inicial y angulo
//POST: crea torreta, devuelve NULL en caso de error
torreta_t *torreta_crear(double posx, double posy, double angulo);

//destruye torreta
void torreta_destruir(torreta_t *torreta);


torreta_t **torretas_activar(char nivel[MAX_LVL], size_t *n);

void torreta_vector_destruir(torreta_t **t, size_t n);

//PRE: torreta ya fue creada
//POST: devuelve posicion/angulo
float torreta_get_posx(torreta_t *t);
float torreta_get_posy(torreta_t *t);
float torreta_get_angulo(torreta_t *t);

//PRE: torreta ya fue creada
//POST: devuelve su estado de vida
bool torreta_vive(torreta_t *torreta);

//PRE: torreta ya fue creada
//POST: cambia el estado de vivo a muerto
void torreta_matar(void *torreta);

void torreta_diccionario_matar(float posicion_x, float posicion_y, char nivel[MAX_LVL]);

#endif
