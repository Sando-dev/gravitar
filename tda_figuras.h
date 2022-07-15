#ifndef FIGURAS_H
#define FIGURAS_H


#define TAMANIO_NOMBRE 20

#define MSK_INF 0x40

#define MSK_TIPO 0x0E
#define SHIFT_TIPO 1


typedef enum {
    FIGURA_ICONO,
    FIGURA_NIVEL,
    FIGURA_SPRITE,
    FIGURA_PLANETA,
    FIGURA_BASE,
    FIGURA_COMBUSTIBLE,
    FIGURA_TORRETA,
    FIGURA_REACTOR,
}figura_tipo_t;


typedef struct figura figura_t;

polilinea_t *figura_return_polilinea(figura_t *f, size_t i);

figura_t **figura_leer_archivo(size_t *n);

size_t figura_cant_polilineas(figura_t *f);

figura_t *crear_figura_vacia();
figura_t *figura_crear(FILE *f);
void figura_destruir(figura_t *figura, size_t i, void (*destruir)(polilinea_t*));


bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas);
const char* figura_tipo_a_cadena(figura_tipo_t figura);

const char* figura_return_tipo(figura_t *f);
char *figura_return_nombre(figura_t *f);
bool figura_return_inf(figura_t *f);

polilinea_t **figura_return_vector_polilineas(figura_t *f);
size_t figura_return_cantidad_polilineas(figura_t *f);


size_t figura_buscar(figura_t **f, size_t n_f, char nombre[TAMANIO_NOMBRE]);

#endif