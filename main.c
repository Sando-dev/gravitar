#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "tda_fisicaymatematica.h"
#include "tda_polilineas.h"
#include "tda_figuras.h"
#include "tda_nave.h"

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

    // El chorro de la nave:




    // Queremos que todo se dibuje escalado por f:
    float f = 1;
    // END código del alumno
    nave_t *navei=nave_crear(388,218);
    float a=0;
    /*
    float posx = 388;
    float posy = 218;
    float vx=0;
    float vy=0;
    */
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
                        nave_prender_chorro(navei);
                        a=NAVE_ACELERACION;
                        break;
                    case SDLK_DOWN:
                        nave_prender_escudo(navei);
                        break;
                    case SDLK_RIGHT:
                        angulo = -NAVE_ROTACION_PASO;
                        break;
                    case SDLK_LEFT:
                        angulo = NAVE_ROTACION_PASO;
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        // Apagamos el chorro:
                        nave_apagar_chorro(navei);
                        a=0;
                        break;
                    case SDLK_DOWN:
                        nave_apagar_escudo(navei);
                        break;
                    case SDLK_RIGHT:
                        angulo = 0;
                        break;
                    case SDLK_LEFT:
                        angulo = 0;
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
        float angulo_estrella=atan2(457-nave_get_posx(navei),364-nave_get_posy(navei));
        nave_mover(navei,a,angulo,angulo_estrella);

        if(nave_chorro_esta_prendido(navei)){
          polilinea_t **nave=copiar_figura(figura_vector[1],nave_get_posx(navei),nave_get_posy(navei),nave_get_angulo(navei));
          for(size_t i=0; i<figura_cant_polilineas(figura_vector[1]);i++){
            graficar_polilinea(renderer,nave[i],f);
          }
          destruir_figura(nave,figura_cant_polilineas(figura_vector[1]));
        }
        else{
          polilinea_t **nave=copiar_figura(figura_vector[0],nave_get_posx(navei),nave_get_posy(navei),nave_get_angulo(navei));
          for(size_t i=0; i<figura_cant_polilineas(figura_vector[0]);i++){
            graficar_polilinea(renderer,nave[i],f);
          }
          destruir_figura(nave,figura_cant_polilineas(figura_vector[0]));
        }

        if(nave_escudo_esta_prendido(navei)){
          polilinea_t **escudo=copiar_figura(figura_vector[18],nave_get_posx(navei),nave_get_posy(navei),nave_get_angulo(navei));
          for(size_t i=0; i<figura_cant_polilineas(figura_vector[18]);i++){
            graficar_polilinea(renderer,escudo[i],f);
          }
          destruir_figura(escudo,figura_cant_polilineas(figura_vector[18]));
        }

        polilinea_t **base=copiar_figura(figura_vector[2],388,218,0);
        for(size_t i=0; i<figura_cant_polilineas(figura_vector[2]);i++){
          graficar_polilinea(renderer,base[i],f);
        }
        destruir_figura(base,figura_cant_polilineas(figura_vector[2]));

        polilinea_t **estrella=copiar_figura(figura_vector[3],457,364,0);
        for(size_t i=0; i<figura_cant_polilineas(figura_vector[3]);i++){
          graficar_polilinea(renderer,estrella[i],f);
        }
        destruir_figura(estrella,figura_cant_polilineas(figura_vector[3]));

        polilinea_t **planeta1=copiar_figura(figura_vector[4],663,473,0);
        for(size_t i=0; i<figura_cant_polilineas(figura_vector[4]);i++){
          graficar_polilinea(renderer,planeta1[i],f);
        }
        destruir_figura(planeta1,figura_cant_polilineas(figura_vector[4]));

        polilinea_t **planeta2=copiar_figura(figura_vector[5],671,145,0);
        for(size_t i=0; i<figura_cant_polilineas(figura_vector[5]);i++){
          graficar_polilinea(renderer,planeta2[i],f);
        }
        destruir_figura(planeta2,figura_cant_polilineas(figura_vector[5]));

        polilinea_t **planeta3=copiar_figura(figura_vector[6],110,79,0);
        for(size_t i=0; i<figura_cant_polilineas(figura_vector[6]);i++){
          graficar_polilinea(renderer,planeta3[i],f);
        }
        destruir_figura(planeta3,figura_cant_polilineas(figura_vector[6]));

        polilinea_t **planeta4=copiar_figura(figura_vector[7],204,455,0);
        for(size_t i=0; i<figura_cant_polilineas(figura_vector[7]);i++){
          graficar_polilinea(renderer,planeta4[i],f);
        }
        destruir_figura(planeta4,figura_cant_polilineas(figura_vector[7]));

        polilinea_t **planeta5=copiar_figura(figura_vector[8],111,307,0);
        for(size_t i=0; i<figura_cant_polilineas(figura_vector[8]);i++){
          graficar_polilinea(renderer,planeta5[i],f);
        }
        destruir_figura(planeta5,figura_cant_polilineas(figura_vector[8]));


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

    nave_destruir(navei);

    for(size_t i=0; i < n_figura; i++){
        figura_destruir(figura_vector[i],figura_cant_polilineas(figura_vector[i]),polilinea_destruir);
    }
    free(figura_vector);
    return 0;
}
