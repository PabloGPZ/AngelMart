/**

 INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
 Curso 2016/2017

 Nombre: entorno.cpp
 Descripción: Implementación del TAD Entorno para el proyecto 1010!
 Encargado del manejo de la interfaz del juego.
 Autor:	Profesores de las asignaturas
 Fecha:	25/11/2012
 Fecha última modificación: 10/11/2016 Allegro5

 **/

#include "entorno.h"
#include <stdlib.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

// -------------------------------------------------------------
// Definición de constantes privadas
// -------------------------------------------------------------
// Definición de colores que usa el entorno

const int COLOR_AZUL      = 1;
const int COLOR_VERDE     = 2;
const int COLOR_BLANCO    = 3;
const int COLOR_ROJO      = 4;
const int COLOR_NEGRO     = 5;
const int COLOR_NARANJA   = 6;
const int COLOR_GRIS      = 7;

const int   COLOR_LINEAS = COLOR_BLANCO;
const float GROSOR_LINEAS = 2.0;

const int ANCHO_VENTANA = 700;
const int ALTO_VENTANA  = 600;

// Definicón de constantes para posicionar los números en el tablero
const int DISTANCIA_COLS  = 40;  // Distancia entre columnas
const int DISTANCIA_FILAS = 40;  // Distancia entre filas
const int ORIGEN_X        = 20;  // Origen de las x
const int ORIGEN_Y        = 70;  // Origen de las y

// definicion de las constantes para posicionar los marcadores
const int FILA_MARCADOR = 64;
const int COL_MARCADOR  = 31;

// constante para el tiempo

const float FPS = 60.0;

ALLEGRO_TIMER *timer = NULL, *contador = 0;

ALLEGRO_DISPLAY     *display;
ALLEGRO_FONT        *font1, *font2;
ALLEGRO_EVENT_QUEUE *colaEventos = NULL;
ALLEGRO_EVENT_QUEUE *colaContador = NULL;


// -------------------------------------------------------------
// Declaración de módulos PRIVADOS
// -------------------------------------------------------------


// define el color en función de los valores makecol - allegro library
ALLEGRO_COLOR makecolor2 (int color);

// Dibuja en la pantalla el borde de un tablero con el ancho indicado
void entornoPintarRejilla(int tamanio);


// -------------------------------------------------------------
// Definición de módulos PRIVADOS
// -------------------------------------------------------------


ALLEGRO_COLOR makecolor2(int color) {

	ALLEGRO_COLOR alColor;

	switch(color){
	case COLOR_AZUL:
		alColor = al_map_rgb( 50,  50, 255);
		break;
	case COLOR_VERDE:
		alColor = al_map_rgb(  20, 110, 20);
		break;
	case COLOR_BLANCO:
		alColor = al_map_rgb(255, 255, 255);
		break;
	case COLOR_ROJO:
		alColor = al_map_rgb(255,  0,    0);
		break;
	case COLOR_NEGRO:
		alColor = al_map_rgb(  0,  0,    0);
		break;
	case COLOR_NARANJA:
		alColor = al_map_rgb(216, 075, 032);
		break;
	case COLOR_GRIS:
		alColor = al_map_rgb(200, 200, 200);
		break;
	default:
		alColor = al_map_rgb(255, 255, 255);
		break; //color blanco
	}
	return alColor;
}

void entornoPintarRejilla(int tamano){
	int i;
	int columnas    = tamano;
	int filas       = tamano;
	int nVecesMarco = 5; // número de veces que se repite el marco

	for(i = 1; i < nVecesMarco; i++){
		al_draw_filled_rectangle( ORIGEN_X + i, ORIGEN_Y + i,
				ORIGEN_X + columnas * DISTANCIA_COLS + i,
				ORIGEN_Y + filas * DISTANCIA_FILAS + i,
				makecolor2(COLOR_GRIS));
	}

	// horizontales
	for(i = 0; i <= (columnas); i++){
		al_draw_line( ORIGEN_X + 0 * DISTANCIA_COLS,
				ORIGEN_Y + i * DISTANCIA_FILAS,
				ORIGEN_X + columnas * DISTANCIA_COLS,
				ORIGEN_Y + i * DISTANCIA_FILAS, makecolor2(COLOR_LINEAS),GROSOR_LINEAS);
	}

	//verticales
	for(i = 0; i <= (filas); i++){
		al_draw_line( ORIGEN_X + i * DISTANCIA_COLS,
				ORIGEN_Y + 0 * DISTANCIA_FILAS, ORIGEN_X + i * DISTANCIA_COLS,
				ORIGEN_Y + filas * DISTANCIA_FILAS, makecolor2(COLOR_LINEAS), GROSOR_LINEAS);
	}
	al_draw_text(font1, makecolor2(COLOR_VERDE),  150,9,   ALLEGRO_ALIGN_CENTER,"puntuación               tiempo " );
	al_draw_text(font1, makecolor2(COLOR_VERDE),  550,30,  ALLEGRO_ALIGN_CENTER,"*** Angel Mart ***"              );
	al_draw_text(font1, makecolor2(COLOR_VERDE),  550,50,  ALLEGRO_ALIGN_CENTER, "  PROYECTO DE PROGRAMACIÓN"   );
	al_draw_text(font1, makecolor2(COLOR_VERDE),  440,80,  ALLEGRO_ALIGN_LEFT, "TECLAS: "                     );
	al_draw_text(font1, makecolor2(COLOR_VERDE),  440,100, ALLEGRO_ALIGN_LEFT, "   Arriba : Flecha arriba"    );
	al_draw_text(font1, makecolor2(COLOR_VERDE),  440,120, ALLEGRO_ALIGN_LEFT, "   Abajo  : Flecha abajo"     );
	al_draw_text(font1, makecolor2(COLOR_VERDE),  440,140, ALLEGRO_ALIGN_LEFT, "   Drcha  : Flecha derecha"   );
	al_draw_text(font1, makecolor2(COLOR_VERDE),  440,160, ALLEGRO_ALIGN_LEFT, "   Izqda   : Flecha izquierda");
	al_draw_text(font1, makecolor2(COLOR_VERDE),  440,190, ALLEGRO_ALIGN_LEFT, "   Enter   : Seleccionar"     );
	al_draw_text(font1, makecolor2(COLOR_VERDE),  440,210, ALLEGRO_ALIGN_LEFT, "   Salir    : Escape"         );
	al_draw_text(font1, makecolor2(COLOR_NARANJA),440,250, ALLEGRO_ALIGN_LEFT, "TECLAS para ampliaciones: "   );
	al_draw_text(font1, makecolor2(COLOR_NARANJA),440,270, ALLEGRO_ALIGN_LEFT, "   X : Pista 1               ");
	al_draw_text(font1, makecolor2(COLOR_NARANJA),440,290, ALLEGRO_ALIGN_LEFT, "   Y : Pista 2               ");
	al_draw_text(font1, makecolor2(COLOR_NARANJA),440,310, ALLEGRO_ALIGN_LEFT, "   Z : Pista 3               ");
}


void invertirFC(int &fila, int &columna){
	int aux = columna;
	columna = fila;
	fila = aux;
}


// -------------------------------------------------------------
// Definición de la interfaz PÚBLICA
// -------------------------------------------------------------


bool entornoIniciar(int tam){
	bool iniciado = true;
	if(al_init()) {
		display = al_create_display(ANCHO_VENTANA, ALTO_VENTANA);
		if(display){
			if(al_install_keyboard()){
				if(al_init_primitives_addon()){
					al_init_font_addon();
					if(al_init_ttf_addon()){
						font1 = al_load_ttf_font("DroidSerif-Regular.ttf", 17,0);
						font2 = al_load_ttf_font("DejaVuSansCondensed-Bold.ttf",30, 0);
						if(font1 && font2){
							al_clear_to_color(makecolor2(COLOR_BLANCO));
							al_set_window_title(display, "Angel Mart");

							colaEventos = al_create_event_queue();
							colaContador = al_create_event_queue();

							timer = al_create_timer(1.0); // FPS);
							contador = al_create_timer(1.0);
							al_register_event_source(colaEventos,
									al_get_keyboard_event_source());

							al_register_event_source(colaEventos,al_get_timer_event_source(timer));
							al_register_event_source(colaContador,al_get_timer_event_source(contador));

							al_start_timer(timer);
							al_start_timer(contador);

							entornoPintarRejilla(tam);
							al_flip_display();
						}else
							iniciado = false;
					}else
						iniciado = false;
				}else
					iniciado = false;
			}else
				iniciado = false;
		}else
			iniciado = false;
	}else
		iniciado = false;
	return iniciado;
}


void entornoTerminar(){
	al_destroy_display          (display);
	al_destroy_event_queue      (colaEventos);
	al_shutdown_primitives_addon();
	al_shutdown_font_addon      ();
	al_shutdown_ttf_addon       ();

	al_destroy_timer            (timer);
	al_destroy_timer            (contador);
}


bool entornoCargarConfiguracion(int &tamano, int &tiempo, int &ptosARestar){

	bool leido;
	ifstream entrada;
	string cadena;
	entrada.open("AngelMart.cnf");
	if(entrada.is_open()){
		getline(entrada, cadena);
		tamano = atoi(cadena.c_str());
		getline(entrada, cadena);
		tiempo = atoi(cadena.c_str());
		getline(entrada, cadena);
		ptosARestar = atoi(cadena.c_str());

		leido = true;
		entrada.close();
	}else{
		cout
				<< "Fichero de configuración no encontrado (<proyecto>/AngelMart.cnf)."
				<< endl;
		cout << "Formato:" << endl;
		cout << "\t[Tamaño del tablero 4..10]" << endl;
		cout << "\t[tiempo]" << endl;
		cout << "\t[nivel]" << endl;

		leido = false;
	}
	return leido;
}


// signo de interrogación
void entornoFichaReves(int fila, int columna){

	invertirFC(fila, columna);
	al_draw_filled_rectangle( ORIGEN_X + fila * DISTANCIA_COLS + 3,
				ORIGEN_Y + columna * DISTANCIA_FILAS + 3,
				ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS - 2,
				ORIGEN_Y + columna * DISTANCIA_FILAS + DISTANCIA_FILAS - 2,makecolor2(COLOR_VERDE));

	al_draw_text(font2, makecolor2(COLOR_BLANCO), ORIGEN_X + fila * DISTANCIA_COLS + (DISTANCIA_COLS/3),ORIGEN_Y + columna * DISTANCIA_FILAS + 6, ALLEGRO_ALIGN_LEFT, "?");
	al_flip_display();
}


void entornoFichaAnverso(int fila, int columna, int numero){
	invertirFC(fila, columna);
	al_draw_filled_rectangle( ORIGEN_X + fila * DISTANCIA_COLS + 3,
			ORIGEN_Y + columna * DISTANCIA_FILAS + 3,
			ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS - 2,
			ORIGEN_Y + columna * DISTANCIA_FILAS + DISTANCIA_FILAS - 2,al_map_rgb(55*numero,100*numero,15*numero));
			//al_map_rgb(182*numero,149*numero,192*numero));
			//al_map_rgb(55*numero,100*numero,15*numero));

	al_draw_text(font2, makecolor2(COLOR_BLANCO), ORIGEN_X + fila * DISTANCIA_COLS + (DISTANCIA_COLS/3),ORIGEN_Y + columna * DISTANCIA_FILAS + 3, ALLEGRO_ALIGN_LEFT, toString(numero).c_str());
	al_flip_display();
}


void entornoFichaCanto(int fila, int columna){
	invertirFC(fila, columna);
	al_draw_filled_rectangle( ORIGEN_X + fila * DISTANCIA_COLS + 3,
				ORIGEN_Y + columna * DISTANCIA_FILAS + 3,
				ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS - 2,
				ORIGEN_Y + columna * DISTANCIA_FILAS + DISTANCIA_FILAS - 2,makecolor2(COLOR_GRIS));

	al_draw_filled_rectangle(ORIGEN_X + fila * DISTANCIA_COLS + 18,
				ORIGEN_Y + columna * DISTANCIA_FILAS + 4,
				ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS - 13,
				ORIGEN_Y + columna * DISTANCIA_FILAS + DISTANCIA_FILAS - 4, makecolor2(COLOR_VERDE));
	al_flip_display();
}


void entornoFichaBono(int fila, int columna, int numero) {
	invertirFC(fila, columna);
	al_draw_filled_rectangle(ORIGEN_X + fila * DISTANCIA_COLS + 3,
			ORIGEN_Y + columna * DISTANCIA_FILAS + 3,
			ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS - 2,
			ORIGEN_Y + columna * DISTANCIA_FILAS + DISTANCIA_FILAS - 2,
			makecolor2(COLOR_ROJO));

	al_draw_filled_rectangle(ORIGEN_X + fila * DISTANCIA_COLS + 6,
			ORIGEN_Y + columna * DISTANCIA_FILAS + 6,
			ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS - 5,
			ORIGEN_Y + columna * DISTANCIA_FILAS + DISTANCIA_FILAS - 5,
			makecolor2(COLOR_BLANCO));

	al_draw_text(font2, makecolor2(COLOR_ROJO),
			ORIGEN_X + fila * DISTANCIA_COLS + (DISTANCIA_COLS / 3),
			ORIGEN_Y + columna * DISTANCIA_FILAS + 3, ALLEGRO_ALIGN_LEFT,
			toString(numero).c_str());
	al_flip_display();
}


void entornoFichaBomba(int fila, int columna, int numero) {
	invertirFC(fila, columna);
	al_draw_filled_rectangle(ORIGEN_X + fila * DISTANCIA_COLS + 3,
			ORIGEN_Y + columna * DISTANCIA_FILAS + 3,
			ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS - 2,
			ORIGEN_Y + columna * DISTANCIA_FILAS + DISTANCIA_FILAS - 2,
			makecolor2(COLOR_NEGRO));

	al_draw_filled_rectangle(ORIGEN_X + fila * DISTANCIA_COLS + 6,
				ORIGEN_Y + columna * DISTANCIA_FILAS + 6,
				ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS - 5,
				ORIGEN_Y + columna * DISTANCIA_FILAS + DISTANCIA_FILAS - 5,
				makecolor2(COLOR_NEGRO));

	al_draw_text(font2, makecolor2(COLOR_ROJO),
			ORIGEN_X + fila * DISTANCIA_COLS + (DISTANCIA_COLS / 3),
			ORIGEN_Y + columna * DISTANCIA_FILAS + 3, ALLEGRO_ALIGN_LEFT,
			toString(numero).c_str());
	al_flip_display();

}


void entornoBorrarCelda(int fila, int columna) {
	invertirFC(fila, columna);
	al_draw_filled_rectangle( ORIGEN_X + fila * DISTANCIA_COLS + 3,
				ORIGEN_Y + columna * DISTANCIA_FILAS + 3,
				ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS - 2,
				ORIGEN_Y + columna * DISTANCIA_FILAS + DISTANCIA_FILAS - 2,
				makecolor2(COLOR_GRIS));
	al_flip_display();
}


void entornoActivarCelda(int fila, int columna) {
	int color = COLOR_NARANJA;
	invertirFC(fila, columna);

// vertical izquierda
	al_draw_line( ORIGEN_X + fila * DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS,
			ORIGEN_X + fila * DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS,
			makecolor2(color),GROSOR_LINEAS);
// horizontal arriba
	al_draw_line( ORIGEN_X + fila * DISTANCIA_FILAS ,
			ORIGEN_Y + columna * DISTANCIA_COLS ,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS ,
			ORIGEN_Y + columna * DISTANCIA_COLS ,
			makecolor2(color),GROSOR_LINEAS);

// vertical derecha
	al_draw_line( ORIGEN_X + fila * DISTANCIA_FILAS +DISTANCIA_FILAS ,
			ORIGEN_Y + columna * DISTANCIA_COLS ,
			ORIGEN_X + fila * DISTANCIA_FILAS +DISTANCIA_FILAS ,
			ORIGEN_Y + columna * DISTANCIA_COLS +DISTANCIA_COLS,
			makecolor2(color), GROSOR_LINEAS);
// horizontal abajo
	al_draw_line( ORIGEN_X + fila * DISTANCIA_FILAS ,
			ORIGEN_Y + columna * DISTANCIA_COLS +DISTANCIA_COLS,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS ,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS ,
			makecolor2(color), GROSOR_LINEAS);

	al_flip_display();
}


void entornoDesactivarCelda(int fila, int columna) {

	invertirFC(fila, columna);

	// vertical izquierda
	al_draw_line(ORIGEN_X + fila * DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS,
			ORIGEN_X + fila * DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS,
			makecolor2(COLOR_LINEAS), GROSOR_LINEAS);
	// horizontal arriba
	al_draw_line(ORIGEN_X + fila * DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS, makecolor2(COLOR_LINEAS),
			GROSOR_LINEAS);

	// vertical derecha
	al_draw_line(ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS,
			makecolor2(COLOR_LINEAS), GROSOR_LINEAS);
	// horizontal abajo
	al_draw_line(ORIGEN_X + fila * DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS,
			ORIGEN_X + fila * DISTANCIA_FILAS + DISTANCIA_FILAS,
			ORIGEN_Y + columna * DISTANCIA_COLS + DISTANCIA_COLS,
			makecolor2(COLOR_LINEAS), GROSOR_LINEAS);

	al_flip_display();
}


void entornoMostrarMensaje(TipoZona zona, string msg) {
	int fila;
	int col = 50;
	switch(zona){
	case Zona1:
		fila = 480;
		break;
	case Zona2:
		fila = 505;
		break;
	case Zona3:
		fila = 530;
		break;
	default:
		return;
	}
	al_draw_filled_rectangle(col-2 , fila,  col + 600,fila+25,  makecolor2(COLOR_BLANCO));
	al_draw_text(font1, makecolor2(COLOR_AZUL),col,fila, ALLEGRO_ALIGN_LEFT, msg.c_str());
	al_flip_display();
}


void entornoMostrarMensajeFin(string msg) {
	int i, j;
		for(i = 0, j = 0; i < 40 && j < 40; i += 4, j += 4) {
			al_draw_filled_rectangle(i + 220 , j + 240, 600 - i, 380 -j,  makecolor2(COLOR_VERDE));
			al_draw_filled_rectangle(i + 222 , j + 242, 598 - i, 378 -j,  makecolor2(COLOR_BLANCO));
			al_rest(0.10); // pausa
			al_flip_display();
		}
	al_draw_text(font1, makecolor2(COLOR_VERDE),380,300, ALLEGRO_ALIGN_CENTRE, msg.c_str());
	al_flip_display();
}


void entornoPonerPuntuacion(int valor) {
	al_draw_filled_rectangle(FILA_MARCADOR , COL_MARCADOR, FILA_MARCADOR+ 100, COL_MARCADOR+30, makecolor2(COLOR_BLANCO));
	al_draw_text(font1, makecolor2(COLOR_VERDE),FILA_MARCADOR + 22, COL_MARCADOR   , ALLEGRO_ALIGN_LEFT, toString(valor).c_str());
	al_flip_display();
}


TipoTecla entornoLeerTecla() {

	TipoTecla tecla = TNada;
	ALLEGRO_EVENT evento;

	al_wait_for_event(colaEventos, &evento);
	if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
		tecla = TSalir;
	}else{
		if(evento.type == ALLEGRO_EVENT_KEY_UP){
			switch(evento.keyboard.keycode){
			case ALLEGRO_KEY_UP:
				tecla = TArriba;
				break;
			case ALLEGRO_KEY_DOWN:
				tecla = TAbajo;
				break;
			case ALLEGRO_KEY_LEFT:
				tecla = TIzquierda;
				break;
			case ALLEGRO_KEY_RIGHT:
				tecla = TDerecha;
				break;
			case ALLEGRO_KEY_ESCAPE:
				tecla = TSalir;
				break;
			case ALLEGRO_KEY_ENTER:
				tecla = TEnter;
				break;
			case ALLEGRO_KEY_X:
				tecla = TX;
				break;
			case ALLEGRO_KEY_Y:
				tecla = TY;
				break;
			case ALLEGRO_KEY_Z:
				tecla = TZ;
				break;
			default:
				tecla = TNada;
				break;
			}
		}
	}
	return tecla;
}


void entornoTiempo(int &seg, int contador) {

	int tam = 70;

	int color = COLOR_VERDE;
	if(!al_is_event_queue_empty(colaContador)){
		ALLEGRO_EVENT evento;
		al_wait_for_event(colaContador, &evento);

		if(evento.type == ALLEGRO_EVENT_TIMER){
			seg++;

			if(seg == contador){
				color = COLOR_ROJO;
			}
		}
	}
	al_draw_filled_rectangle(FILA_MARCADOR *3  , COL_MARCADOR, (FILA_MARCADOR * 3) + tam , COL_MARCADOR+ tam/2, makecolor2(COLOR_BLANCO));
	al_draw_textf(font1, makecolor2(color), FILA_MARCADOR + 160, COL_MARCADOR ,ALLEGRO_ALIGN_CENTRE, "%02d", seg);

	al_flip_display();
}


void entornoPausa(float pausa) {
	al_rest(pausa);
}


string toString(int numero) {
	stringstream flujo;
	string cadena;
	flujo << numero;
	flujo >> cadena;
	return cadena;
}
