#include "encabezado.h"
#include "caracteres.h"

#define MAX_DIGITS 7
#define MAX_STRING 20

struct encabezado {
    int score;
    char score_number[MAX_DIGITS];
    char score_string[MAX_STRING];
    int fuel;
    char fuel_number[MAX_DIGITS];
    char fuel_string[MAX_STRING];
};

encabezado_t *encabezado_crear(void) {
    encabezado_t *e = malloc(sizeof(encabezado_t));
    if(e==NULL)
        return NULL;
    e->fuel = 10000;
    strcpy(e->fuel_number, "10000");
    strcpy(e->fuel_string, "fuel");
    e->score = 0;
    strcpy(e->score_number, "0");
    strcpy(e->score_string, "score");
    return e;
}

void encabezado_destruir(encabezado_t *e) {
    free(encabezado);
}

void encabezado_graficar(encabezado_t *e) {
    for(size_t i=0; e->fuel_string[i]; i++) {
        size_t posicion = pos_caracter_polilinea(e->fuel_string[i]);
        size_t tam = tamanio_letra(e->fuel_string[i]);
        polilinea_t *p = polilinea_crear(caracteres[posicion], tam, 0xAD,0xD8,0xE6);
        polilinea_destruir(p);
    }

}



