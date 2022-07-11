#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "tda_fisicaymatematica.h"
#include "tda_polilineas.h"
#include "tda_figuras.h"

polilinea_t **copiar_figura(figura_t *figura, double x, double y, double ang){
  polilinea_t **polilineas=malloc(figura_cant_polilineas(figura)*sizeof(polilinea_t*));
  if(polilineas==NULL){
    return NULL;
  }
  for(size_t i=0; i < figura_cant_polilineas(figura); i++){
    polilineas[i]=polilinea_clonar(figura_return_polilinea(figura,i));
    if(polilineas[i]==NULL){
      return NULL;
    }
    rotar(polilineas[i],ang);
    trasladar(polilineas[i],x,y);
  }
  return polilineas;
}

void destruir_figura(polilinea_t **polilineas,size_t n){
  for(size_t i=0;i<n;i++){
    polilinea_destruir(polilineas[i]);
  }
  free(polilineas);
}

void graficar_polilinea(SDL_Renderer *renderer, polilinea_t *p, float f){
    SDL_SetRenderDrawColor(renderer, polilinea_get_red(p), polilinea_get_green(p), polilinea_get_blue(p), 0x00);
    float x1,x2,y1,y2;
    for(int i = 0; i < polilinea_cantidad_puntos(p)-1; i++) {
        polilinea_obtener_punto(p,i,&x1,&y1);
        polilinea_obtener_punto(p,i+1,&x2,&y2);
        SDL_RenderDrawLine(
            renderer,
            x1 * f,
            VENTANA_ALTO-(y1 * f),
            x2 * f,
            VENTANA_ALTO-(y2 * f)
        );
    }
}



int main() {


    size_t n_figura;
    figura_t **figura_vector = figura_leer_archivo(&n_figura);
    if(figura_vector == NULL)
        return 1;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    int dormir = 0;

    // BEGIN código del alumno
    // Mi nave:
    float nave[][2] = {{8, 0}, {-1, 6}, {-4, 4}, {-4, 2}, {-2, 0}, {-4, -2}, {-4, -4}, {-1, -6}, {8, 0}};
    size_t nave_tam = 9;
    for(size_t i=0; i<figura_cant_polilineas(figura_vector[8]); i++){
        polilinea_t *p = figura_return_polilinea(figura_vector[8],i);
        for(size_t j=0; j<polilinea_cantidad_puntos(p); j++){
            float x,y;
            polilinea_obtener_punto(p,j,&x,&y);
            //printf("%f,%f\n",x,y);
        }
    }

    // El chorro de la nave:
    float chorro[][2] = {{-4, 2}, {-8, 0}, {-4, -2}};
    size_t chorro_tam = 3;


    bool chorro_prendido = false;



    // Queremos que todo se dibuje escalado por f:
    float f = 0.62;
    // END código del alumno

    float a=0;
    float posx = 0;
    float posy = 0;
    float vx=0;
    float vy=0;
    float angulo = NAVE_ANGULO_INICIAL;

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Prendemos el chorro:

                        chorro_prendido = true;
                        a=NAVE_ACELERACION;
                        break;
                    case SDLK_DOWN:

                        break;
                    case SDLK_RIGHT:
                        angulo -= NAVE_ROTACION_PASO;
                        break;
                    case SDLK_LEFT:
                        angulo += NAVE_ROTACION_PASO;
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Apagamos el chorro:

                        chorro_prendido = false;
                        a=0;
                        break;
                }
            }
            // END código del alumno
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);


        //ACA SE REALIZAN COMPARACIONES Y SE ANALIZAN CASOS PARA NIVELES ETC
        // BEGIN código del alumno

        vx=computar_velocidad(vx,a*cos(angulo),(float)1/JUEGO_FPS);
        vy=computar_velocidad(vy,a*sin(angulo)-G,(float)1/JUEGO_FPS);
        posx=computar_posicion(posx,vx,(float)1/JUEGO_FPS);
        posy=computar_posicion(posy,vy,(float)1/JUEGO_FPS);

        polilinea_t **estrella=copiar_figura(figura_vector[3],457,364,0);
        for(size_t i=0; i<figura_cant_polilineas(figura_vector[3]);i++){
          graficar_polilinea(renderer,estrella[i],f);
        }
        destruir_figura(estrella,figura_cant_polilineas(figura_vector[3]));
/*
        float nave_clon[9][2];
        float chorro_clon[3][2];

        for(size_t i=0; i < nave_tam; i++) {
            nave_clon[i][0] = nave[i][0];
            nave_clon[i][1] = nave[i][1];
        }

        for(size_t j=0; j < chorro_tam; j++) {
            chorro_clon[j][0] = chorro[j][0];
            chorro_clon[j][1] = chorro[j][1];
        }


        rotar(nave_clon, nave_tam, angulo);
        rotar(chorro_clon, chorro_tam, angulo);


        trasladar(nave_clon, nave_tam, posx, posy);
        trasladar(chorro_clon, chorro_tam, posx, posy);
*/

/*
        // Dibujamos la nave escalada por f en el centro de la pantalla:
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
        for(int i = 0; i < nave_tam - 1; i++)
            SDL_RenderDrawLine(
                renderer,
                nave_clon[i][0] * f + VENTANA_ANCHO / 2,
                -nave_clon[i][1] * f + VENTANA_ALTO / 2,
                nave_clon[i+1][0] * f + VENTANA_ANCHO / 2,
                -nave_clon[i+1][1] * f + VENTANA_ALTO / 2
            );
*/
/*
        for(size_t i=0; i<figura_cant_polilineas(figura_vector[14]); i++)
            graficar_polilinea(renderer, figura_return_polilinea(figura_vector[14],i),f);

*/
/*
        if(chorro_prendido) {
            // Dibujamos el chorro escalado por f en el centro de la pantalla:
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
            for(int i = 0; i < chorro_tam - 1; i++)
                SDL_RenderDrawLine(
                    renderer,
                    chorro_clon[i][0] * f + VENTANA_ANCHO / 2,
                    -chorro_clon[i][1] * f + VENTANA_ALTO / 2,
                    chorro_clon[i+1][0] * f + VENTANA_ANCHO / 2,
                    -chorro_clon[i+1][1] * f + VENTANA_ALTO / 2
                );
        }

*/

        // END código del alumno

        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);
        ticks = SDL_GetTicks();
    }

    // BEGIN código del alumno

    // No tengo nada que destruir.
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    for(size_t i=0; i < n_figura; i++){
        figura_destruir(figura_vector[i],figura_cant_polilineas(figura_vector[i]),polilinea_destruir);
    }
    free(figura_vector);
    return 0;
}
