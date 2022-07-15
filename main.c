#include <SDL2/SDL.h>
#include <stdbool.h>
#include <string.h>

#include "config.h"
#include "tda_fisicaymatematica.h"
#include "tda_polilineas.h"

#include "tda_figuras.h"
#include "tda_nave.h"
#include "tda_nivel.h"
#include "tda_disparos.h"
#include "caracteres.h"
#include "tda_lista.h"


float nivel_calcular_escala(polilinea_t **p, size_t n, bool inf, float nave_pos_y,double *ancho){
  float f = 1;
  float x_max = 0;
  float y_max = 0;
  float x_min = VENTANA_ANCHO*100;
  for(size_t i=0; i<n; i++){
    if(x_max < polilinea_buscar_xmax(p[i]))
      x_max = polilinea_buscar_xmax(p[i]);
    if(x_min > polilinea_buscar_xmin(p[i]))
      x_min = polilinea_buscar_xmin(p[i]);
    if(y_max < polilinea_buscar_ymax(p[i]))
      y_max = polilinea_buscar_ymax(p[i]);
  }
  *ancho=x_max-x_min;
  if(inf) {
    if(nave_pos_y > VENTANA_ALTO * MARGEN_ALTURA)
      f = VENTANA_ALTO * MARGEN_ALTURA / nave_pos_y;
    if(f < ESCALA_MINIMA)
      f = ESCALA_MINIMA;
  }
  else{
    f = VENTANA_ALTO / y_max;
    if(VENTANA_ANCHO / (x_max + x_min) < f)
      f = VENTANA_ANCHO / (x_max + x_min);
  }
  return f;
}



polilinea_t **copiar_polilineas(figura_t *figura, double x, double y, double ang){
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

void destruir_vector_polilineas(polilinea_t **polilineas,size_t n){
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

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Gravitar");

    int dormir = 0;

    // BEGIN código del alumno
    size_t n_figura;
    figura_t **figura_vector = figura_leer_archivo(&n_figura);
    if(figura_vector == NULL)
        return 1;

    //VECTOR NIVELEEEESSSS
    size_t n_niveles=0;
    nivel_t **niveles=malloc(sizeof(nivel_t*));
    size_t tamanio=1;
    if(niveles==NULL){
      return 1;
    }
    for(size_t i=0;i<n_figura;i++){
      if(strcmp(figura_return_tipo(figura_vector[i]),"Nivel")==0){
        if(n_niveles==tamanio){
          tamanio++;
          nivel_t **aux=realloc(niveles,tamanio*sizeof(nivel_t*));
          if(aux==NULL){
            return 1;
          }
          niveles=aux;
        }
        nivel_t *nivel=nivel_crear(figura_return_nombre(figura_vector[i]),figura_return_inf(figura_vector[i]));
        if(nivel==NULL){
          return 1;
        }
        if(nivel_return_inf(nivel))
          nivel_set_escala_inicial(nivel, ESCALA_MINIMA);
        else {
          size_t can_polilineas = figura_cant_polilineas(figura_vector[i]);
          double anch;
          float f = nivel_calcular_escala(figura_return_vector_polilineas(figura_vector[i]), can_polilineas, NULL, 0,&anch);
          nivel_set_escala_inicial(nivel, f);
        }
        niveles[n_niveles++]=nivel;
      }
    }
    //TERMINA VECTOR NIVELES

    nave_t *navei=nave_crear(388,218);

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


    // Queremos que todo se dibuje escalado por f:
    float centro=0;
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
        /*float angulo_estrella=atan2(364-nave_get_posy(navei),457-nave_get_posx(navei));
        nave_mover(navei,a,angulo,angulo_estrella);
*/
        //ARRANCA NAVE
        size_t n_nave;
        polilinea_t **nave;
        if(nave_chorro_esta_prendido(navei)){
          nave=copiar_polilineas(figura_vector[chorro_en_vector],nave_get_posx(navei)-centro+ VENTANA_ANCHO / 2 / f,nave_get_posy(navei),nave_get_angulo(navei));
          n_nave=figura_cant_polilineas(figura_vector[chorro_en_vector]);
        }
        else{
          nave=copiar_polilineas(figura_vector[nave_en_vector],nave_get_posx(navei)-centro+ VENTANA_ANCHO / 2 / f,nave_get_posy(navei),nave_get_angulo(navei));
          n_nave=figura_cant_polilineas(figura_vector[nave_en_vector]);
        }

        if(nave_escudo_esta_prendido(navei)){
          polilinea_t **escudo=copiar_polilineas(figura_vector[escudo_en_vector],nave_get_posx(navei)-centro+ VENTANA_ANCHO / 2 / f,nave_get_posy(navei),nave_get_angulo(navei));
          for(size_t i=0; i<figura_cant_polilineas(figura_vector[escudo_en_vector]);i++){
            graficar_polilinea(renderer,escudo[i],f);
          }
          destruir_vector_polilineas(escudo,figura_cant_polilineas(figura_vector[escudo_en_vector]));
        }

        for(size_t i=0; i<n_nave;i++){
          graficar_polilinea(renderer, nave[i], f);
        }
        //TERMINA NAVE SE ELIMINA AL FINAL

        //ARRANCA NIVELES
        size_t indice_nivel;
        bool hay_nivel_activo=false;
        for(indice_nivel=0; indice_nivel<n_niveles; indice_nivel++){
          if(nivel_esta_activo(niveles[indice_nivel])){
            hay_nivel_activo=true;
            break;
          }
        }

        if(hay_nivel_activo){

          float angulo_estrella=0;
          nave_mover(navei,a,angulo,angulo_estrella);

          size_t nivel_en_figuras = figura_buscar(figura_vector,n_figura,nivel_nombre(niveles[indice_nivel]));

          size_t n_nivel=figura_cant_polilineas(figura_vector[nivel_en_figuras]);
          polilinea_t **nivel_polilinea=copiar_polilineas(figura_vector[nivel_en_figuras],(-centro+ VENTANA_ANCHO / 2 /f) ,0,0);

          double ancho_nivel;
          f = nivel_calcular_escala(nivel_polilinea, n_nivel, nivel_return_inf(niveles[indice_nivel]), nave_get_posy(navei),&ancho_nivel);

          if(nave_get_posy(navei) > VENTANA_ALTO/f) {
            nave_trasladar(navei,388,218,true);
            nivel_desactivar(niveles[indice_nivel]);
            f = 1;
          }
          if(!nivel_return_inf(niveles[indice_nivel])) {
            if(nave_get_posx(navei)<0 || nave_get_posx(navei)>VENTANA_ANCHO/f){
              nave_rebotar_x(navei);
            }
          }
          else{

            if((nave_get_posx(navei) - centro) * f > VENTANA_ANCHO / 2 * MARGEN_ANCHO){
              centro = nave_get_posx(navei) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / f;
            }
            else if((centro - nave_get_posx(navei)) * f > VENTANA_ANCHO / 2 * MARGEN_ANCHO){
              centro = nave_get_posx(navei) + VENTANA_ANCHO / 2 * MARGEN_ANCHO / f;
            }

            if(nave_get_posx(navei)>ancho_nivel){
              nave_trasladar(navei,nave_get_posx(navei)-ancho_nivel,nave_get_posy(navei),false);
            }
            else if(nave_get_posx(navei)<0){
              nave_trasladar(navei,nave_get_posx(navei)+ancho_nivel,nave_get_posy(navei),false);
            }

            polilinea_t **nivel_polilinea2=copiar_polilineas(figura_vector[nivel_en_figuras],(-centro+ VENTANA_ANCHO / 2 /f)+ancho_nivel ,0,0);
            polilinea_t **nivel_polilinea3=copiar_polilineas(figura_vector[nivel_en_figuras],(-centro+ VENTANA_ANCHO / 2 /f)-ancho_nivel ,0,0);

            for(size_t i=0; i<n_nivel;i++){
              graficar_polilinea(renderer,nivel_polilinea2[i],f);
              graficar_polilinea(renderer,nivel_polilinea3[i],f);
            }

            destruir_vector_polilineas(nivel_polilinea2,n_nivel);
            destruir_vector_polilineas(nivel_polilinea3,n_nivel);


          }


          if(nave_get_posy(navei)<0){
            nave_rebotar_y(navei);
          }

          for(size_t i=0; i<n_nivel;i++){
            if(distancia_punto_a_polilinea(nivel_polilinea[i],nave_get_posx(navei),nave_get_posy(navei))<=1){
              f = nivel_return_escala_inicial(niveles[indice_nivel]);
              nave_matar(navei,400/f,550/f);
            }
          }


          for(size_t i=0; i<n_nivel;i++){
            graficar_polilinea(renderer,nivel_polilinea[i],f);
          }

          destruir_vector_polilineas(nivel_polilinea,n_nivel);
        }
        //TERMINA NIVELES ARRANCA PANTALLA PRINCIPAL

        else{
          centro = VENTANA_ANCHO/2/f;

          float angulo_estrella=atan2(364-nave_get_posy(navei),457-nave_get_posx(navei));
          nave_mover(navei,a,angulo,angulo_estrella);

          size_t n_base=figura_cant_polilineas(figura_vector[base_en_vector]);
          polilinea_t **base=copiar_polilineas(figura_vector[base_en_vector],388-centro+ VENTANA_ANCHO / 2 / f,218,0);

          size_t n_estrella=figura_cant_polilineas(figura_vector[estrella_en_vector]);
          polilinea_t **estrella=copiar_polilineas(figura_vector[estrella_en_vector],457-centro+ VENTANA_ANCHO / 2 / f,364,0);

          size_t n_planeta1=figura_cant_polilineas(figura_vector[planeta1_en_vector]);
          polilinea_t **planeta1=copiar_polilineas(figura_vector[planeta1_en_vector],663-centro+ VENTANA_ANCHO / 2 / f,473,0);

          size_t n_planeta2=figura_cant_polilineas(figura_vector[planeta2_en_vector]);
          polilinea_t **planeta2=copiar_polilineas(figura_vector[planeta2_en_vector],671-centro+ VENTANA_ANCHO / 2 / f,145,0);

          size_t n_planeta3=figura_cant_polilineas(figura_vector[planeta3_en_vector]);
          polilinea_t **planeta3=copiar_polilineas(figura_vector[planeta3_en_vector],110-centro+ VENTANA_ANCHO / 2 / f,79,0);

          size_t n_planeta4=figura_cant_polilineas(figura_vector[planeta4_en_vector]);
          polilinea_t **planeta4=copiar_polilineas(figura_vector[planeta4_en_vector],204-centro+ VENTANA_ANCHO / 2 / f,455,0);

          size_t n_planeta5=figura_cant_polilineas(figura_vector[planeta5_en_vector]);
          polilinea_t **planeta5=copiar_polilineas(figura_vector[planeta5_en_vector],111-centro+ VENTANA_ANCHO / 2 / f,307,0);


          for(size_t i=0;i<n_estrella;i++){
            if(distancia_punto_a_polilinea(estrella[i],nave_get_posx(navei),nave_get_posy(navei))<=3){
              nave_matar(navei,388,218);
            }
          }

          for(size_t i=0;i<n_planeta1;i++){
            if(distancia_punto_a_polilinea(planeta1[i],nave_get_posx(navei),nave_get_posy(navei))<=10){
              size_t posicion_nivel = nivel_buscar(niveles, n_niveles, "NIVEL1NE");
              nivel_activar(niveles[posicion_nivel]);
              f = nivel_return_escala_inicial(niveles[posicion_nivel]);
              nave_trasladar(navei,400/f,500/f,true);
              centro=nave_get_posx(navei);
            }
          }

          for(size_t i=0;i<n_planeta2;i++){
            if(distancia_punto_a_polilinea(planeta2[i],nave_get_posx(navei),nave_get_posy(navei))<=10){
              size_t posicion_nivel = nivel_buscar(niveles, n_niveles, "NIVEL1SE");
              nivel_activar(niveles[posicion_nivel]);
              f = nivel_return_escala_inicial(niveles[posicion_nivel]);
              nave_trasladar(navei,400/f,500/f,true);
              centro=nave_get_posx(navei);
            }
          }

          for(size_t i=0;i<n_planeta3;i++){
            if(distancia_punto_a_polilinea(planeta3[i],nave_get_posx(navei),nave_get_posy(navei))<=10){
              size_t posicion_nivel = nivel_buscar(niveles, n_niveles, "NIVEL1SW");
              nivel_activar(niveles[posicion_nivel]);
              f = nivel_return_escala_inicial(niveles[posicion_nivel]);
              nave_trasladar(navei,400/f,500/f,true);
              centro=nave_get_posx(navei);
            }
          }

          for(size_t i=0;i<n_planeta4;i++){
            if(distancia_punto_a_polilinea(planeta4[i],nave_get_posx(navei),nave_get_posy(navei))<=10){
              size_t posicion_nivel = nivel_buscar(niveles, n_niveles, "NIVEL1NW");
              nivel_activar(niveles[posicion_nivel]);
              f = nivel_return_escala_inicial(niveles[posicion_nivel]);
              nave_trasladar(navei,400/f,500/f,true);
              centro=nave_get_posx(navei);
            }
          }

          for(size_t i=0;i<n_planeta5;i++){
            if(distancia_punto_a_polilinea(planeta5[i],nave_get_posx(navei),nave_get_posy(navei))<=10){
              size_t posicion_nivel = nivel_buscar(niveles, n_niveles, "NIVEL1R");
              nivel_activar(niveles[posicion_nivel]);
              f = nivel_return_escala_inicial(niveles[posicion_nivel]);
              nave_trasladar(navei,400/f,500/f,true);
              centro=nave_get_posx(navei);
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

          destruir_vector_polilineas(base, n_base);
          destruir_vector_polilineas(estrella, n_estrella);
          destruir_vector_polilineas(planeta1, n_planeta1);
          destruir_vector_polilineas(planeta2, n_planeta2);
          destruir_vector_polilineas(planeta3, n_planeta3);
          destruir_vector_polilineas(planeta4, n_planeta4);
          destruir_vector_polilineas(planeta5, n_planeta5);

        }

        //ZONA DESTRUIR

        destruir_vector_polilineas(nave,n_nave);



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

    for(size_t i=0; i<n_niveles; i++){
      nivel_destruir(niveles[i]);
    }
    free(niveles);

    for(size_t i=0; i < n_figura; i++){
        figura_destruir(figura_vector[i],figura_cant_polilineas(figura_vector[i]),polilinea_destruir);
    }
    free(figura_vector);


    return 0;
}
