#ifndef FIGURAS_H
#define FIGURAS_H

typedef struct figura figura_t;
typedef enum tipos figura_tipo_t;

figura_t *crear_figura_vacia();
figura_t *figura_crear(FILE *f);
void figura_destruir(figura_t *figura, size_t i, void (*destruir)(polilinea_t*));


bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas);
const char* figura_tipo_a_cadena(figura_tipo_t figura);

#endif
