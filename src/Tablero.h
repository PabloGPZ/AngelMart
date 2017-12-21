/*
 * Celda.h
 * Autor: jgarciapft
 *
 * Descripción: TAD que maneja las el tablero de juego en memoria
 *
 */

#ifndef TABLERO_H_
#define TABLERO_H_

const int MAX_TAMANO = 10;

typedef Celda vCeldas[MAX_TAMANO];

struct Tablero{
	vCeldas v;
	int tamanoTablero;
};


int obtenerConfTamanoTablero();


void iniciarTablero(Tablero &t, int tamano);


void insertarCelda(Tablero &t, int pos_x, int pos_y);


void eliminarCelda(Tablero &t, int pos_x, int pos_y);


bool cabeNuevaFila(Tablero t);


void insertarNuevaFila(Tablero &t);


bool estaVacio(Tablero t);


int obtenerTamanoTablero(Tablero t);


bool celdaEstaVacia(Tablero t, int pos_x, int pos_y);


int celdaObtenerValor(Tablero t, int pos_x, int pos_y);


bool celdaObtenerMostrandoAnverso(Tablero t, int pos_x, int pos_y);


void celdaVoltear(Tablero &t, int pos_x, int pos_y);

#endif /* TABLERO_H_ */
