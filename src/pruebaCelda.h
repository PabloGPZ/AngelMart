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
 * 	Se llama al módulo iniciar() en una celda y se comprueba que su valor sea VALOR_PREDEFINIDO = -1,
 * 		que esté vacia (obtenerEstaVacia() -> true) y que esté mostrando el reverso
 * 		(obtenerMostrandoAnverso() -> false)
 */
void pruebaIniciarCelda();

/*
 * Verifica que funcionen correctamente los metodos ponerValor(), obtenerValor(), vaciarCelda() y obtenerEstaVacia()
 *
 *  ponerValor(celda,7) -> debe modificar el valor de la celda a 7. Se comprueba con obtenerValor()
 *  	obtenerValor(celda) = 7
 *  vaciarCelda(celda) -> debe designar la celda vacia. Se comprueba con obtenerEstaVacia()
 *  	obtenerEstaVacia(celda) = true
 */
void pruebaPonerValor();

/*
 * Verifica que funcione correctamente el módulo sonIguales()
 *
 * 	valor c1	valor c2	->		sonIguales()
 * 		5			5		->			true
 * 		7			5		->			false
 */
void pruebaSonIguales();

/*
 * Módulo que llama a todas las pruebas del TAD Celda
 */
void pruebasTADCelda();

#endif /* PRUEBACELDA_H_ */
