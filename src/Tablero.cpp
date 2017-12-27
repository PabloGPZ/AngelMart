/*
 * Tablero.cpp
 * Autor: jgarciapft
 *
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
void insertarFicha(Tablero& t, int pos_x, int pos_y, int valor) {

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
		for(int i=0; i<obtenerTamanoTablero(t) && cabeFila; i++){ //comprueba solo la fila superior
			if(!celdaEstaVacia(t, i, 0))
				cabeFila = false;
		}
	}
	return cabeFila;
}

void insertarFila(Tablero& t) {
}

bool estaVacio(Tablero t) {
	bool estaVacio = true; //bandera
	for(int i=0; i<obtenerTamanoTablero(t) && estaVacio; i++){ //si no hay nada en la ultima fila significa que el tablero está vacio. Solo comprobamos la última fila
		if(!celdaEstaVacia(t, i, obtenerTamanoTablero(t)-1))
			estaVacio = false;
	}
	return estaVacio;
}

int obtenerTamanoTablero(Tablero t) {
	return t.tamanoTablero;
}

bool celdaEstaVacia(Tablero t, int pos_x, int pos_y) {
	return obtenerEstaVacia(t.v[pos_y][pos_x]);
}

int celdaObtenerValor(Tablero t, int pos_x, int pos_y) {
	return obtenerValor(t.v[pos_y][pos_x]);
}

bool celdaObtenerMostrandoAnverso(Tablero t, int pos_x, int pos_y) {
	return obtenerMostrandoAnverso(t.v[pos_y][pos_x]);
}
