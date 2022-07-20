#ifndef FISICAYMATEMATICA_H
#define FISICAYMATEMATICA_H

//funciones fisica

//recibe velocidad inicial, aceleracion y tiempo, devuelve la velocidad actual
double computar_velocidad(double vi, double a, double dt);

//recibe posicion inicial, velocidad inicial y tiempo, devuelve la posicion actual
double computar_posicion(double pi, double vi, double dt);

//funciones matematica

//recibe dos puntos, devuelve el producto intero entre ambos
double producto_interno(double x1, double y1, double x2, double y2);

//recibe un punto, devuelve la norma
double norma(double x, double y);

//calculo de alfa para distancia
double alfa(float px, float py, float ax, float ay, float bx, float by);

//para el caso 0<alfa<1 se calcula el punto mas cercano del segmento usando esta funcion para cada componente del punto
double punto_del_segmento(double a,double b,double alf);

#endif
