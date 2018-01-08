/*
 * pruebaCelda.cpp
 * Autor: Juan Pablo García Plaza Pérez (jgarciapft)
 *
 */

#include <iostream>
#include "pruebaCelda.h"
#include "Celda.h"

using namespace std;

Celda celda, c1, c2;

void pruebaIniciarCelda(){
	iniciarCelda(celda);
	if(obtenerValor(celda) != VALOR_PREDEFINIDO ||
			obtenerEstaVacia(celda) != true ||
			obtenerMostrandoAnverso(celda) != false)
		cout << "ERROR: La celda no está correctamente inicializada" << endl;
}

void pruebaValorCelda(){
	ponerValor(celda, 7);
	if(obtenerValor(celda) != 7)
		cout << "ERROR: La celda no tiene el valor deseado" << endl;
	vaciarCelda(celda);
	if(obtenerEstaVacia(celda) != true)
		cout << "ERROR: La celda no está vacía despues de haberla vaciado" << endl;
}

void pruebaSonIguales(){
	//Inicialización y asignación de valores a las celdas de prueba "c1" y "c2"
	iniciarCelda(c1);
	iniciarCelda(c2);
	ponerValor(c1, 5);
	ponerValor(c2, 5);

	if(sonIguales(c1, c2) != true)
		cout << "ERROR: el método sonIguales() funciona correctamente" << endl;

	ponerValor(c1, 7);

	if(sonIguales(c1, c2) != false)
		cout << "ERROR: el método sonIguales() funciona correctamente" << endl;
}

void pruebasTADCelda(){
	cout << "INICIO: pruebas del TAD Celda" << endl;

	pruebaIniciarCelda();
	pruebaValorCelda();
	pruebaSonIguales();

	cout << "FIN: pruebas del TAD Celda" << endl << endl;
}
