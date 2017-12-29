/*
 * pruebaTablero.cpp
 * Autor: jgarciapft
 *
 * Descripción: Clase que maneja las pruebas sobre el TAD Tablero
 *
 */

#include "pruebaTablero.h"
#include "Tablero.h"
#include <iostream>

using namespace std;

Tablero t1, t2, t3;

void pruebaIniciarTablero() {
	bool correcto = true; //bandera
	iniciarTablero(t1, 6);
	for(int i=0; i<obtenerTamanoTablero(t1) && correcto; i++){
		for(int j=0; j<obtenerTamanoTablero(t1) && correcto; j++){
			if(celdaEstaVacia(t1, j, i) != true)
				correcto = false;
		}
	}
	if(!correcto)
		cout << "ERROR: La porción del tablero designada por el tamaño no está inicializada" << endl;
	if(celdaEstaVacia(t1, 0, obtenerTamanoTablero(t1)+1) != false)
		cout << "ERROR: Se inician más filas inferiores de las que indica el tamaño" << endl;
	if(celdaEstaVacia(t1, obtenerTamanoTablero(t1)+1, 0) != false)
		cout << "ERROR: Se inician más columnas de las que indica el tamaño" << endl;
}

void pruebaInsertarFicha() {
	//1. Se inserta una ficha sin obstáculos para comprobar que se coloqué en el fondo
	insertarFicha(t1, 0, 0, 0);
	if(celdaEstaVacia(t1, 0, obtenerTamanoTablero(t1)-1) != false)
		cout << "ERROR: La ficha no cae correctamente cuando no hay obstáculo" << endl;

	//2. Se coloca un obstáculo para comprobar que pare
	insertarFicha(t1, 0, 1, 0); //colocamos una ficha en la segunda columna
	insertarFicha(t1, 0, 1, 1); //dejamos caer una encima
	if(celdaEstaVacia(t1, 1, obtenerTamanoTablero(t1)-2) != false)
		cout << "ERROR: La segunda ficha no se para en el obstáculo" << endl;
}

void pruebaEliminarFicha() {
	//1. Se elimina una ficha que no tiene ninguna ficha encima
	eliminarFicha(t1, 0, obtenerTamanoTablero(t1)-1);
	if(celdaEstaVacia(t1, 0, obtenerTamanoTablero(t1)-1) != true)
		cout << "ERROR: La primera ficha no se ha eliminado correctamente" << endl;

	//2. Se elimina una ficha que tenga más fichas encima

	eliminarFicha(t1, 1, obtenerTamanoTablero(t1)-1);
	if(celdaEstaVacia(t1, 1, obtenerTamanoTablero(t1)-2) != true
			&& celdaObtenerValor(t1, 1, obtenerTamanoTablero(t1)-1) != 1) //1 es el valor de la ficha superior
		cout << "ERROR: No ha caido la ficha superior" << endl;
}

void pruebaFichaVoltear() {
	//Comprobamos que exista la ficha y que muestre el reverso
	if(!celdaEstaVacia(t1, 1, obtenerTamanoTablero(t1)-1)){
		if(!celdaObtenerMostrandoAnverso(t1, 1, obtenerTamanoTablero(t1)-1)){
			fichaVoltear(t1, 1, obtenerTamanoTablero(t1)-1); //pasa de REVERSO a ANVERSO
			if(celdaObtenerMostrandoAnverso(t1, 1, obtenerTamanoTablero(t1)-1) != true){
				cout << "ERROR: La ficha no ha cambiado de REVERSO a ANVERSO" << endl;
				fichaVoltear(t1, 1, obtenerTamanoTablero(t1)-1); //pasa de ANVERSO a REVERSO
				if(celdaObtenerMostrandoAnverso(t1, 1, obtenerTamanoTablero(t1)-1) != false)
					cout << "ERROR: La ficha no ha cambiado de ANVERSO a REVERSO" << endl;
			}else{
				cout << "PELIGRO: NO SE PUEDEN REALIZAR LAS PRUEBAS DE fichaVoltear()" << endl;
			}
		}else{
			cout << "PELIGRO: NO SE PUEDEN REALIZAR LAS PRUEBAS DE fichaVoltear()" << endl;
		}
	}else{
		cout << "PELIGRO: NO SE PUEDEN REALIZAR LAS PRUEBAS DE fichaVoltear()" << endl;
	}
}

void pruebaCabeFila() {
	//1. El tablero no está lleno y se puede colocar una fila más
	if(cabeFila(t1) != true)
		cout << "ERROR: Se pueden insertar más filas en el tablero" << endl;

	//2. Hay alguna ficha en la fila superior y por tanto no se puede introducir ninguna fila más
	iniciarTablero(t2, 4); //Inicio un segundoo tablero
	for(int i=0; i<obtenerTamanoTablero(t2); i++){ //Relleno el tablero completamente
		for(int j=0; j<obtenerTamanoTablero(t2); j++){
			ponerValor(t2.v[i][j], 0);
		}
	}
	if(cabeFila(t2) != false)
		cout << "ERROR: No se pueden insertar más filas en el tablero" << endl;
}

void pruebaInsertarFila() {
	insertarFila(t1);
	for(int i=0; i<obtenerTamanoTablero(t1); i++){
		if(i == 1){ //En la segunda columna hay ya una ficha sobre la que debe caer la nueva
			if(celdaEstaVacia(t1, i, obtenerTamanoTablero(t1)-2) != false)
				cout << "ERROR: La ficha de la columna " << i << " no está bien posicionada" << endl;
		}else{
			if(celdaEstaVacia(t1, i, obtenerTamanoTablero(t1)-1) != false)
				cout << "ERROR: La ficha de la columna " << i << " no está bien posicionada" << endl;
		}
	}
}

void pruebaEstaVacio() {
	//1. El tablero está contiene alguna ficha	->	estaVacio() = FALSE
	if(estaVacio(t1) != false)
		cout << "ERROR: El tablero no está vacio" << endl;

	//2. El tablero está vacío					->	estaVacio() = TRUE
	iniciarTablero(t3, 4);
	if(estaVacio(t3) != true)
		cout << "ERROR: El tablero está vacio" << endl;
}

void pruebaGenerarVectorUnico() {
	//La comprobación es visual para evitar repetir el mismo algoritmo de busqueda de repeticiones dentro del vector
	vValores v1, v2, v3;
	generarVectorUnico(v1, 5, 6);

	//1. Primer vector único
	cout << "v1 -> ";
	for(int i=0; i<6; i++){
		cout << "[" << v1[i] << "]";
	}
	cout << endl;

	//2. Segundo vector único
	generarVectorUnico(v2, 5, 6);
	cout << "v2 -> ";
	for(int i=0; i<6; i++){
		cout << "[" << v2[i] << "]";
	}
	cout << endl;

	//3. Tercer vector único
	generarVectorUnico(v3, 5, 6);
	cout << "v3 -> ";
	for(int i=0; i<6; i++){
		cout << "[" << v3[i] << "]";
	}
	cout << endl;
}

void mostrarTablero(Tablero t){
	for(int i=0; i<obtenerTamanoTablero(t); i++){
		for(int j=0; j<obtenerTamanoTablero(t); j++){
			cout << "[" << celdaObtenerValor(t, j, i) << "/" << celdaEstaVacia(t, j, i) << "]";
		}
		cout << endl;
	}
}

void pruebasTADTablero(){
	cout << "INICIO: pruebas del TAD Tablero" << endl;

	pruebaIniciarTablero();
	mostrarTablero(t1);
	pruebaInsertarFicha();
	pruebaEliminarFicha();
	pruebaFichaVoltear();
	pruebaCabeFila();
	pruebaInsertarFila();
	pruebaEstaVacio();
	pruebaGenerarVectorUnico();

	cout << "FIN: pruebas del TAD Tablero" << endl << endl;
}
