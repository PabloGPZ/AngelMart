/*
 * Tablero.cpp
 * Autor: jgarciapft
 *
 *TODO Replantearse los módulos definidos
 */

#include "Tablero.h"
#include "entorno.h"

void iniciarTablero(Tablero& t, int tamano) {
	t.tamanoTablero = tamano;
	for(int i=0; i<tamano; i++){ //bucles para iniciar cada celda del tablero
		for(int j=0; j<tamano; j++){
			iniciar(t.v[j][i]);
		}
	}
}

//TODO Corregir insertarFicha()
void insertarFicha(Tablero& t, int pos_x, int pos_y) {
	Celda c;
	iniciar(c);
	t.v[pos_y][pos_x] = c;
}

//TODO Corregir eliminarFicha()
void eliminarFicha(Tablero& t, int pos_x, int pos_y) {
	vaciarCelda(t.v[pos_y][pos_x]);
}

void fichaVoltear(Tablero& t, int pos_x, int pos_y) {
	if(!obtenerMostrandoAnverso(t.v[pos_y][pos_x]))
		ponerMostrandoAnverso(t.v[pos_y][pos_x], true);
	else
		ponerMostrandoAnverso(t.v[pos_y][pos_x], false);
}

bool cabeFila(Tablero t) {
	bool cabeFila = true; //bandera
	if(!estaVacio(t)){
		for(int i=0; i<MAX_TAMANO && cabeFila; i++){ //comprueba solo la fila superior
			if(!celdaEstaVacia(t, 0, i))
				cabeFila = false;
		}
	}
	return cabeFila;
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
