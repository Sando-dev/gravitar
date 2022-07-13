#ifndef NIVEL_H
#define NIVEL_H

typedef struct nivel nivel_t;

#define TAMANIO_NOMBRE 20

nivel_t *nivel_crear(char *nombre);
void nivel_destruir(nivel_t *nivel);

char *nivel_nombre(nivel_t *nivel);
size_t nivel_buscar(nivel_t **n_vector, size_t n_n, char nombre[TAMANIO_NOMBRE]);

void nivel_activar(nivel_t *nivel);
void nivel_desactivar(nivel_t *nivel);

bool nivel_esta_activo(nivel_t *nivel);

#endif