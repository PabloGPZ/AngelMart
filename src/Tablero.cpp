/*
 * Tablero.cpp
 * Autor: jgarciapft
 *
 */

#include "Tablero.h"
#include "entorno.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

void iniciarTablero(Tablero& t, int tamano) {
	t.tamanoTablero = tamano;
	for(int i=0; i<tamano; i++){ //bucles para iniciar cada celda del tablero
		for(int j=0; j<tamano; j++){
			iniciar(t.v[j][i]);
		}
	}
}

//v1.0
void insertarFicha(Tablero& t, int pos_x, int pos_y, int valor) {
	bool obs = false; //bandera

	ponerValor(t.v[pos_y][pos_x], valor);
	for(int i=0; i<obtenerTamanoTablero(t)-1 && !obs; i++){ //deja caer la ficha
		if(celdaEstaVacia(t, pos_y+1, pos_x)){
			t.v[pos_y+1][pos_x] = t.v[pos_y][pos_x];
			vaciarCelda(t.v[pos_y][pos_x]);
		}else{
			obs = true;
		}
	}
}

//v1.0
void eliminarFicha(Tablero& t, int pos_x, int pos_y) {
	bool vacio = false; //bandera
	int movidas = 0; //contador

	vaciarCelda(t.v[pos_y][pos_x]);
	for(int i=0; i<obtenerTamanoTablero(t)-1 && !vacio; i++){ //deja caer las fichas superiores
		if(!celdaEstaVacia(t, pos_y-1-movidas, pos_x)){
			t.v[pos_y][pos_x] = t.v[pos_y-1-movidas][pos_x];
			vaciarCelda(t.v[pos_y-1-movidas][pos_x]);
			movidas++;
		}
		else{
			vacio = true;
		}
	}
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

//TODO terminar insertarFila()
void insertarFila(Tablero& t) {
	//Algoritmo de generación de parejas
	srand(time(NULL)); //semilla que se actualiza con el tiempo del sistema
	bool enc = false; //bandera
	int valor; //valor generado
	int j; //indice
	int coincidencias[obtenerTamanoTablero(t)/2]; //vector de valores generados anteriormente para evitar valores repetidos
	int valores[obtenerTamanoTablero(t)]; //hay que generar tamanoTablero/2 parejas de valores

	for(int i=0; i<obtenerTamanoTablero(t)/2; i++){ //Inicializa coincidencias[] con valores negativos para garantizar que no puedan coincidir con los generados
		coincidencias[i] = -1;
	}

	for(int i=0; i<obtenerTamanoTablero(t)/2; i++){ //popula la mitad de valores[] para obtener posteriormente los pares de valores
		valor = rand()%10;
		for(j=0; j<i && !enc; j++){
			if(coincidencias[j] == valor)
				enc = true;
		}
		if(!enc){
			coincidencias[j];
			valores[i] = valor;
		}else{
			i--; //Si el valor esta repetido no cuenta la iteración
		}
		enc = false;
	}

	//TODO Mover el algoritmo a un método
	for(int i=0; i<obtenerTamanoTablero(t); i++){
		insertarFicha(t, i, 0, NULL);
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
