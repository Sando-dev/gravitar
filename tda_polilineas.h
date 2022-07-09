#ifndef POLILINEAS_H
#define POLILINEAS_H

typedef uint8_t color_t;

struct polilinea{
    float (*puntos)[2];
    size_t n;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

typedef struct polilinea polilinea_t;



polilinea_t *polilinea_crear(const float puntos[][2], size_t n);
void polilinea_destruir(polilinea_t *polilinea);

size_t polilinea_cantidad_puntos(const polilinea_t *polilinea);
bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y);
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);

polilinea_t *polilinea_clonar(const polilinea_t *polilinea);

bool polilinea_setear_color(polilinea_t *polilinea, color_t color);



void trasladar(float polilinea[][2], size_t n, float dx, float dy);
void rotar(float polilinea[][2], size_t n, double rad);

polilinea_t *leer_polilinea(FILE *f);

#endif
