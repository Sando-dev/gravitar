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
#include "lista.h"
#include "encabezado.h"
#include "tda_torreta.h"
#include "tda_fuel.h"

typedef struct {
  char *nombre;
  double posx;
  double posy;
  char *nivel;
} planetas_niveles_t;

planetas_niveles_t planetas_niveles[]={
  {"PLANETA1",PLAN1_POSICION_X, PLAN1_POSICION_Y,"NIVEL1NE"},
  {"PLANETA2",PLAN2_POSICION_X, PLAN2_POSICION_Y,"NIVEL1SE"},
  {"PLANETA3",PLAN3_POSICION_X, PLAN3_POSICION_Y,"NIVEL1SW"},
  {"PLANETA4",PLAN4_POSICION_X, PLAN4_POSICION_Y,"NIVEL1NW"},
  {"PLANETA5",PLAN5_POSICION_X, PLAN5_POSICION_Y,"NIVEL1R"},
};

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
    encabezado_t *e = encabezado_crear();
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

    nave_t *navei=nave_crear(BASE_POSICION_X,BASE_POSICION_Y  );

    float a=0;
    float angulo = 0;
    float angulo_estrella = atan2(ESTRELLA_POSICION_Y-nave_get_posy(navei),ESTRELLA_POSICION_X-nave_get_posx(navei));

    size_t base_en_vector = figura_buscar(figura_vector,n_figura,"BASE");
    size_t estrella_en_vector = figura_buscar(figura_vector,n_figura,"ESTRELLA");
    size_t nave_en_vector = figura_buscar(figura_vector,n_figura,"NAVE");
    size_t chorro_en_vector = figura_buscar(figura_vector,n_figura,"NAVE+CHORRO");
    size_t escudo_en_vector = figura_buscar(figura_vector,n_figura,"ESCUDO2");
    size_t disparo_en_vector = figura_buscar(figura_vector,n_figura,"DISPARO");
    size_t fuel_en_vector = figura_buscar(figura_vector, n_figura, "COMBUSTIBLE");
    size_t torreta_en_vector = figura_buscar(figura_vector,n_figura,"TORRETA");
    size_t reactor_en_vector = figura_buscar(figura_vector,n_figura,"REACTOR");

    size_t n_planetas= sizeof(planetas_niveles) / sizeof(planetas_niveles[0]);
    int next_ship=10000;
    float tiempo_coldown_torretas=0;
    float centro=0;
    float f = 1;
    lista_t *disparos=lista_crear();
    lista_t *torretas_lista = lista_crear();
    lista_t *torreta_disparos= lista_crear();
    lista_t *fuel_lista = lista_crear();
    lista_t *reactor_lista = lista_crear();
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
                        lista_insertar_ultimo(disparos,crear_disparo(nave_get_posx(navei),nave_get_posy(navei),nave_get_angulo(navei)));
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

        //ARRANCA NAVE
        size_t n_nave;
        polilinea_t **nave;
        if(nave_chorro_esta_prendido(navei)){
          nave=copiar_polilineas(figura_vector[chorro_en_vector],nave_get_posx(navei),nave_get_posy(navei),nave_get_angulo(navei));
          n_nave=figura_cant_polilineas(figura_vector[chorro_en_vector]);
        }
        else{
          nave=copiar_polilineas(figura_vector[nave_en_vector],nave_get_posx(navei),nave_get_posy(navei),nave_get_angulo(navei));
          n_nave=figura_cant_polilineas(figura_vector[nave_en_vector]);
        }

        nave_mover(navei,a,angulo,angulo_estrella);
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
          tiempo_coldown_torretas+=(float)1/JUEGO_FPS;
          angulo_estrella=((float)3/2)*PI;


          lista_iterar(disparos,disparo_mover,NULL);
          lista_iterar(torreta_disparos,disparo_mover,NULL);

          size_t nivel_en_figuras = figura_buscar(figura_vector,n_figura,nivel_nombre(niveles[indice_nivel]));

          size_t n_nivel=figura_cant_polilineas(figura_vector[nivel_en_figuras]);
          polilinea_t **nivel_polilinea=copiar_polilineas(figura_vector[nivel_en_figuras],0,0,0);

          polilinea_t **escudo=copiar_polilineas(figura_vector[escudo_en_vector],nave_get_posx(navei),nave_get_posy(navei),nave_get_angulo(navei)-NAVE_ANGULO_INICIAL);
          size_t n_escudo=figura_cant_polilineas(figura_vector[escudo_en_vector]);

          double ancho_nivel;
          f = nivel_calcular_escala(nivel_polilinea, n_nivel, nivel_return_inf(niveles[indice_nivel]), nave_get_posy(navei),&ancho_nivel);

          lista_iter_t *iter_disparos=lista_iter_crear(disparos);
          while(!lista_iter_al_final(iter_disparos)){
            disparo_t *disparo=lista_iter_ver_actual(iter_disparos);
            size_t n_disparo=figura_cant_polilineas(figura_vector[disparo_en_vector]);
            polilinea_t **disparo_polilinea=copiar_polilineas(figura_vector[disparo_en_vector],disparo_get_posx(disparo),disparo_get_posy(disparo),disparo_get_angulo(disparo));
            for(size_t i=0; i<n_nivel;i++){
              if(distancia_punto_a_polilinea(nivel_polilinea[i],disparo_get_posx(disparo),disparo_get_posy(disparo))<=1){
                lista_iter_borrar(iter_disparos);
                free(disparo);
                break;
              }
            }
            destruir_vector_polilineas(disparo_polilinea,n_disparo);
            lista_iter_avanzar(iter_disparos);
          }
          lista_iter_destruir(iter_disparos);


          lista_iter_t *iter_disparos_torretas=lista_iter_crear(torreta_disparos);
          while(!lista_iter_al_final(iter_disparos_torretas)){
            disparo_t *disparo=lista_iter_ver_actual(iter_disparos_torretas);
            size_t n_disparo=figura_cant_polilineas(figura_vector[disparo_en_vector]);
            polilinea_t **disparo_polilinea=copiar_polilineas(figura_vector[disparo_en_vector],disparo_get_posx(disparo),disparo_get_posy(disparo),disparo_get_angulo(disparo));

            if(norma(disparo_get_posx(disparo)-nave_get_posx(navei),disparo_get_posy(disparo)-nave_get_posy(navei))<=5){
              if(nave_escudo_esta_prendido(navei)){
                lista_iter_borrar(iter_disparos_torretas);
                free(disparo);
              }
              else{
                f = nivel_return_escala_inicial(niveles[indice_nivel]);
                nave_matar(navei,400/f,500/f);
                centro=nave_get_posx(navei);
                lista_iter_borrar(iter_disparos_torretas);
                free(disparo);
              }
              destruir_vector_polilineas(disparo_polilinea,n_disparo);
              lista_iter_avanzar(iter_disparos_torretas);
              continue;
            }

            for(size_t i=0; i<n_nivel;i++){
              if(distancia_punto_a_polilinea(nivel_polilinea[i],disparo_get_posx(disparo),disparo_get_posy(disparo))<=0.2){
                lista_iter_borrar(iter_disparos_torretas);
                free(disparo);
                break;
              }
            }

            destruir_vector_polilineas(disparo_polilinea,n_disparo);
            lista_iter_avanzar(iter_disparos_torretas);
          }
          lista_iter_destruir(iter_disparos_torretas);



          lista_iter_t *iter_torretas = lista_iter_crear(torretas_lista);
          while(!lista_iter_al_final(iter_torretas)){
            torreta_t *torreta = lista_iter_ver_actual(iter_torretas);
            if(torreta_vive(torreta)){
              size_t n_torreta = figura_cant_polilineas(figura_vector[torreta_en_vector]);
              polilinea_t **torreta_polilinea = copiar_polilineas(figura_vector[torreta_en_vector], torreta_get_posx(torreta), torreta_get_posy(torreta), torreta_get_angulo(torreta));

              if(norma(torreta_get_posx(torreta)-nave_get_posx(navei),torreta_get_posy(torreta)-nave_get_posy(navei))<250 && tiempo_coldown_torretas>0.5){
                float angulo_disparo=atan2(nave_get_posy(navei)-torreta_get_posy(torreta),nave_get_posx(navei)-torreta_get_posx(torreta));
                lista_insertar_ultimo(torreta_disparos,crear_disparo(torreta_get_posx(torreta),torreta_get_posy(torreta),angulo_disparo));
                tiempo_coldown_torretas=0;
              }

              lista_iter_t *iter_disparos=lista_iter_crear(disparos);
              while(!lista_iter_al_final(iter_disparos)){
                disparo_t *disparo=lista_iter_ver_actual(iter_disparos);
                for(size_t i=0; i<n_torreta;i++){
                  if(distancia_punto_a_polilinea(torreta_polilinea[i],disparo_get_posx(disparo),disparo_get_posy(disparo))<=1){
                    torreta_matar(torreta);
                    torreta_diccionario_matar(torreta_get_posx(torreta), torreta_get_posy(torreta), nivel_nombre(niveles[indice_nivel]));
                    encabezado_torreta_matada(e);
                    lista_iter_borrar(iter_disparos);
                    free(disparo);
                    break;
                  }
                }
                lista_iter_avanzar(iter_disparos);
              }
              destruir_vector_polilineas(torreta_polilinea,n_torreta);
              lista_iter_destruir(iter_disparos);
            }
            lista_iter_avanzar(iter_torretas);
          }
          lista_iter_destruir(iter_torretas);


          lista_iter_t *iter_fuel_lista = lista_iter_crear(fuel_lista);
          while(!lista_iter_al_final(iter_fuel_lista)){
            fuel_t *fuel = lista_iter_ver_actual(iter_fuel_lista);
            if(fuel_vive(fuel)){
              size_t n_fuel = figura_cant_polilineas(figura_vector[fuel_en_vector]);
              polilinea_t **fuel_polilinea = copiar_polilineas(figura_vector[fuel_en_vector],fuel_get_posx(fuel), fuel_get_posy(fuel), fuel_get_ang(fuel));

              if(nave_escudo_esta_prendido(navei)){
                for(size_t i=0; i<n_escudo; i++){
                  if(distancia_punto_a_polilinea(escudo[i],fuel_get_posx(fuel),fuel_get_posy(fuel))<=15){
                    fuel_matar(fuel);
                    fuel_diccionario_taken(fuel_get_posx(fuel),fuel_get_posy(fuel),nivel_nombre(niveles[indice_nivel]));
                    nave_add_fuel(navei);
                    break;
                  }
                }
              }
              destruir_vector_polilineas(fuel_polilinea,n_fuel);
            }
            lista_iter_avanzar(iter_fuel_lista);
          }
          lista_iter_destruir(iter_fuel_lista);



          lista_iter_t *iter_reactor_lista = lista_iter_crear(reactor_lista);
          while(!lista_iter_al_final(iter_reactor_lista)){
            reactor_t *reactor = lista_iter_ver_actual(iter_reactor_lista);
            if(reactor_get_alive(reactor)){
              size_t n_reactor = figura_cant_polilineas(figura_vector[reactor_en_vector]);
              polilinea_t **reactor_polilinea = copiar_polilineas(figura_vector[reactor_en_vector], reactor_get_posx(reactor), reactor_get_posy(reactor), reactor_get_angulo(reactor));

              lista_iter_t *iter_disparos=lista_iter_crear(disparos);
              while(!lista_iter_al_final(iter_disparos)){
                disparo_t *disparo=lista_iter_ver_actual(iter_disparos);
                for(size_t i=0; i<n_reactor;i++){
                  if(distancia_punto_a_polilinea(reactor_polilinea[i],disparo_get_posx(disparo),disparo_get_posy(disparo))<=1){
                    reactor_matar(reactor);
                    torreta_diccionario_matar(reactor_get_posx(reactor), reactor_get_posy(reactor), nivel_nombre(niveles[indice_nivel]));
                    lista_iter_borrar(iter_disparos);
                    free(disparo);
                    break;
                  }
                }
                lista_iter_avanzar(iter_disparos);
              }
              destruir_vector_polilineas(reactor_polilinea,n_reactor);
              lista_iter_destruir(iter_disparos);

              encabezado_set_timer(e,25-reactor_get_time(reactor));
              reactor_pasa_tiempo(reactor);
              if(reactor_explotar(reactor)){
                  nave_matar(navei,BASE_POSICION_X,BASE_POSICION_Y);
                  nivel_desactivar(niveles[indice_nivel]);
                  lista_destruir(disparos,free);
                  disparos=lista_crear();
                  lista_destruir(torretas_lista,free);
                  torretas_lista = lista_crear();
                  lista_destruir(fuel_lista,free);
                  lista_destruir(torreta_disparos,free);
                  lista_destruir(reactor_lista, free);
                  reactor_lista = lista_crear();
                  torreta_disparos=lista_crear();
                  fuel_lista = lista_crear();
                  f = 1;
                  encabezado_set_timer(e,0);
                  encabezado_set_lvl_completed(e,false);
              }
            }
            lista_iter_avanzar(iter_reactor_lista);
          }
          lista_iter_destruir(iter_reactor_lista);
          if(lista_esta_vacia(fuel_lista) & lista_esta_vacia(reactor_lista) && lista_esta_vacia(torretas_lista))
            encabezado_set_lvl_completed(e,true);

          if(nave_get_posy(navei) > VENTANA_ALTO/f) {
            if(lista_esta_vacia(fuel_lista) & lista_esta_vacia(reactor_lista) && lista_esta_vacia(torretas_lista))
              encabezado_nivel_completado(e,nivel_nombre(niveles[indice_nivel]));
            nave_trasladar(navei,BASE_POSICION_X,BASE_POSICION_Y,true);
            nivel_desactivar(niveles[indice_nivel]);
            lista_destruir(disparos,free);
            disparos=lista_crear();
            lista_destruir(torretas_lista,free);
            torretas_lista = lista_crear();
            lista_destruir(fuel_lista,free);
            lista_destruir(torreta_disparos,free);
            lista_destruir(reactor_lista, free);
            reactor_lista = lista_crear();
            torreta_disparos=lista_crear();
            fuel_lista = lista_crear();
            f = 1;
            encabezado_set_timer(e,0);
            encabezado_set_lvl_completed(e,false);
          }

          if(nave_get_posy(navei)<0){
            nave_rebotar_y(navei);
          }

          for(size_t i=0; i<n_nivel;i++){
            if(distancia_punto_a_polilinea(nivel_polilinea[i],nave_get_posx(navei),nave_get_posy(navei))<=1){
              f = nivel_return_escala_inicial(niveles[indice_nivel]);
              nave_matar(navei,400/f,500/f);
              centro=nave_get_posx(navei);
            }
          }

          if(!nivel_return_inf(niveles[indice_nivel])) {
            if(nave_get_posx(navei)<0 || nave_get_posx(navei)>VENTANA_ANCHO/f){
              nave_rebotar_x(navei);
            }
          }
          else{
            if((nave_get_posx(navei) - centro) * f > VENTANA_ANCHO / 2 * MARGEN_ANCHO  ){
              centro = nave_get_posx(navei) - VENTANA_ANCHO / 2 * MARGEN_ANCHO / f ;
            }
            else if((centro - nave_get_posx(navei)) * f > VENTANA_ANCHO / 2 * MARGEN_ANCHO  ){
              centro = nave_get_posx(navei)+ VENTANA_ANCHO / 2 * MARGEN_ANCHO / f ;
            }

            if(nave_get_posx(navei)>ancho_nivel){
              nave_trasladar(navei,nave_get_posx(navei)-ancho_nivel,nave_get_posy(navei),false);
              centro-=ancho_nivel;

            }
            else if(nave_get_posx(navei)<0){
              nave_trasladar(navei,nave_get_posx(navei)+ancho_nivel,nave_get_posy(navei),false);
              centro+=ancho_nivel;
            }

            polilinea_t **nivel_polilinea2=copiar_polilineas(figura_vector[nivel_en_figuras],(-centro+ VENTANA_ANCHO / 2 /f)+ancho_nivel ,0,0);
            polilinea_t **nivel_polilinea3=copiar_polilineas(figura_vector[nivel_en_figuras],(-centro+ VENTANA_ANCHO / 2 /f)-ancho_nivel ,0,0);



            for(size_t i=0; i<n_nivel;i++){
              graficar_polilinea(renderer,nivel_polilinea2[i],f);
              graficar_polilinea(renderer,nivel_polilinea3[i],f);
            }

            lista_iter_t *iter_torretas = lista_iter_crear(torretas_lista);
            while(!lista_iter_al_final(iter_torretas)){
              torreta_t *torreta = lista_iter_ver_actual(iter_torretas);
              if(torreta_vive(torreta)){
                size_t n_torreta = figura_cant_polilineas(figura_vector[torreta_en_vector]);
                polilinea_t **torreta_polilinea2 = copiar_polilineas(figura_vector[torreta_en_vector], torreta_get_posx(torreta)-centro+ VENTANA_ANCHO / 2 / f +ancho_nivel, torreta_get_posy(torreta), torreta_get_angulo(torreta));
                polilinea_t **torreta_polilinea3 = copiar_polilineas(figura_vector[torreta_en_vector], torreta_get_posx(torreta)-centro+ VENTANA_ANCHO / 2 / f -ancho_nivel, torreta_get_posy(torreta), torreta_get_angulo(torreta));
                for(size_t i=0; i<n_torreta;i++){
                  graficar_polilinea(renderer,torreta_polilinea2[i],f);
                  graficar_polilinea(renderer,torreta_polilinea3[i],f);
                }
                destruir_vector_polilineas(torreta_polilinea2,n_torreta);
                destruir_vector_polilineas(torreta_polilinea3,n_torreta);
              }
              lista_iter_avanzar(iter_torretas);
            }
            lista_iter_destruir(iter_torretas);



            lista_iter_t *iter_fuel_lista = lista_iter_crear(fuel_lista);
            while(!lista_iter_al_final(iter_fuel_lista)){
              fuel_t *fuel = lista_iter_ver_actual(iter_fuel_lista);
              if(fuel_vive(fuel)){
                size_t n_fuel = figura_cant_polilineas(figura_vector[fuel_en_vector]);
                polilinea_t **fuel_polilinea2 = copiar_polilineas(figura_vector[fuel_en_vector], fuel_get_posx(fuel)-centro+ VENTANA_ANCHO / 2 / f +ancho_nivel, fuel_get_posy(fuel), fuel_get_ang(fuel));
                polilinea_t **fuel_polilinea3 = copiar_polilineas(figura_vector[fuel_en_vector], fuel_get_posx(fuel)-centro+ VENTANA_ANCHO / 2 / f -ancho_nivel, fuel_get_posy(fuel), fuel_get_ang(fuel));
                for(size_t i=0; i<n_fuel;i++){
                  graficar_polilinea(renderer,fuel_polilinea2[i],f);
                  graficar_polilinea(renderer,fuel_polilinea3[i],f);
                }
                destruir_vector_polilineas(fuel_polilinea2,n_fuel);
                destruir_vector_polilineas(fuel_polilinea3,n_fuel);
              }
              lista_iter_avanzar(iter_fuel_lista);
            }
            lista_iter_destruir(iter_fuel_lista);

            destruir_vector_polilineas(nivel_polilinea2,n_nivel);
            destruir_vector_polilineas(nivel_polilinea3,n_nivel);


          }


          for(size_t i=0; i<n_nivel;i++){
            trasladar(nivel_polilinea[i],-centro + VENTANA_ANCHO / 2 / f, 0);
            graficar_polilinea(renderer,nivel_polilinea[i],f);
          }

          if(nave_escudo_esta_prendido(navei)){
            for(size_t i=0; i<n_escudo;i++){
              trasladar(escudo[i],-centro + VENTANA_ANCHO / 2 / f, 0);
              graficar_polilinea(renderer,escudo[i],f);
            }
          }

          lista_iter_t *iter_disparos2=lista_iter_crear(disparos);
          while(!lista_iter_al_final(iter_disparos2)){
            disparo_t *disparo=lista_iter_ver_actual(iter_disparos2);
            size_t n_disparo=figura_cant_polilineas(figura_vector[disparo_en_vector]);
            polilinea_t **disparo_polilinea=copiar_polilineas(figura_vector[disparo_en_vector],disparo_get_posx(disparo) - centro + VENTANA_ANCHO / 2 /f,disparo_get_posy(disparo),disparo_get_angulo(disparo));
            for(size_t i=0; i<n_disparo;i++){
              graficar_polilinea(renderer,disparo_polilinea[i],f);
            }
            destruir_vector_polilineas(disparo_polilinea,n_disparo);
            lista_iter_avanzar(iter_disparos2);
          }
          lista_iter_destruir(iter_disparos2);

          lista_iter_t *iter_disparos_torretas2=lista_iter_crear(torreta_disparos);
          while(!lista_iter_al_final(iter_disparos_torretas2)){
            disparo_t *disparo=lista_iter_ver_actual(iter_disparos_torretas2);
            size_t n_disparo=figura_cant_polilineas(figura_vector[disparo_en_vector]);
            polilinea_t **disparo_polilinea=copiar_polilineas(figura_vector[disparo_en_vector],disparo_get_posx(disparo) - centro + VENTANA_ANCHO / 2 / f,disparo_get_posy(disparo),disparo_get_angulo(disparo));

            for(size_t i=0; i<n_disparo;i++){
              graficar_polilinea(renderer,disparo_polilinea[i],f);
            }
            destruir_vector_polilineas(disparo_polilinea,n_disparo);
            lista_iter_avanzar(iter_disparos_torretas2);
          }
          lista_iter_destruir(iter_disparos_torretas2);

          lista_iter_t *iter_torretas2 = lista_iter_crear(torretas_lista);
          while(!lista_iter_al_final(iter_torretas2)){
            torreta_t *torreta = lista_iter_ver_actual(iter_torretas2);
            if(torreta_vive(torreta)){
              size_t n_torreta = figura_cant_polilineas(figura_vector[torreta_en_vector]);
              polilinea_t **torreta_polilinea = copiar_polilineas(figura_vector[torreta_en_vector], torreta_get_posx(torreta) - centro + VENTANA_ANCHO / 2 / f, torreta_get_posy(torreta), torreta_get_angulo(torreta));
              for(size_t i=0; i<n_torreta;i++){
                graficar_polilinea(renderer,torreta_polilinea[i],f);
              }

              destruir_vector_polilineas(torreta_polilinea,n_torreta);
            }
            lista_iter_avanzar(iter_torretas2);
          }
          lista_iter_destruir(iter_torretas2);

          lista_iter_t *iter_fuel_lista2 = lista_iter_crear(fuel_lista);
          while(!lista_iter_al_final(iter_fuel_lista2)){
            fuel_t *fuel = lista_iter_ver_actual(iter_fuel_lista2);
            if(fuel_vive(fuel)){
              size_t n_fuel = figura_cant_polilineas(figura_vector[fuel_en_vector]);
              polilinea_t **fuel_polilinea = copiar_polilineas(figura_vector[fuel_en_vector],fuel_get_posx(fuel)- centro + VENTANA_ANCHO / 2 / f, fuel_get_posy(fuel), fuel_get_ang(fuel));
              for(size_t i=0; i<n_fuel;i++){
                graficar_polilinea(renderer,fuel_polilinea[i],f);
              }
              destruir_vector_polilineas(fuel_polilinea,n_fuel);
            }
            lista_iter_avanzar(iter_fuel_lista2);
          }
          lista_iter_destruir(iter_fuel_lista2);

          lista_iter_t *iter_reactor_lista2 = lista_iter_crear(reactor_lista);
          while(!lista_iter_al_final(iter_reactor_lista2)){
            reactor_t *reactor = lista_iter_ver_actual(iter_reactor_lista2);
            if(reactor_get_alive(reactor)){
              size_t n_reactor = figura_cant_polilineas(figura_vector[reactor_en_vector]);
              polilinea_t **reactor_polilinea = copiar_polilineas(figura_vector[reactor_en_vector], reactor_get_posx(reactor) - centro + VENTANA_ANCHO / 2 / f, reactor_get_posy(reactor), reactor_get_angulo(reactor));
              for(size_t i=0; i<n_reactor;i++){
                graficar_polilinea(renderer,reactor_polilinea[i],f);
              }
              destruir_vector_polilineas(reactor_polilinea,n_reactor);
            }
            lista_iter_avanzar(iter_reactor_lista2);
          }
          lista_iter_destruir(iter_reactor_lista2);

          destruir_vector_polilineas(escudo,n_escudo);
          destruir_vector_polilineas(nivel_polilinea,n_nivel);



        }
        //TERMINA NIVELES ARRANCA PANTALLA PRINCIPAL

        else{
          centro = VENTANA_ANCHO/2/f;

          angulo_estrella=atan2(ESTRELLA_POSICION_Y-nave_get_posy(navei),ESTRELLA_POSICION_X-nave_get_posx(navei));


          lista_iterar(disparos,disparo_mover,NULL);

          lista_iter_t *iter_disparos=lista_iter_crear(disparos);
          while(!lista_iter_al_final(iter_disparos)){
            disparo_t *disparo=lista_iter_ver_actual(iter_disparos);
            size_t n_disparo=figura_cant_polilineas(figura_vector[disparo_en_vector]);
            polilinea_t **disparo_polilinea=copiar_polilineas(figura_vector[disparo_en_vector],disparo_get_posx(disparo)-centro+ VENTANA_ANCHO / 2 / f,disparo_get_posy(disparo),disparo_get_angulo(disparo));

            for(size_t i=0; i<n_disparo;i++){
              graficar_polilinea(renderer,disparo_polilinea[i],f);
            }

            destruir_vector_polilineas(disparo_polilinea,n_disparo);
            lista_iter_avanzar(iter_disparos);
          }
          lista_iter_destruir(iter_disparos);



          size_t n_base=figura_cant_polilineas(figura_vector[base_en_vector]);
          polilinea_t **base=copiar_polilineas(figura_vector[base_en_vector],BASE_POSICION_X,BASE_POSICION_Y,0);

          size_t n_estrella=figura_cant_polilineas(figura_vector[estrella_en_vector]);
          polilinea_t **estrella=copiar_polilineas(figura_vector[estrella_en_vector],ESTRELLA_POSICION_X,ESTRELLA_POSICION_Y,0);

          for(size_t i=0;i<n_estrella;i++){
            if(distancia_punto_a_polilinea(estrella[i],nave_get_posx(navei),nave_get_posy(navei))<=3){
              nave_matar(navei,BASE_POSICION_X,BASE_POSICION_Y);
            }
          }

          for(size_t i=0;i<n_planetas;i++){

            size_t planeta_en_vector = figura_buscar(figura_vector,n_figura,planetas_niveles[i].nombre);

            size_t n_planeta=figura_cant_polilineas(figura_vector[planeta_en_vector]);
            polilinea_t **planeta=copiar_polilineas(figura_vector[planeta_en_vector],planetas_niveles[i].posx,planetas_niveles[i].posy,0);

            if(norma(planetas_niveles[i].posx-nave_get_posx(navei),planetas_niveles[i].posy-nave_get_posy(navei))<=25){
              size_t posicion_nivel = nivel_buscar(niveles, n_niveles, planetas_niveles[i].nivel);
              nivel_activar(niveles[posicion_nivel]);
              f = nivel_return_escala_inicial(niveles[posicion_nivel]);
              nave_trasladar(navei,400/f,500/f,true);
              centro=nave_get_posx(navei);
              size_t n;
              torreta_t **t = torretas_activar(planetas_niveles[i].nivel,&n);
              for(size_t j=0; j<n; j++){
                lista_insertar_ultimo(torretas_lista,t[j]);
              }
              free(t);
              fuel_t **f = fuel_activar(planetas_niveles[i].nivel,&n);
              for(size_t j=0; j<n; j++){
                lista_insertar_ultimo(fuel_lista,f[j]);
              }
              free(f);
              reactor_t **reactores_vector = reactor_activar(planetas_niveles[i].nivel,&n);
              for(size_t j=0; j<n; j++){
                lista_insertar_ultimo(reactor_lista,reactores_vector[j]);
              }
              free(reactores_vector);
              lista_destruir(disparos,free);
              disparos=lista_crear();
              lista_destruir(torreta_disparos,free);
              torreta_disparos=lista_crear();
            }

            for(size_t i=0; i<n_planeta;i++){
              trasladar(planeta[i],-centro + VENTANA_ANCHO / 2 / f,0);
              graficar_polilinea(renderer,planeta[i],f);
            }

            destruir_vector_polilineas(planeta, n_planeta);
          }



          if(nave_get_posx(navei)<0 || nave_get_posx(navei)>VENTANA_ANCHO){
            nave_rebotar_x(navei);
          }
          if(nave_get_posy(navei)<0 || nave_get_posy(navei)>VENTANA_ALTO){
            nave_rebotar_y(navei);
          }


          //ZONA GRAFICAR

          for(size_t i=0; i<n_base;i++){
            trasladar(base[i],-centro + VENTANA_ANCHO / 2 / f, 0);
            graficar_polilinea(renderer,base[i],f);
          }

          for(size_t i=0; i<n_estrella;i++){
            trasladar(estrella[i],-centro + VENTANA_ANCHO / 2 / f, 0);
            graficar_polilinea(renderer,estrella[i],f);
          }


          destruir_vector_polilineas(base, n_base);
          destruir_vector_polilineas(estrella, n_estrella);

        }

        for(size_t i=0; i<n_nave;i++){
          trasladar(nave[i],-centro + VENTANA_ANCHO/ 2 / f,0);
          graficar_polilinea(renderer, nave[i], f);
        }

        destruir_vector_polilineas(nave,n_nave);

        if(encabezado_get_score(e)>=next_ship){
          next_ship+=10000;
          nave_add_vida(navei);
        }

        if(nave_get_vidas(navei)>0){
        for(size_t i=0; i<nave_get_vidas(navei);i++){
            polilinea_t **nave_vida=copiar_polilineas(figura_vector[nave_en_vector],(100+(40*i))/2.5,960/2.5,NAVE_ANGULO_INICIAL);
            size_t n_nave_vida=figura_cant_polilineas(figura_vector[nave_en_vector]);
            for(size_t j=0; j<n_nave_vida;j++){
              graficar_polilinea(renderer, nave_vida[j], 1.5);
            }
            destruir_vector_polilineas(nave_vida,n_nave_vida);
          }
        }
        encabezado_set_fuel(e,nave_get_fuel(navei));
        encabezado_graficar(e,renderer);

        //ZONA DESTRUIR
        disparo_t *primer_disparo=lista_ver_primero(disparos);
        if(primer_disparo!=NULL && disparo_expiro(primer_disparo,NULL)){
          lista_borrar_primero(disparos);
          free(primer_disparo);
        }

        disparo_t *primer_disparo_torreta=lista_ver_primero(torreta_disparos);
        if(primer_disparo_torreta!=NULL && disparo_expiro(primer_disparo_torreta,NULL)){
          lista_borrar_primero(torreta_disparos);
          free(primer_disparo_torreta);
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

    nave_destruir(navei);
    encabezado_destruir(e);

    lista_destruir(disparos,free);
    lista_destruir(torreta_disparos,free);
    lista_destruir(torretas_lista,free);
    lista_destruir(fuel_lista, free);
    lista_destruir(reactor_lista,free);

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
