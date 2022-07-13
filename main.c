#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "tda_fisicaymatematica.h"
#include "tda_polilineas.h"

#include "tda_figuras.h"
#include "tda_nave.h"
#include "tda_nivel.h"
#include "tda_disparos.h"

#include "tda_lista.h"



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
    nave_t *navei=nave_crear(388,218);
    nivel_t *nivel1=crear_nivel();
    nivel_t *nivel2=crear_nivel();
    nivel_t *nivel3=crear_nivel();
    nivel_t *nivel4=crear_nivel();
    nivel_t *nivel5=crear_nivel();


    float a=0;
    float angulo = 0;

    size_t base_en_vector = figura_buscar(figura_vector,n_figura,"BASE");
    size_t estrella_en_vector = figura_buscar(figura_vector,n_figura,"ESTRELLA");
    size_t planeta1_en_vector = figura_buscar(figura_vector,n_figura,"PLANETA1");
    size_t planeta2_en_vector = figura_buscar(figura_vector,n_figura,"PLANETA2");
    size_t planeta3_en_vector = figura_buscar(figura_vector,n_figura,"PLANETA3");
    size_t planeta4_en_vector = figura_buscar(figura_vector,n_figura,"PLANETA4");
    size_t planeta5_en_vector = figura_buscar(figura_vector,n_figura,"PLANETA5");
    size_t nave_en_vector = figura_buscar(figura_vector,n_figura,"NAVE");
    size_t chorro_en_vector = figura_buscar(figura_vector,n_figura,"NAVE+CHORRO");
    size_t escudo_en_vector = figura_buscar(figura_vector,n_figura,"ESCUDO2");
    size_t nivel1_en_vector = figura_buscar(figura_vector,n_figura,"NIVEL1NE");
    size_t nivel2_en_vector = figura_buscar(figura_vector,n_figura,"NIVEL1SE");
    size_t nivel3_en_vector = figura_buscar(figura_vector,n_figura,"NIVEL1SW");
    size_t nivel4_en_vector = figura_buscar(figura_vector,n_figura,"NIVEL1NW");
    size_t nivel5_en_vector = figura_buscar(figura_vector,n_figura,"NIVEL1R");




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
                    case SDLK_SPACE:

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
                    case SDLK_SPACE:
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
        float angulo_estrella=atan2(364-nave_get_posy(navei),457-nave_get_posx(navei));
        nave_mover(navei,a,angulo,angulo_estrella);


        //ZONA CREAR
        size_t n_nave;
        polilinea_t **nave;
        if(nave_chorro_esta_prendido(navei)){
          nave=copiar_figura(figura_vector[chorro_en_vector],nave_get_posx(navei),nave_get_posy(navei),nave_get_angulo(navei));
          n_nave=figura_cant_polilineas(figura_vector[chorro_en_vector]);
        }
        else{
          nave=copiar_figura(figura_vector[nave_en_vector],nave_get_posx(navei),nave_get_posy(navei),nave_get_angulo(navei));
          n_nave=figura_cant_polilineas(figura_vector[nave_en_vector]);
        }

        if(nave_escudo_esta_prendido(navei)){
          polilinea_t **escudo=copiar_figura(figura_vector[escudo_en_vector],nave_get_posx(navei),nave_get_posy(navei),nave_get_angulo(navei));
          for(size_t i=0; i<figura_cant_polilineas(figura_vector[escudo_en_vector]);i++){
            graficar_polilinea(renderer,escudo[i],f);
          }
          destruir_figura(escudo,figura_cant_polilineas(figura_vector[18]));
        }



        size_t n_base=figura_cant_polilineas(figura_vector[base_en_vector]);
        polilinea_t **base=copiar_figura(figura_vector[base_en_vector],388,218,0);

        size_t n_estrella=figura_cant_polilineas(figura_vector[estrella_en_vector]);
        polilinea_t **estrella=copiar_figura(figura_vector[estrella_en_vector],457,364,0);

        size_t n_planeta1=figura_cant_polilineas(figura_vector[planeta1_en_vector]);
        polilinea_t **planeta1=copiar_figura(figura_vector[planeta1_en_vector],663,473,0);

        size_t n_planeta2=figura_cant_polilineas(figura_vector[planeta2_en_vector]);
        polilinea_t **planeta2=copiar_figura(figura_vector[planeta2_en_vector],671,145,0);

        size_t n_planeta3=figura_cant_polilineas(figura_vector[planeta3_en_vector]);
        polilinea_t **planeta3=copiar_figura(figura_vector[planeta3_en_vector],110,79,0);

        size_t n_planeta4=figura_cant_polilineas(figura_vector[planeta4_en_vector]);
        polilinea_t **planeta4=copiar_figura(figura_vector[planeta4_en_vector],204,455,0);

        size_t n_planeta5=figura_cant_polilineas(figura_vector[planeta5_en_vector]);
        polilinea_t **planeta5=copiar_figura(figura_vector[planeta5_en_vector],111,307,0);


        size_t n_nivel1=figura_cant_polilineas(figura_vector[nivel1_en_vector]);
        polilinea_t **nivel1p=copiar_figura(figura_vector[nivel1_en_vector],0,0,0);

        size_t n_nivel2=figura_cant_polilineas(figura_vector[nivel2_en_vector]);
        polilinea_t **nivel2p=copiar_figura(figura_vector[nivel2_en_vector],0,0,0);

        size_t n_nivel3=figura_cant_polilineas(figura_vector[nivel3_en_vector]);
        polilinea_t **nivel3p=copiar_figura(figura_vector[nivel3_en_vector],0,0,0);

        size_t n_nivel4=figura_cant_polilineas(figura_vector[nivel4_en_vector]);
        polilinea_t **nivel4p=copiar_figura(figura_vector[nivel4_en_vector],0,0,0);

        size_t n_nivel5=figura_cant_polilineas(figura_vector[nivel5_en_vector]);
        polilinea_t **nivel5p=copiar_figura(figura_vector[nivel5_en_vector],0,0,0);


        if(nivel_esta_activo(nivel1)){

          for(size_t i=0; i<n_nivel1;i++){
            graficar_polilinea(renderer,nivel1p[i],f);
          }

        }
        else if(nivel_esta_activo(nivel2)){

          for(size_t i=0; i<n_nivel2;i++){
            graficar_polilinea(renderer,nivel2p[i],f);
          }

        }
        else if(nivel_esta_activo(nivel3)){

          for(size_t i=0; i<n_nivel3;i++){
            graficar_polilinea(renderer,nivel3p[i],f);
          }
          
        }
        else if(nivel_esta_activo(nivel4)){
          f=0.63;

          for(size_t i=0; i<n_nivel4;i++){
            graficar_polilinea(renderer,nivel4p[i],f);
          }

        }
        else if(nivel_esta_activo(nivel5)){

          for(size_t i=0; i<n_nivel5;i++){
            graficar_polilinea(renderer,nivel5p[i],f);
          }

        }
        else{
          //ZONA DECIDIR

          for(size_t i=0;i<n_estrella;i++){
            if(distancia_punto_a_polilinea(estrella[i],nave_get_posx(navei),nave_get_posy(navei))<=3){
              nave_matar(navei,388,218);
            }
          }

          for(size_t i=0;i<n_planeta1;i++){
            if(distancia_punto_a_polilinea(planeta1[i],nave_get_posx(navei),nave_get_posy(navei))<=10){
              nivel_activar(nivel1);

            }
          }

          for(size_t i=0;i<n_planeta2;i++){
            if(distancia_punto_a_polilinea(planeta2[i],nave_get_posx(navei),nave_get_posy(navei))<=10){
              nivel_activar(nivel2);

            }
          }

          for(size_t i=0;i<n_planeta3;i++){
            if(distancia_punto_a_polilinea(planeta3[i],nave_get_posx(navei),nave_get_posy(navei))<=10){
              nivel_activar(nivel3);

            }
          }

          for(size_t i=0;i<n_planeta4;i++){
            if(distancia_punto_a_polilinea(planeta4[i],nave_get_posx(navei),nave_get_posy(navei))<=10){
              nivel_activar(nivel4);

            }
          }

          for(size_t i=0;i<n_planeta5;i++){
            if(distancia_punto_a_polilinea(planeta5[i],nave_get_posx(navei),nave_get_posy(navei))<=10){
              nivel_activar(nivel5);

            }
          }

          if(nave_get_posx(navei)<0 || nave_get_posx(navei)>VENTANA_ANCHO){
            nave_rebotar_x(navei);
          }
          if(nave_get_posy(navei)<0 || nave_get_posy(navei)>VENTANA_ALTO){
            nave_rebotar_y(navei);
          }


          //ZONA GRAFICAR
          for(size_t i=0; i<n_base;i++){
            graficar_polilinea(renderer,base[i],f);
          }

          for(size_t i=0; i<n_nave;i++){
            graficar_polilinea(renderer,nave[i],f);
          }

          for(size_t i=0; i<n_estrella;i++){
            graficar_polilinea(renderer,estrella[i],f);
          }

          for(size_t i=0; i<n_planeta1;i++){
            graficar_polilinea(renderer,planeta1[i],f);
          }

          for(size_t i=0; i<n_planeta2;i++){
            graficar_polilinea(renderer,planeta2[i],f);
          }

          for(size_t i=0; i<n_planeta3;i++){
            graficar_polilinea(renderer,planeta3[i],f);
          }

          for(size_t i=0; i<n_planeta4;i++){
            graficar_polilinea(renderer,planeta4[i],f);
          }

          for(size_t i=0; i<n_planeta5;i++){
            graficar_polilinea(renderer,planeta5[i],f);
          }


        }

        //ZONA DESTRUIR


        destruir_figura(nivel1p,n_nivel1);
        destruir_figura(nivel2p,n_nivel2);
        destruir_figura(nivel3p,n_nivel3);
        destruir_figura(nivel4p,n_nivel4);
        destruir_figura(nivel5p,n_nivel5);

        destruir_figura(nave,n_nave);

        destruir_figura(base,figura_cant_polilineas(figura_vector[2]));
        destruir_figura(estrella,figura_cant_polilineas(figura_vector[3]));
        destruir_figura(planeta1,figura_cant_polilineas(figura_vector[4]));
        destruir_figura(planeta2,figura_cant_polilineas(figura_vector[5]));
        destruir_figura(planeta3,figura_cant_polilineas(figura_vector[6]));
        destruir_figura(planeta4,figura_cant_polilineas(figura_vector[7]));
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
    nivel_destruir(nivel1);
    nivel_destruir(nivel2);
    nivel_destruir(nivel3);
    nivel_destruir(nivel4);
    nivel_destruir(nivel5);

    for(size_t i=0; i < n_figura; i++){
        figura_destruir(figura_vector[i],figura_cant_polilineas(figura_vector[i]),polilinea_destruir);
    }
    free(figura_vector);
    return 0;
}
