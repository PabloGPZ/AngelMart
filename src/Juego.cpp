/*
 * Juego.cpp
 * Autor: Juan Pablo García Plaza Pérez (jgarciapft)
 *
 */

#include "Juego.h"

using namespace std;

void cargarJuego(Juego &j){
	int tamanoTablero;  											//Guardará el número de filas y columnas del tablero, rol: valor fijo
	int tiempoJugada;   											//Guardará el tiempo de una jugada, rol: valor fijo
	int puntosPista; 												//Guardara el número de puntos que se restan en algunas ampliaciones, rol: valor fijo

	//Carga la configuración e inicia el tablero
	if(entornoCargarConfiguracion(tamanoTablero, tiempoJugada, puntosPista)){
		//Comprobaciones de los parámetros de configuración
		if(tamanoTablero % 2 == 0 && tamanoTablero >= 4 && tamanoTablero <= 10){
			if(tiempoJugada > 0){
				if(puntosPista > 0){
					if(entornoIniciar(tamanoTablero)){
						/*
						 * INICIALIZACIÓN DEL TABLERO DE JUEGO Y PUNTUACIÓN
						 */
						iniciarTablero(j.t, tamanoTablero);
						j.puntuacion = PTOS_INICALES;
						entornoPonerPuntuacion(PTOS_INICALES);
						j.tiempoJugada = tiempoJugada;
						j.puntosPista = puntosPista;

						manejadorJuego(j);							//Inicia la partida
					}
				}else{
					cout << "ERROR: El coste de puntos por pista debe ser un entero positivo. En su lugar (" << puntosPista << ")" << endl;
				}
			}else{
				cout << "ERROR: El tiempo por jugada debe ser un entero positivo. En su lugar (" << tiempoJugada << ")" << endl;
			}
		}else{
			cout << "ERROR: El tamaño del tablero debe ser un entero positivo par entre 4 y 10. En su lugar (" << tamanoTablero << ")" << endl;
		}
	}
}

void manejadorJuego(Juego &j){
	int seg = 0;	  												//Almacena los segundos del cronometro, rol: más reciente
	bool salir = false;												//Controla la salida del bucle, rol: bandera
	TipoTecla tecla;												//Almacena las teclas pulsadas, rol: mas reciente
	int pos_x, pos_y;												//Almacena la posición de la celda seleccionada, rol: transformación
	int sel_x1, sel_y1, sel_x2, sel_y2; 							//Almacenan las posiciones de las dos fichas seleccionadas, rol: transformación
	int seleccionadas = 0;											//Almacena el numero de fichas seleccionadas, rol: contador
	bool estado;                                           			//Bandera de la pista 1, rol: bandera

	/*
	 * INICIALIZACIÓN DEL ENTORNO
	 */
	pos_x = 0;
	pos_y = obtenerTamanoTablero(obtenerTablero(j))-1;
	entornoActivarCelda(pos_y, pos_x);

	//Inserción de filas iniciales
	for(int i=0; i<FILAS_INICIALES; i++){
		insertarFila(obtenerTablero(j), time(NULL)+i);				//El tiempo + i como semilla para que se generen 2 filas distintas en un mismo segundo
	}
	actualizarEntorno(j);

	/*
	 * Bucle que mantiene el procesamiento de la lógica del juego
	 */
	while(!salir){
		/*
		 * Manejador de tiempo
		 */
		entornoTiempo(seg, obtenerTiempoJugada(j));					//Se actualizan y muestran los segundos del cronómetro
		if(seg == obtenerTiempoJugada(j)){							//Al llegar a 'tiempoJugada' segundos, el cronómetro se vuelve a iniciar
			seg = 0;
			if(cabeFila(obtenerTablero(j))) 						//Comprueba si cabe una fila adicional en el tablero
				juegoInsertarFila(j);
			else
				salir = true;
		}

		/*
		 * Manejador de entrada de usuario
		 */
		tecla = entornoLeerTecla();
		switch(tecla) {
			case TEnter:
				switch(seleccionadas){
				case 0:
					if(!celdaObtenerEstaVacia(obtenerTablero(j), pos_x, pos_y)){ //Se comprueba que la celda no esté vacia
						juegoFichaVoltear(j, pos_x, pos_y);

						sel_x1 = pos_x;
						sel_y1 = pos_y;

						seleccionadas++;
					}
					break;
				case 1:
					if(!celdaObtenerEstaVacia(obtenerTablero(j), pos_x, pos_y)){//Se comprueba que la celda no esté vacia
						if(sel_x1 != pos_x || sel_y1 != pos_y){		//Se comprueba que no se seleccione dos veces la misma ficha
							juegoFichaVoltear(j, pos_x, pos_y);

							sel_x2 = pos_x;
							sel_y2 = pos_y;

							seleccionadas++;
						}
					}
					break;
				default:
					break;
				}
				break;
			case TDerecha:
				entornoDesactivarCelda(pos_y, pos_x);
				if (pos_x < obtenerTamanoTablero(obtenerTablero(j))-1)
					pos_x++;
				else
					pos_x = 0;
				entornoActivarCelda(pos_y, pos_x);
				break;
			case TIzquierda:
				entornoDesactivarCelda(pos_y, pos_x);
				if (pos_x > 0)
					pos_x--;
				else
					pos_x = obtenerTamanoTablero(obtenerTablero(j))-1;
				entornoActivarCelda(pos_y, pos_x);
				break;
			case TArriba:
				entornoDesactivarCelda(pos_y, pos_x);
				if (pos_y > 0)
					pos_y--;
				else
					pos_y = obtenerTamanoTablero(obtenerTablero(j))-1;
				entornoActivarCelda(pos_y, pos_x);
				break;
			case TAbajo:
				entornoDesactivarCelda(pos_y, pos_x);
				if (pos_y < obtenerTamanoTablero(obtenerTablero(j))-1)
					pos_y++;
				else
					pos_y = 0;
				entornoActivarCelda(pos_y, pos_x);
				break;
			case TX: 												//Pista 1
				estado = true; 										//Inicialización de la bandera

				if(obtenerPuntuacion(j)-obtenerPuntosPista(j) >= 0){//Bucle para voltear la ficha de REVERSO a ANVERSO y a REVERSO
					obtenerPuntuacion(j) = obtenerPuntuacion(j)-obtenerPuntosPista(j); //Se actualiza la puntuación
					entornoPonerPuntuacion(obtenerPuntuacion(j));

					for(int c=0; c<2; c++){
						for(int i=0; i<obtenerTamanoTablero(obtenerTablero(j)); i++){ //Bucles for anidados para iterar cada celda del tablero
							for(int z=0; z<obtenerTamanoTablero(obtenerTablero(j)); z++){
																	//Si hay alguna ficha seleccionada se mantiene su anverso
								if(!celdaObtenerEstaVacia(obtenerTablero(j), z, i) && ( i != sel_y1 || z != sel_x1)) //Con que una coordenada sea distinta no será la misma posición
									celdaPonerMostrandoAnverso(obtenerTablero(j), z, i, estado);
							}
						}
						actualizarEntorno(j);
						entornoPausa(TIEMPO_PISTA_1); 				//Tiempo de retraso entre ambos volteos
						estado = false; 							//Actualización de la bandera para pasar de ANVERSO a REVERSO
					}

					actualizarEntorno(j);
				}
				break;
			case TY: 												//Pista 2
				if(obtenerPuntuacion(j)-obtenerPuntosPista(j)/2 >= 0){ //Bucle para voltear la ficha de REVERSO a ANVERSO y a REVERSO
					obtenerPuntuacion(j) = obtenerPuntuacion(j)-obtenerPuntosPista(j)/2; //Se actualiza la puntuación
					entornoPonerPuntuacion(obtenerPuntuacion(j));

					for(int i=0; i<obtenerTamanoTablero(obtenerTablero(j)); i++){ //Bucles for anidados para iterar cada celda del tablero
						for(int z=0; z<obtenerTamanoTablero(obtenerTablero(j)); z++){
							if(!celdaObtenerEstaVacia(obtenerTablero(j), z, i) && ( i != sel_y1 || z != sel_x1)){ //Con que una coordenada sea distinta no será la misma posición){
								juegoFichaVoltear(j, z, i);
								entornoPausa(TIEMPO_PISTA_2);
								juegoFichaVoltear(j, z, i);
							}
						}
					}
				}
				break;
			case TZ:
				break;
			case TSalir:
				salir = true;
				break;
			case TNada:
				break;
		}

		/*
		 * Manejador de comparación de fichas
		 */
		if(seleccionadas == 2){
			entornoPausa(TIEMPO_RETRASO_SELECCION); 				//Pausa para que el jugador vea la comparación

			if(compararFichas(obtenerTablero(j), sel_x1, sel_y1, sel_x2, sel_y2)){ 	//Son iguales
				if(sel_y1 < sel_y2){ 								//Si se elimina primero la ficha inferior la superior cae y se desplaza, por lo que su posicion varia
					juegoEliminarFicha(j, sel_x1, sel_y1);
					juegoEliminarFicha(j, sel_x2, sel_y2);
				}else{
					juegoEliminarFicha(j, sel_x2, sel_y2);
					juegoEliminarFicha(j, sel_x1, sel_y1);
				}

				obtenerPuntuacion(j) = obtenerPuntuacion(j) + PTOS_PAREJA; //Se suman los puntos
				entornoPonerPuntuacion(obtenerPuntuacion(j));

				/*
				 * Manejador de final por vaciar tablero
				 */
				if(tableroEstaVacio(obtenerTablero(j)))
					salir = true;
			}else{													//Son distintas
				juegoFichaVoltear(j, sel_x1, sel_y1);				//Se vuelven a voltear las fichas
				juegoFichaVoltear(j, sel_x2, sel_y2);
			}
			
			seleccionadas = 0;										//Se reinicia el contador
		}
	}

	/*
	 * Manejador de final de juego
	 */
	if(salir)
		terminarJuego(j); 											//Finaliza la partida
}

void terminarJuego(Juego &j) {
	string mensaje;  												//Almacena los diferentes mensajes que aparecen durante la ejecucion, rol: valor fijo

	if(tableroEstaVacio(obtenerTablero(j)))
		obtenerPuntuacion(j) = obtenerPuntuacion(j) + PTOS_FINAL_TABLERO_VACIO;	//Si la partida termina por vaciar el tablero se dan ptos extra

	mensaje = "             Puntuación final : " + toString(obtenerPuntuacion(j)) + " ptos";
	entornoMostrarMensajeFin(mensaje);

	entornoPausa(TIEMPO_PAUSA_FINAL);
	entornoTerminar();
}

void actualizarEntorno(Juego &j){
	for(int i=0; i<obtenerTamanoTablero(obtenerTablero(j)); i++){
		for(int z=0; z<obtenerTamanoTablero(obtenerTablero(j)); z++){
			if(!celdaObtenerEstaVacia(obtenerTablero(j), z, i)){ 	//Actualiza el estado de la ficha en función de su miembro 'mostrandoAnverso'
				if(celdaObtenerMostrandoAnverso(obtenerTablero(j), z, i))
					entornoFichaAnverso(i, z, celdaObtenerValor(obtenerTablero(j), z, i));
				else
					entornoFichaReves(i, z);
			}else if(celdaObtenerValor(obtenerTablero(j), z, i) != VALOR_PREDEFINIDO){ //Elimina las fichas que fueron borradas de la memoria del tablero
				entornoBorrarCelda(i, z);
			}
		}
	}
}

void juegoInsertarFila(Juego &j){
	insertarFila(obtenerTablero(j), time(NULL)); 					//El timepo del sistema como semilla

	/*
	 * Hace que aparezca una fila de fichas mostrando el reverso en la parte superior del tablero
	 * 		y después de un pequeño retraso desaparece para hacer la ilusión de que cae hacia abajo
	 */
	for(int i=0; i<obtenerTamanoTablero(obtenerTablero(j)); i++){
		entornoFichaReves(0, i);
	}
	entornoPausa(TIEMPO_INSERCION_FILA); 							//Retraso antes del borrado de la fila
	for(int i=0; i<obtenerTamanoTablero(obtenerTablero(j)); i++){
		entornoBorrarCelda(0, i);
	}

	actualizarEntorno(j);
}

Tablero& obtenerTablero(Juego &j){
	return j.t;
}

int& obtenerPuntuacion(Juego &j){
	return j.puntuacion;
}

int obtenerTiempoJugada(Juego j){
	return j.tiempoJugada;
}

int obtenerPuntosPista(Juego j){
	return j.puntosPista;
}

void juegoEliminarFicha(Juego &j, int pos_x, int pos_y){
	if(!celdaObtenerEstaVacia(obtenerTablero(j), pos_x, pos_y)){ 	//Si la celda esta vacia no hace nada
		eliminarFicha(obtenerTablero(j), pos_x, pos_y);
		actualizarEntorno(j);
	}
}

void juegoFichaVoltear(Juego &j, int pos_x, int pos_y){
	if(!celdaObtenerEstaVacia(obtenerTablero(j), pos_x, pos_y)){ 	//Si la celda esta vacia no hace nada
		if(fichaVoltear(obtenerTablero(j), pos_x, pos_y)){ 			//Animación de volteado de la ficha
			entornoFichaCanto(pos_y, pos_x);
			entornoPausa(TIEMPO_TRANSICION_ESTADOS);
			entornoFichaAnverso(pos_y, pos_x, celdaObtenerValor(obtenerTablero(j), pos_x, pos_y));
		}else{
			entornoFichaCanto(pos_y, pos_x);
			entornoPausa(TIEMPO_TRANSICION_ESTADOS-0.15); 			//La animación de ANVERSO a REVERSO es más corta
			entornoFichaReves(pos_y, pos_x);
		}
	}
}

int main(){															//PROGRAMA PRINCIPAL
	Juego j;														//Instancia principal del juego

	//Llamada a todas las pruebas
	//pruebas();
	cargarJuego(j);													//Llamada a comenzar de la partida
}
