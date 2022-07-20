#ifndef NAVE_H
#define NAVE_H

typedef struct nave nave_t;

//PRE: recibe numeros flotantes de posicion inicial
//POST: crea nave, devuelve NULL en caso de error
nave_t *nave_crear(double px_inicial, double py_inicial);

//destruye nave
void nave_destruir(nave_t *nave);

//PRE: nave ya fue creada, numeros flotantes para su posicion de respawn
//POST: descuenta una vida y transporta a la posicion de respawn
void nave_matar(nave_t *nave, double px_inicial, double py_inicial);

//PRE: nave ya fue creada
//POST: prende o apaga su escudo/chorro
void nave_mover(nave_t *nave, double a, double angulo, double angulo_estrella);

//PRE: nave ya fue creada
//POST: invierte el sentido de la velocidad de la nave en dicha coordenada
void nave_rebotar_x(nave_t *nave);
void nave_rebotar_y(nave_t *nave);

//PRE: nave ya fue creada, numeros flotantes para su posicion de respawn y booleano si se quiere resetear su velocidad
//POST: transporta a la posicion de respawn
void nave_trasladar(nave_t *nave, double px_inicial, double py_inicial,bool resetear);

//PRE: nave ya fue creada
//POST: prende o apaga su escudo/chorro
void nave_prender_chorro(nave_t *nave);
void nave_apagar_chorro(nave_t *nave);
void nave_prender_escudo(nave_t *nave);
void nave_apagar_escudo(nave_t *nave);

//PRE: nave ya fue creada
//POST: devuelve el estado del chorro/escudo
bool nave_chorro_esta_prendido(nave_t *nave);
bool nave_escudo_esta_prendido(nave_t *nave);

//PRE: nave ya fue creada
//POST: devuelve posicion/angulo/cant de vidas/fuel restante
double nave_get_posx(nave_t *nave);
double nave_get_posy(nave_t *nave);
double nave_get_angulo(nave_t *nave);
int nave_get_vidas(nave_t *nave);
int nave_get_fuel(nave_t *nave);

void nave_add_fuel(nave_t *nave);

#endif
