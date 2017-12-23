/*
 * Tablero.cpp
 * Autor: jgarciapft
 *
 */

#include "Tablero.h"
#include "Celda.h"
#include "entorno.h"

int obtenerConfTamanoTablero() {
	int tamano, placehorlder_1, placeholder_2;
	if(!entornoCargarConfiguracion(tamano, placehorlder_1, placeholder_2))
		tamano = -1;
	return tamano;
}

void iniciarTablero(Tablero& t, int tamano) {
	t.tamanoTablero = tamano;
}

void insertarFicha(Tablero& t, int pos_x, int pos_y) {
	Celda c;
	iniciar(c);
	t.v[pos_y][pos_x] = c;
}

void eliminarFicha(Tablero& t, int pos_x, int pos_y) {
	vaciarCelda(t.v[pos_y][pos_x]);
}

void fichaVoltear(Tablero& t, int pos_x, int pos_y) {
}

bool cabeFila(Tablero t) {
}

void insertarFila(Tablero& t) {
}

bool estaVacio(Tablero t) {
}

int obtenerTamanoTablero(Tablero t) {
}

bool celdaEstaVacia(Tablero t, int pos_x, int pos_y) {
}

int celdaObtenerValor(Tablero t, int pos_x, int pos_y) {
}

bool celdaObtenerMostrandoAnverso(Tablero t, int pos_x, int pos_y) {
}
