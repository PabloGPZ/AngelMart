/*
 * pruebaTablero.h
 * Autor: Juan Pablo García Plaz Pérez (jgarciapft)
 *
 * Descripción: Clase que maneja las pruebas sobre el TAD Tablero
 *
 */

#ifndef PRUEBATABLERO_H_
#define PRUEBATABLERO_H_

/*
 * Verifica que se inicie la porción correcta del tablero
 *
 * #. Se inicia el tablero con un tamaño cualquiera, por ejemplo 6
 */
void pruebaIniciarTablero();


/*
 * Verifica que al insertarse una ficha caiga hasta la siguiente ficha en su columna
 * 		o el fondo del tablero
 *
 * 1. Se inserta una ficha sin obstáculos para comprobar que se coloqué en el fondo
 * 2. Se coloca un obstáculo para comprobar que pare
 */
void pruebaInsertarFicha();


/*
 * Verifica que al eliminarse una ficha las que haya encima caigan
 *
 * 1. Se elimina una ficha que no tiene ninguna ficha encima
 * 2. Se elimina una ficha que tenga más fichas encima
 */
void pruebaEliminarFicha();


/*
 * Verifica que cambia el estado de la ficha de la posición [pos_y][pos_x]
 *
 * fichaVoltear()	->	fichaVoltear()
 * 		Reverso		->		TRUE
 * 		Anverso		->		FALSE
 */
void pruebaFichaVoltear();


/*
 * Verifica que se determine correctamente cuando cabe o no una fila más en el tablero
 *
 * 1. El tablero no está lleno y se puede colocar una fila más
 * 2. Hay alguna ficha en la fila superior y por tanto no se puede introducir ninguna fila más
 */
void pruebaCabeFila();


/*
 * Verifica que se inserte una fila de fichas en la parte superior del tablero y sus
 * 		fichas caigan por columnas hasta la ficha siguiente o el fondo
 *
 * #. Se inserta una fila en la parte superior y se comprueba que caigan las fichas
 */
void pruebaInsertarFila();


/*
 * Verifica que se determine correctamente que el tablero esté vacío o no
 *
 * 1. El tablero está contiene alguna ficha	->	estaVacio() = FALSE
 * 2. El tablero está vacío					->	estaVacio() = TRUE
 */
void pruebaTableroEstaVacio();


/*
 * Verifica que se determine correctamente cuando dos fichas son iguales y cuando no
 *
 * 1. Las dos fichas tienen el mismo valor (0,0)	->	compararFichas() = TRUE
 * 2. Las dos fichas tienen distinto valor (0,1)	->	compararFichas() = FALSE
 */
void pruebaCompararFichas();


/*
 * Verifica que el algoritmo de generación de números aleatorios únicos dentro de un rango
 * 		funcione correctamente.
 *
 * tamano	rang	->	vector
 * 	 5		  5		->	[5 VALORES ALEATORIOS NO REPETIDOS]
 */
void pruebaGenerarVectorUnico();


/*
 * Módulo para llamar a todas las pruebas del TAD Tablero
 */
void pruebasTADTablero();

#endif /* PRUEBATABLERO_H_ */
