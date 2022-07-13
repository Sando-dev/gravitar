#include <stdlib.h>

#include "tda_lista.h"

struct nodo {
    struct nodo *sig;
    void *dato;
};

struct lista {
    struct nodo *prim;
};

static struct nodo *crear_nodo(void *d, struct nodo *sig) {
    struct nodo *n = malloc(sizeof(struct nodo));
    if(n == NULL) return NULL;

    n->dato = d;
    n->sig = sig;

    return n;
}

lista_t *lista_crear() {
    lista_t *l = malloc(sizeof(lista_t));
    if(l == NULL) return NULL;

    l->prim = NULL;

    return l;
}

void lista_destruir(lista_t *l, void (*destruir_dato)(void *)) {
    struct nodo *actual = l->prim;
    while(actual != NULL) {
        destruir_dato(actual->dato);
        struct nodo *sig = actual->sig;

        free(actual);

        actual = sig;
    }
    free(l);
}

bool lista_es_vacia(const lista_t *l) {
    return l->prim == NULL;
}

bool lista_agregar_al_principio(lista_t *l, void *dato) {
    struct nodo *nuevo = crear_nodo(dato, l->prim);
    if(nuevo == NULL) return false;

    l->prim = nuevo;

    return true;
}

bool lista_agregar_al_final(lista_t *l, void *dato) {
    if(l->prim == NULL) {
        return lista_agregar_al_principio(l, dato);
    }

    struct nodo *actual = l->prim;
    while(actual->sig != NULL) {
        actual = actual->sig;
    }

    actual->sig = crear_nodo(dato, NULL);
    return actual->sig != NULL;
}

void *lista_buscar(const lista_t *l, void *dato, int (*cmp)(const void *, const void *)) {
    struct nodo *actual = l->prim;
    while(actual != NULL) {
        if(cmp(actual->dato, dato) == 0)
            return actual->dato;

        actual = actual->sig;
    }
    return NULL;
}

void *lista_borrar(lista_t *l, void *dato, int (*cmp)(const void *, const void *)) {

    struct nodo *anterior = NULL;
    struct nodo *actual = l->prim;
    while(actual != NULL) {
        if(cmp(actual->dato, dato) == 0) {
            if(anterior == NULL) {
                l->prim = actual->sig;
            }
            else {
                anterior->sig = actual->sig;
            }

            void *aux = actual->dato;
            free(actual);
            return aux;
        }

        anterior = actual;
        actual = actual->sig;
    }
    return NULL;
}

void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra) {
    struct nodo *actual = l->prim;
    while(actual != NULL) {
        if(! visitar(actual->dato, extra)) return;

        actual = actual->sig;
    }
}


/*
void *lista_borrar(lista_t *l, void *dato, int (*cmp)(const void *, const void *)) {
    struct nodo **anterior = &(l->prim);
    while(*anterior != NULL) {
        struct nodo *actual = *anterior;

        if(cmp(actual->dato, dato) == 0) {
            *anterior = actual->sig;
            void *aux = actual->dato;
            free(actual);
            return aux;
        }

        anterior = &(actual->sig);
    }

}
*/
