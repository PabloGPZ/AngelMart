/*
 * pruebas.h
 * Autor: Juan Pablo García Plaz Pérez (jgarciapft)
 *
 * Definición: Archivo de cabeceras para incluir un módulo que realice todas las pruebas
 */

#ifndef PRUEBAS_H_
#define PRUEBAS_H_

#include "entorno.h"
#include "pruebaCelda.h"
#include "pruebaTablero.h"

/*
 * Módulo responsable de las pruebas del entorno gráfico
 */
void pruebasEntorno();

/*
 * Módulo responsable de llamar a todas las pruebas de todos los TAD que requieren
 * de pruebas
 */
void pruebas();

#endif /* PRUEBAS_H_ */
