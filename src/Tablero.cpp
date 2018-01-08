/*
 * Tablero.cpp
 * Autor: Juan Pablo García Plaza Pérez (jgarciapft)
 *
 */

#include "Tablero.h"
#include "Celda.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

void iniciarTablero(Tablero &t, int tamano) {
	t.tamanoTablero = tamano;

	for(int i=0; i<tamano; i++){ //Bucles for anidados para iniciar cada celda del tablero
		for(int j=0; j<tamano; j++){
			iniciarCelda(t.v[i][j]);
		}
	}
}

void insertarFicha(Tablero &t, int pos_x, int pos_y, int valor) {
	bool obs = false; //bandera

	ponerValor(t.v[pos_y][pos_x], valor);

	for(int i=0; i<obtenerTamanoTablero(t)-1 && !obs; i++){ //Deja caer la ficha
		if(celdaEstaVacia(t, pos_x, pos_y+i+1)){
			ponerValor(t.v[pos_y+i+1][pos_x],  celdaObtenerValor(t, pos_x, pos_y+i));
			vaciarCelda(t.v[pos_y+i][pos_x]);
		}else{
			obs = true;
		}
	}
}

void eliminarFicha(Tablero &t, int pos_x, int pos_y) {
	bool vacio = false; //bandera

	vaciarCelda(t.v[pos_y][pos_x]);
	for(int i=0; i<obtenerTamanoTablero(t)-1 && !vacio; i++){ //Deja caer las fichas superiores
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

	if(!celdaObtenerMostrandoAnverso(t, pos_x, pos_y)){ //Estado presente: ANVERSO
		ponerMostrandoAnverso(t.v[pos_y][pos_x], true);
		mostrandoAnverso = true; //Estado siguiente: REVERSO
	}else{ //Estado presente: REVERSO
		ponerMostrandoAnverso(t.v[pos_y][pos_x], false);
		mostrandoAnverso = false; //Estado siguiente: ANVERSO
	}
	return mostrandoAnverso;
}

bool cabeFila(Tablero t) {
	bool cabeFila = true; //bandera

	if(!tableroEstaVacio(t)){
		for(int i=0; i<obtenerTamanoTablero(t) && cabeFila; i++){ //Si hay alguna ficha en la fila superior no caben más filas. Comprueba solo la fila superior
			if(!celdaEstaVacia(t, i, 0))
				cabeFila = false;
		}
	}
	return cabeFila;
}

void insertarFila(Tablero &t) {
	vValores valores; //Vector de valores
	vValores posiciones; //Vector de posiciones de parejas

	generarVectorUnico(valores, obtenerTamanoTablero(t)/2, MAX_VALOR_FICHA+1); //Vector de valores únicos que representan una fila nueva. Solo se rellena hasta la mitad
	generarVectorUnico(posiciones, obtenerTamanoTablero(t)/2, obtenerTamanoTablero(t)/2); //Vector de posiciones que deben ocupar cada pareja de valores generados

	for(int i=obtenerTamanoTablero(t)/2; i<obtenerTamanoTablero(t); i++){ //Relleno la otra mitad del vector con las parejas de los valores presentes en base al vector de posiciones
		valores[i] = valores[posiciones[i-obtenerTamanoTablero(t)/2]];
	}

	for(int i=0; i<obtenerTamanoTablero(t); i++){ //Inserción de fichas
		insertarFicha(t, i, 0, valores[i]);
	}
}

bool tableroEstaVacio(Tablero t) {
	bool estaVacio = true; //bandera

	for(int i=0; i<obtenerTamanoTablero(t) && estaVacio; i++){ //Si no hay nada en la ultima fila significa que el tablero está vacio. Solo comprobamos la última fila
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

void generarVectorUnico(vValores &vector, int tamano, int rang){
	/*
	 *Algoritmo de generación de vectores de valores únicos para la generación de filas de valores emparejados
	 */
	srand(time(NULL)); //Semilla que se actualiza con el tiempo del sistema

	bool enc = false; //bandera
	int valor; //valor generado
	int j; //indice

	for(int i=0; i<tamano; i++){ //Popula vector[] hasta 'tamano'
		valor = rand()%rang;
		for(j=0; j<i && !enc; j++){ //Comprobamos que el valor no esté repetido
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
