#ifndef FISICAYMATEMATICA_H
#define FISICAYMATEMATICA_H

//funciones fisica
double computar_velocidad(double vi, double a, double dt);
double computar_posicion(double pi, double vi, double dt);

//funciones matematica
double producto_interno(double x1, double y1, double x2, double y2);
double norma(double x, double y);
double alfa(float px, float py, float ax, float ay, float bx, float by);
double punto_del_segmento(double a,double b,double alf);

#endif
