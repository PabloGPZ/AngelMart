/*
 * Celda.cpp
 * Autor: jgarciapft
 *
 */

#include "Celda.h"

void iniciarCelda(Celda &c){
	c.valor = VALOR_PREDEFINIDO;
	c.estaVacia = true;
	c.mostrandoAnverso = false;
}


void vaciarCelda(Celda &c){
	c.estaVacia = true;
}


void ponerValor(Celda &c, int valor){
	c.valor = valor;
	c.estaVacia = false;
	c.mostrandoAnverso = false;
}


void ponerMostrandoAnverso(Celda &c, bool estado){
	c.mostrandoAnverso = estado;
}


int obtenerValor(Celda c){
	return c.valor;
}


bool obtenerEstaVacia(Celda c){
	return c.estaVacia;
}


bool obtenerMostrandoAnverso(Celda c){
	return c.mostrandoAnverso;
}


bool sonIguales(Celda c1, Celda c2){
	return c1.valor == c2.valor;
}
