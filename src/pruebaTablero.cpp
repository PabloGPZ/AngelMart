/*
 * pruebaTablero.cpp
 * Autor: Juan Pablo García Plaza Pérez (jgarciapft)
 *
 */

#include "pruebaTablero.h"

using namespace std;

void pruebaIniciarTablero() {
	bool correcto = true; 													//bandera
	Tablero t;

	//Inicialización del tablero de prueba
	iniciarTablero(t, 6);

	for(int i=0; i<obtenerTamanoTablero(t) && correcto; i++){
		for(int j=0; j<obtenerTamanoTablero(t) && correcto; j++){
			if(celdaObtenerEstaVacia(t, j, i) != true
					&& celdaObtenerValor(t, j, i) != VALOR_PREDEFINIDO
					&& celdaObtenerMostrandoAnverso(t, j, i) != false)
				correcto = false;
		}
	}
	if(!correcto)
		cout << "ERROR: La porción del tablero designada por el tamaño no está inicializada" << endl;

	if(celdaObtenerEstaVacia(t, 0, obtenerTamanoTablero(t)) != false
			&& celdaObtenerValor(t, 0, obtenerTamanoTablero(t)+1) == VALOR_PREDEFINIDO)
		cout << "ERROR: Se inician más filas inferiores de las que indica el tamaño" << endl;

	if(celdaObtenerEstaVacia(t, obtenerTamanoTablero(t), 0) != false
			&& celdaObtenerValor(t, obtenerTamanoTablero(t)+1, 0) == VALOR_PREDEFINIDO)
		cout << "ERROR: Se inician más columnas de las que indica el tamaño" << endl;
}

void pruebaInsertarFicha() {
	Tablero t;
	
	//Inicialización del tablero de prueba
	iniciarTablero(t, 6);
	
	//1. Se inserta una ficha sin obstáculos para comprobar que se coloqué en el fondo
	insertarFicha(t, 0, 0, 0);

	if(celdaObtenerEstaVacia(t, 0, obtenerTamanoTablero(t)-1) != false)
		cout << "ERROR: La ficha no cae correctamente cuando no hay obstáculo" << endl;

	//2. Se coloca un obstáculo para comprobar que pare
	insertarFicha(t, 1, 0, 0); 											//Colocamos una ficha en la segunda columna
	insertarFicha(t, 1, 0, 1); 											//Dejamos caer una encima

	if(celdaObtenerEstaVacia(t, 1, obtenerTamanoTablero(t)-2) != false)
		cout << "ERROR: La segunda ficha no se para en el obstáculo" << endl;
}

void pruebaEliminarFicha() {
	Tablero t;
	
	//Inicialización del tablero de prueba
	iniciarTablero(t, 6);
	insertarFicha(t, 0, 0, 0);
	insertarFicha(t, 1, 0, 0);
	insertarFicha(t, 1, 0, 1); 
	
	//1. Se elimina una ficha que no tiene ninguna ficha encima
	eliminarFicha(t, 0, obtenerTamanoTablero(t)-1);

	if(celdaObtenerEstaVacia(t, 0, obtenerTamanoTablero(t)-1) != true)
		cout << "ERROR: La primera ficha no se ha eliminado correctamente" << endl;

	//2. Se elimina una ficha que tenga más fichas encima
	eliminarFicha(t, 1, obtenerTamanoTablero(t)-1);

	if(celdaObtenerEstaVacia(t, 1, obtenerTamanoTablero(t)-2) != true
			&& celdaObtenerValor(t, 1, obtenerTamanoTablero(t)-1) != 1) 	//1 es el valor de la ficha superior
		cout << "ERROR: No ha caido la ficha superior" << endl;
}

void pruebaFichaVoltear() {
	Tablero t;
	
	//Inicialización del tablero de prueba
	iniciarTablero(t, 6);
	insertarFicha(t, 0, 0, 1);
	
	//Comprobamos que exista la ficha y que muestre el reverso
	if(!celdaObtenerEstaVacia(t, 0, obtenerTamanoTablero(t)-1)){
		if(!celdaObtenerMostrandoAnverso(t, 1, obtenerTamanoTablero(t)-1)){
			if(fichaVoltear(t, 0, obtenerTamanoTablero(t)-1) != true){ 	//Pasa de REVERSO a ANVERSO
				cout << "ERROR: La ficha no ha cambiado de REVERSO a ANVERSO" << endl;
				if(fichaVoltear(t, 0, obtenerTamanoTablero(t)-1) != false)//Pasa de ANVERSO a REVERSO
					cout << "ERROR: La ficha no ha cambiado de ANVERSO a REVERSO" << endl;
			}
		}else{
			cout << "PELIGRO: NO SE PUEDEN REALIZAR LAS PRUEBAS DE fichaVoltear() #2" << endl;
		}
	}else{
		cout << "PELIGRO: NO SE PUEDEN REALIZAR LAS PRUEBAS DE fichaVoltear() #1" << endl;
	}
}

void pruebaCabeFila() {
	Tablero t1, t2;
	
	//Inicialización de los tableros de prueba
	iniciarTablero(t1, 6);
	iniciarTablero(t2, 6);
	
	//1. El tablero no está lleno y se puede colocar una fila más
	if(cabeFila(t1) != true)
		cout << "ERROR: Se pueden insertar más filas en el tablero" << endl;

	//2. Hay alguna ficha en la fila superior y por tanto no se puede introducir ninguna fila más
	for(int i=0; i<obtenerTamanoTablero(t2); i++){ 							//Relleno el tablero completamente
		for(int j=0; j<obtenerTamanoTablero(t2); j++){
			celdaPonerValor(t2, j, i, 0);
		}
	}

	if(cabeFila(t2) != false)
		cout << "ERROR: No se pueden insertar más filas en el tablero" << endl;
}

void pruebaInsertarFila() {
	Tablero t;
	
	//Inicialización del tablero de prueba
	iniciarTablero(t, 6);	
	
	insertarFila(t, time(NULL)); 											//El tiempo como semilla

	for(int i=0; i<obtenerTamanoTablero(t); i++){
		if(celdaObtenerEstaVacia(t, i, obtenerTamanoTablero(t)-1) != false)
			cout << "ERROR: La ficha de la columna " << i << " no está bien posicionada" << endl;
	}
}

void pruebaTableroEstaVacio() {
	Tablero t1, t2;
	
	//Inicialización de los tableros de prueba
	iniciarTablero(t1, 6);
	insertarFila(t1, time(NULL));
	
	iniciarTablero(t2, 6);
	
	//1. El tablero está contiene alguna ficha	->	tableroEstaVacio() = FALSE
	if(tableroEstaVacio(t1) != false)
		cout << "ERROR: El tablero no está vacio" << endl;

	//2. El tablero está vacío					->	tableroEstaVacio() = TRUE
	if(tableroEstaVacio(t2) != true)
		cout << "ERROR: El tablero está vacio" << endl;
}

void pruebaCompararFichas(){
	Tablero t;
	
	//Inicialización del tablero de prueba
	iniciarTablero(t, 6);
	insertarFicha(t, 0, 0, 0);
	insertarFicha(t, 1, 0, 0);
	
	//1. Las dos fichas tienen el mismo valor (0,0)	->	compararFichas() = TRUE
	if(compararFichas(t, 0, obtenerTamanoTablero(t)-1, 1, obtenerTamanoTablero(t)-1) != true)
		cout << "ERROR: Las fichas tienen el mismo valor" << endl;

	//2. Las dos fichas tienen distinto valor (0,1)	->	compararFichas() = FALSE
	insertarFicha(t, 2, 0, 0); 											//Ficha 1 con valor 0
	insertarFicha(t, 3, 0, 1); 											//Ficha 2 con valor 1

	if(compararFichas(t, 2, obtenerTamanoTablero(t)-1, 3, obtenerTamanoTablero(t)-1) != false)
		cout << "ERROR: Las fichas no tienen el mismo valor" << endl;
}

void pruebaGenerarVectorUnico() {
	/*
	 * Se comprueba visualmente para evitar repetir el mismo algoritmo de busqueda de repeticiones dentro del vector
	 */
	vValores v;

	generarVectorUnico(v, 5, 5, time(NULL)); 								//El tiempo como semilla

	cout << "v -> ";
	for(int i=0; i<5; i++){
		cout << "[" << v[i] << "]";
	}
	cout << endl;
}

void pruebasTADTablero(){
	cout << "INICIO: pruebas del TAD Tablero" << endl;

	pruebaIniciarTablero();
	pruebaInsertarFicha();
	pruebaEliminarFicha();
	pruebaFichaVoltear();
	pruebaCabeFila();
	pruebaInsertarFila();
	pruebaTableroEstaVacio();
	pruebaCompararFichas();
	pruebaGenerarVectorUnico();

	cout << "FIN: pruebas del TAD Tablero" << endl << endl;
}
