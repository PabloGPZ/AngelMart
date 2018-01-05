/*
 * Tablero.h
 * Autor: jgarciapft
 *
 * Descripción: TAD que maneja el tablero de juego en memoria
 *
 */

#ifndef TABLERO_H_
#define TABLERO_H_

#include "Celda.h"

const int MAX_TAMANO = 10;
const int MAX_VALOR_FICHA = 9;

typedef Celda vCeldas[MAX_TAMANO][MAX_TAMANO];
typedef int vValores[MAX_TAMANO];

struct Tablero{
	vCeldas v;
	int tamanoTablero;
};

/*
 * PRE: 4 <= 'tamano' <= 10 y es un valor par
 * POST: Modifica el Tablero 't' para iniciarlo con el tamño indicado por 'tamano'
 * COMPLEJIDAD: 0(n²)
 */
void iniciarTablero(Tablero &t, int tamano);


/*
 * PRE: 'pos_x' y 'pos_y' dentro de los límites del Tablero 't' y la celda objetivo está vacia
 * POST: Modifica el Tablero 't' para insertar una ficha en la posición ('pos_x', 'pos_y')
 * COMPLEJIDAD: O(n)
 */
void insertarFicha(Tablero &t, int pos_x, int pos_y, int valor);


/*
 * PRE: 'pos_x' y 'pos_y' dentro de los límites del Tablero 't' y la celda objetivo contiene una ficha
 * POST: Modifica el Tablero 't' para eliminar la ficha en la posición ('pos_x', 'pos_y')
 * COMPLEJIDAD: O(n)
 */
void eliminarFicha(Tablero &t, int pos_x, int pos_y);


/*
 * PRE: 'pos_x' y 'pos_y' dentro de los límites del Tablero 't' y la celda objetivo contiene una ficha
 * POST: Modifica el Tablero 't' para voltear (mostrar el anverso si muestra el reverso y viceversa) una ficha
 * COMPLEJIDAD: O(1)
 */
bool fichaVoltear(Tablero &t, int pos_x, int pos_y);


/*
 * PRE:
 * POST: Devuelve si cabe una nueva Fila en el Tablero 't'
 * COMPLEJIDAD: O(n)
 */
bool cabeFila(Tablero t);


/*
 * PRE: cabe una nueva fila en el Tablero 't'
 * POST: Modifica el Tablero 't' para insertar una nueva fila de fichas
 * 			en la parte superior y que bajen hasta ocupar los huecos libres del tablero
 * COMPLEJIDAD: O(n)
 */
void insertarFila(Tablero &t);


/*
 * PRE:
 * POST: Devuelve si el Tablero 't' está vacio
 * COMPLEJIDAD: 0(n)
 */
bool estaVacio(Tablero t);


/*
 * PRE:
 * POST: Devuelve el tamaño real indicado por el fichero de configuracion del Tablero 't'
 * COMPLEJIDAD: 0(1)
 */
int obtenerTamanoTablero(Tablero t);


/*
 * PRE: 'pos_x' y 'pos_y' dentro de los límites del Tablero 't'
 * POST: Devuelve si la celda de la posicion ('pos_x','pos_y') contiene o no una ficha
 * COMPLEJIDAD: 0(1)
 */
bool celdaEstaVacia(Tablero t, int pos_x, int pos_y);


/*
 * PRE: 'pos_x' y 'pos_y' dentro de los límites del Tablero 't' y existe una ficha en la posicion ('pos_x','pos_y')
 * POST: Devuelve el valor de la celda de la posicion ('pos_x','pos_y') contiene o no una ficha
 * COMPLEJIDAD: 0(1)
 */
int celdaObtenerValor(Tablero t, int pos_x, int pos_y);


/*
 * PRE: 'pos_x' y 'pos_y' dentro de los límites del Tablero 't' y existe una ficha en en la posicion ('pos_x','pos_y')
 * POST: Devuelve si la celda de la posicion ('pos_x','pos_y') esta mostrando el anverso
 * 			(el número es visible) o no
 * COMPLEJIDAD: 0(1)
 */
bool celdaObtenerMostrandoAnverso(Tablero t, int pos_x, int pos_y);

/*
 * PRE: 4 <= 'tamano' <= 'rang' <= 10
 * POST: Modifica un vector 'vector' del tipo vValores de valores aleatorios únicos del tamaño 'tamano'
 * 			y de valores dentro del rango de 0 hasta 'rang'. Si 'tamano' > 'rang' se repetirán valores
 * COMPLEJIDAD: 0(n)
 */
void generarVectorUnico(vValores &vector, int tamano, int rang);

#endif /* TABLERO_H_ */
