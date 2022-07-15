#ifndef POLILINEAS_H
#define POLILINEAS_H

typedef uint8_t color_t;

typedef struct polilinea polilinea_t;

uint8_t polilinea_get_red(polilinea_t *p);
uint8_t polilinea_get_green(polilinea_t *p);
uint8_t polilinea_get_blue(polilinea_t *p);


polilinea_t *polilinea_crear(const float puntos[][2], size_t n, uint8_t r, uint8_t g, uint8_t b);
void polilinea_destruir(polilinea_t *polilinea);

size_t polilinea_cantidad_puntos(const polilinea_t *polilinea);
bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y);
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);

polilinea_t *polilinea_clonar(const polilinea_t *polilinea);

bool polilinea_setear_color(polilinea_t *polilinea, color_t color);

size_t polilinea_sizeof(void);

void trasladar(polilinea_t *polilinea, float dx, float dy);
void rotar(polilinea_t *polilinea, double rad);

double distancia_punto_a_polilinea(polilinea_t *polilinea, float px, float py);

float polilinea_buscar_xmax(polilinea_t *p);

float polilinea_buscar_xmin(polilinea_t *p);

float polilinea_buscar_ymax(polilinea_t *p);

void polilinea_agrandar(polilinea_t *p, float a);

polilinea_t *leer_polilinea(FILE *f);

#endif
