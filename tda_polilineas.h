#ifndef POLILINEAS_H
#define POLILINEAS_H

#include <SDL2/SDL.h>

typedef uint8_t color_t;

typedef struct polilinea polilinea_t;


//PRE: recibe matriz de floats, cantidad de puntos y valores de 8 bits para los colores
//POST: crea polilinea, devuelve NULL en caso de error
polilinea_t *polilinea_crear(const float puntos[][2], size_t n, uint8_t r, uint8_t g, uint8_t b);

//destruye polilinea
void polilinea_destruir(polilinea_t *polilinea);

//PRE: polilinea ya fue creada
//POST: devuelve la cantidad de puntos
size_t polilinea_cantidad_puntos(const polilinea_t *polilinea);

//PRE: polilinea ya fue creada recibe la posicion del punto y punteros a float para las coordenadas
//POST: devuelve booleano por el nombre si se pudo hacer la opreacion y las coordenadas por la interfaz
bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y);

//PRE: polilinea ya fue creada recibe la posicion del punto y floats para cada coordenada
//POST: devuelve booleano por el nombre si se pudo hacer la opreacion y setea el punto en la polilinea
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);

//PRE: polilinea ya fue creada
//POST: devuelve puntero a polilinea con los mismos datos de la polilinea mandada, NULL en caso de falla
polilinea_t *polilinea_clonar(const polilinea_t *polilinea);


bool polilinea_setear_color(polilinea_t *polilinea, color_t color);

size_t polilinea_sizeof(void);

//PRE: polilinea ya fue creada, recibe puntos float para trasladar la polilinea o double angulo para rotarla
//POST: traslada o rota la polilinea mandada
void trasladar(polilinea_t *polilinea, float dx, float dy);
void rotar(polilinea_t *polilinea, double rad);


//PRE: polilinea ya fue creada
//POST: devuelve numero de 8 bits correpondiente al color
uint8_t polilinea_get_red(polilinea_t *p);
uint8_t polilinea_get_green(polilinea_t *p);
uint8_t polilinea_get_blue(polilinea_t *p);

//PRE: polilinea ya fue creada, floats correspondientes al punto a comparar
//POST: devuelve un double con la distancia mas corta del punto a la polilinea
double distancia_punto_a_polilinea(polilinea_t *polilinea, float px, float py);


//PRE: polilinea ya fue creada
//POST: devuelve un float correspondeinte al minimo o maximo de x o y de la poliliena mandada
float polilinea_buscar_xmax(polilinea_t *p);
float polilinea_buscar_xmin(polilinea_t *p);
float polilinea_buscar_ymax(polilinea_t *p);

void polilinea_agrandar(polilinea_t *p, float a);

polilinea_t *leer_polilinea(FILE *f);

void graficar_polilinea(SDL_Renderer *renderer, polilinea_t *p, float f);

#endif
