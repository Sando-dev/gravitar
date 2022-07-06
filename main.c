#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "config.h"


double computar_velocidad(double vi, double a, double dt){
  return dt*a+vi;
}


double computar_posicion(double pi, double vi, double dt){
  return dt*vi+pi;
}




void trasladar(float polilinea[][2], size_t n, float dx, float dy){
  for(int i=0;i<n;i++){
    polilinea[i][0]+=dx;
    polilinea[i][1]+=dy;
  }
}


void rotar(float polilinea[][2], size_t n, double rad){
  double co=cos(rad);
  double si=sin(rad);
  for(int i=0;i<n;i++){
    float xp=polilinea[i][0]*co-polilinea[i][1]*si;
    float yp=polilinea[i][0]*si+polilinea[i][1]*co;
    polilinea[i][0]=xp;
    polilinea[i][1]=yp;
  }
}

int main() {
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

    // El chorro de la nave:
    float chorro[][2] = {{-4, 2}, {-8, 0}, {-4, -2}};
    size_t chorro_tam = 3;

    bool chorro_prendido = false;

    rotar(nave, nave_tam, PI/2);
    rotar(chorro, chorro_tam, PI/2);
    double vi = 0;
    double pi = 0;
    double a_chorro = 0;
    double rotacion=0;

    // Queremos que todo se dibuje escalado por f:
    float f = 1;
    // END código del alumno

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
                        a_chorro = NAVE_ACELERACION;
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_RIGHT:
                        rotacion=-NAVE_ROTACION_PASO;
                        break;
                    case SDLK_LEFT:
                        rotacion=NAVE_ROTACION_PASO;
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Apagamos el chorro:
                        chorro_prendido = false;
                        a_chorro = 0;
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_RIGHT:
                        rotacion=0;
                        break;
                    case SDLK_LEFT:
                        rotacion=0;
                        break;
                }
            }
            // END código del alumno
            continue;
        }

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);



        // BEGIN código del alumno

        vi = computar_velocidad(vi, -G+a_chorro, (float)1/JUEGO_FPS);
        pi = computar_posicion(pi, vi, (float)1/JUEGO_FPS);
        rotar(nave, nave_tam, rotacion);
        trasladar(nave, nave_tam, 0, pi);
        trasladar(chorro, chorro_tam, 0, pi);
        // Dibujamos la nave escalada por f en el centro de la pantalla:
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
        for(int i = 0; i < nave_tam - 1; i++)
            SDL_RenderDrawLine(
                renderer,
                nave[i][0] * f + VENTANA_ANCHO / 2,
                -nave[i][1] * f + VENTANA_ALTO / 2,
                nave[i+1][0] * f + VENTANA_ANCHO / 2,
                -nave[i+1][1] * f + VENTANA_ALTO / 2
            );

        if(chorro_prendido) {
            // Dibujamos el chorro escalado por f en el centro de la pantalla:
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
            for(int i = 0; i < chorro_tam - 1; i++)
                SDL_RenderDrawLine(
                    renderer,
                    chorro[i][0] * f + VENTANA_ANCHO / 2,
                    -chorro[i][1] * f + VENTANA_ALTO / 2,
                    chorro[i+1][0] * f + VENTANA_ANCHO / 2,
                    -chorro[i+1][1] * f + VENTANA_ALTO / 2
                );
        }
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
    return 0;
}
