/*
 * pruebaCelda.h
 * Autor: Juan Pablo García Plaz Pérez (jgarciapft)
 *
 * Descripción: Clase que maneja las pruebas sobre el TAD Celda
 *
 */

#ifndef PRUEBACELDA_H_
#define PRUEBACELDA_H_

/*
 * Verifica que las celdas se inicializan correctamente
 *
 * 	Se llama al método iniciar() en una celda y se comprueba que su valor sera VALOR_PREDEFINIDO = -1,
 * 		que esté vacia (obtenerEstaVacia() = true) y que esté mostrando el reverso
 * 		(obtenerMostrandoAnverso() = false)
 */
void pruebaIniciarCelda();

/*
 * Verifica que funcionen correctamente los metodos ponerValor(), obtenerValor(), vaciarCelda() y obtenerEstaVacia()
 *
 *  ponerValor(celda,7) -> debe modificar el valor de la celda a 7. Se comprueba en con obtenerValor()
 *  obtenerValor(celda) = 7
 *  vaciarCelda(celda) -> debe modificar 'celda' para que celda.estaVacia = true
 *  obtenerEstaVacia(celda) = true
 */
void pruebaValorCelda();

/*
 * Verifica que funcione correctamente el método sonIguales()
 *
 * 	valor c1		valor c2		->		sonIguales()
 * 		5				5			->			true
 * 		7				5			->			false
 */
void pruebaSonIguales();

/*
 * Módulo que llama a todas las pruebas
 */
void pruebasTADCelda();

#endif /* PRUEBACELDA_H_ */
