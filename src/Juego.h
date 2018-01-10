/*
 * Juego.h
 * Autor: Juan Pablo García Plaz Pérez (jgarciapft)
 *
 * Descripción: TAD que maneja el la lógica del juego, la puntuación
 * 					y el entorno gráfico
 *
 */

#ifndef JUEGO_H_
#define JUEGO_H_

#include "Tablero.h"

const int FILAS_INICIALES = 2;
const int PTOS_PAREJA = 10; 					//Ptos obtenidos al hacer pareja
const int PTOS_FINAL_TABLERO_VACIO = 50; 		//Ptos de bonificación por vaciar el tablero
const float TIEMPO_TRANSICION_ESTADOS = 0.25; 	//Retraso entre estados de la animación de voltear fichas
const float TIEMPO_RETRASO_SELECCION = 0.5; 	//Tiempo que se le deja al jugador ver el anverso de ambas fichas
const float TIEMPO_PAUSA_FINAL = 2; 			//Tiempo que se le deja al jugador ver el mensaje final
const float TIEMPO_PISTA_1 = 0.75;				//Tiempo que muestran el reverso todas las fichas al activarse la pista 1
const float TIEMPO_PISTA_2 = 0.25;				//Tiempo que dura la animación de cada volteado de ficha para la pista 2

/*
 * PRE:
 * POST: Punto de entrada del programa. Llama a todas las pruebas y carga la configuración
 * 			inicial para iniciar el entorno gráfico. Si se realiza correctamente llama al
 * 			siguiente módulo 'manejadorJuego()'.
 * 	COMPLEJIDAD: O(1) .Sin contar las pruebas
 */
int main();


/*
 * PRE:
 * POST: Módulo que maneja toda la lógica del juego: entrada del usuario, manejo del tablero,
 *  		manejo del cronómetro, de la puntuación y de la finalización de la partida.
 * 			Una vez la partida acabe se llama al módulo 'terminarJuego()'.
 * 	COMPLEJIDAD: 0(n)
 */
void manejadorJuego();


/*
 * PRE:
 * POST: Módulo que termina el entorno gráfico y libera los recursos asociados. También da
 * 			un mensaje de despedida con la puntuación obtenida.
 * 	COMPLEJIDAD: O(1)
 */
void terminarJuego();


/*
 * PRE:
 * POST: Módulo para actualizar el entorno gráfico del tablero
 * COMPLEJIDAD: 0(n²)
 */
void actualizarEntorno(Tablero &t);


/*
 * PRE: Cabe una fila más en el Tablero 't'
 * POST: Módulo que insertar una fila en el tablero y actualiza el entorno grafico
 * COMPLEJIDAD: O(n*n²) .Por actualizarEntorno()
 */
void juegoInsertarFila(Tablero &t);


/*
 * PRE: 'pos_x' y 'pos_y' dentro de los límites del Tablero t
 * POST: Módulo que elimina la ficha de la posición ('pos_x', 'pos_y') y actualiza el entorno gráfico
 * COMPLEJIDAD: O(n*n²) .Por actualizarEntorno()
 */
void juegoEliminarFicha(Tablero &t, int pos_x, int pos_y);


/*
 * PRE: pos_x' y 'pos_y' dentro de los límites del Tablero t
 * POST: Módulo que voltea la ficha de la posición ('pos_x', 'pos_y') y actualiza el entorno gráfico
 * COMPLEJIDAD: O(1*n²) .Por actualizarEntorno()
 */

void juegoFichaVoltear(Tablero &t, int pos_x, int pos_y);

#endif /* JUEGO_H_ */
