#include <stdio.h>
#include <math.h>
#include "config.h"

#define DT 1/JUEGO_FPS

//calcular velocidad
double computar_velocidad(double vi, double a, double dt){
  return dt*a+vi;
}

//calcular posicion
double computar_posicion(double pi, double vi, double dt){
  return DT*vi+pi;
}

//prod interno x*x+y*y
double producto_interno(double x1, double y1, double x2, double y2){
  return x1*x2+y1*y2;
}

//calcular la norma de un vector
double norma(double x, double y){
  return sqrt(pow(x,2)+pow(y,2));
}

//calculo de alfa usando las funciones producto interno y norma
double alfa(float px, float py, float ax, float ay, float bx, float by){
  return producto_interno(px-ax,py-ay,bx-ax,by-ay)/pow(norma(bx-ax,by-ay),2);

}

//para el caso 0<alfa<1 se calcula el punto mas cercano del segmento usando esta funcion para cada componente del punto
double punto_del_segmento(double a,double b,double alf){
  return a+alf*(b-a);
}
