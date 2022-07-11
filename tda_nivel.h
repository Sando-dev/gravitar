#ifndef NIVEL_H
#define NIVEL_H

typedef struct nivel nivel_t;

nivel_t *crear_nivel();
void nivel_destruir(nivel_t *nivel);

void nivel_activar(nivel_t *nivel);
void nivel_desactivar(nivel_t *nivel);

bool nivel_esta_activo(nivel_t *nivel);

#endif
