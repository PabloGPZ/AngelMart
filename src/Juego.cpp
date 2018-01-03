/*
 * Juego.cpp
 * Autor: jgarciapft
 *
 */

#include "Juego.h"
#include "Tablero.h"
#include "entorno.h"
#include "pruebas.h"

int tamanoTablero;  //guardará el número de filas y columnas del tablero, rol: valor fijo
int tiempoJugada;   //guardará el tiempo de una jugada, rol: valor fijo
int seg;	  		//almacena los segundos del cronometro, rol: más reciente
int puntosPista; 	//guardara el número de puntos que se restan en algunas ampliaciones, rol: valor fijo
string mensaje;  	//almacena los diferentes mensajes que aparecen durante la ejecucion, rol: valor fijo
bool salir;			//controla la salida del bucle, rol: bandera
TipoTecla tecla;	//almacena las teclas pulsadas, rol: mas reciente
int pos_x, pos_y;		//almacena la posición de la celda seleccionada, rol: transformación

int main() { //cargarJuego()
	//Llamada a todas las pruebas
	pruebas();
}

void manejadorJuego() {
}

void terminarJuego() {
}
