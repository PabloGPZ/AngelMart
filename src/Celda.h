/*
 * Celda.h
 * Autor: Juan Pablo García Plaz Pérez (jgarciapft)
 *
 * Descripción: TAD que maneja las celdas del tablero
 *
 */

#ifndef CELDA_H_
#define CELDA_H_

const int VALOR_PREDEFINIDO = -1;

struct Celda{
	int valor;
	bool estaVacia;
	bool mostrandoAnverso;
};

/*
 * PRE:
 * POST: Inicia la celda al valor por defecto, la designa vacia y mostrando el reverso
 * COMPLEJIDAD: O(1)
 */
void iniciarCelda(Celda &c);


/*
 * PRE:
 * POST: Designa una celda vacia
 * COMPLEJIDAD: O(1)
 */
void vaciarCelda(Celda &c);


/*
 * PRE: 0 <= valor <= 9
 * POST: Pone el valor de la celda c a 'valor'
 * COMPLEJIDAD: O(1)
 */
void ponerValor(Celda &c, int valor);


/*
 * PRE:
 * POST: Cambia el estado de la celda c (si muestra el anverso o no)a 'estado'
 * COMPLEJIDAD: O(1)
 */
void ponerMostrandoAnverso(Celda &c, bool estado);


/*
 * PRE:
 * POST: Devuelve el valor de la celda c
 * COMPLEJIDAD: O(1)
 */
int obtenerValor(Celda c);


/*
 * PRE:
 * POST: Devuelve si la celda c esta vacia o no
 * COMPLEJIDAD: O(1)
 */
bool obtenerEstaVacia(Celda c);


/*
 * PRE:
 * POST: Devuelve el estado de la celda c (si esta mostrando el anverso o no)
 * COMPLEJIDAD: O(1)
 */
bool obtenerMostrandoAnverso(Celda c);


/*
 * PRE: 'c1' y 'c2' son objetos tipo Celda correctamente inicializados
 * POST: Devuelve si las celdas 'c1' y 'c2' son de igual valor o no
 * COMPLEJIDAD: O(1)
 */
bool sonIguales(Celda c1, Celda c2);

#endif /* CELDA_H_ */
