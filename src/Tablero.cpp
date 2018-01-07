/*
 * Tablero.cpp
 * Autor: jgarciapft
 *
 */

#include "Tablero.h"
#include "Celda.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

void iniciarTablero(Tablero &t, int tamano) {
	t.tamanoTablero = tamano;
	for(int i=0; i<tamano; i++){ //bucles para iniciar cada celda del tablero
		for(int j=0; j<tamano; j++){
			iniciarCelda(t.v[i][j]);
		}
	}
}

//v1.1
void insertarFicha(Tablero &t, int pos_x, int pos_y, int valor) {
	bool obs = false; //bandera

	ponerValor(t.v[pos_y][pos_x], valor);
	for(int i=0; i<obtenerTamanoTablero(t)-1 && !obs; i++){ //deja caer la ficha
		if(celdaEstaVacia(t, pos_x, pos_y+i+1)){
			ponerValor(t.v[pos_y+i+1][pos_x],  celdaObtenerValor(t, pos_x, pos_y+i));
			vaciarCelda(t.v[pos_y+i][pos_x]);
		}else{
			obs = true;
		}
	}
}

//v1.2
void eliminarFicha(Tablero &t, int pos_x, int pos_y) {
	bool vacio = false; //bandera

	vaciarCelda(t.v[pos_y][pos_x]);
	for(int i=0; i<obtenerTamanoTablero(t)-1 && !vacio; i++){ //deja caer las fichas superiores
		if(!celdaEstaVacia(t, pos_x, pos_y-i-1)){
			ponerValor(t.v[pos_y-i][pos_x],  celdaObtenerValor(t, pos_x, pos_y-i-1));
			vaciarCelda(t.v[pos_y-i-1][pos_x]);
		}
		else{
			vacio = true;
		}
	}
}

bool fichaVoltear(Tablero &t, int pos_x, int pos_y) {
	bool mostrandoAnverso;
	if(!celdaObtenerMostrandoAnverso(t, pos_x, pos_y)){
		ponerMostrandoAnverso(t.v[pos_y][pos_x], true);
		mostrandoAnverso = true;
	}else{
		ponerMostrandoAnverso(t.v[pos_y][pos_x], false);
		mostrandoAnverso = false;
	}
	return mostrandoAnverso;
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

//v1.0
void insertarFila(Tablero &t) {
	vValores valores; //vector de valores
	vValores posiciones; //vector de posiciones de parejas

	generarVectorUnico(valores, obtenerTamanoTablero(t)/2, MAX_VALOR_FICHA+1); //vector de valores únicos que representan una fila nueva. Solo se rellena hasta la mitad
	generarVectorUnico(posiciones, obtenerTamanoTablero(t)/2, obtenerTamanoTablero(t)/2); //vector de posiciones que deben ocupar cada pareja de valores generados

	for(int i=obtenerTamanoTablero(t)/2; i<obtenerTamanoTablero(t); i++){ //relleno la otra mitad del vector con las parejas de los valores presentes en base al vector de posiciones
		valores[i] = valores[posiciones[i-obtenerTamanoTablero(t)/2]];
	}

	for(int i=0; i<obtenerTamanoTablero(t); i++){ //inserción de fichas
		insertarFicha(t, i, 0, valores[i]);
	}
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

//v1.1
void generarVectorUnico(vValores &vector, int tamano, int rang){
	/*
	 *Algoritmo de generación de vectores de valores únicos para la generación de filas de valores emparejados
	 */
	srand(time(NULL)); //semilla que se actualiza con el tiempo del sistema
	bool enc = false; //bandera
	int valor; //valor generado
	int j; //indice

	for(int i=0; i<tamano; i++){ //popula vector[] hasta 'tamano'
		valor = rand()%rang;
		for(j=0; j<i && !enc; j++){ //comprobamos que el valor no esté repetido
			if(vector[j] == valor)
				enc = true;
		}
		if(!enc)
			vector[i] = valor;
		else
			i--; //Si el valor esta repetido no cuenta la iteración
		enc = false;
	}
}
