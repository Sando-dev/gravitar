#ifndef TORRETA_H
#define TORRETA_H

typedef struct torreta torreta_t;

torreta_t *torreta_crear(double posx, double posy, double angulo);
void torreta_destruir(torreta_t *torreta);

void torreta_matar(torreta_t *torreta);



#endif
