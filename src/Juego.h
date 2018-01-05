/*
 * Juego.h
 * Autor: jgarciapft
 *
 * Descripción: TAD que maneja el la lógica del juego, la puntuación
 * 					y el entorno gráfico
 *
 */

#ifndef JUEGO_H_
#define JUEGO_H_

#include "Tablero.h"

const int FILAS_INICIALES = 2;
const int PTOS_PAREJA = 10; //ptos obtenidos al hacer pareja
const int PTOS_FINAL_TABLERO_VACIO = 50; //ptos de bonificación por vaciar el tablero
const float TIEMPO_TRANSICION_ESTADOS = 0.5;

/*
 * Punto de entrada del programa. Llama a todas las pruebas y carga la configuración
 * 	inicial para iniciar el entorno gráfico. Si se realiza correctamente llama al
 * 	siguiente módulo 'manejadorJuego()'.
 */
int main();


/*
 * Módulo que maneja toda la lógica del juego: entrada del usuario, manejo del tablero,
 *  manejo del cronómetro, de la puntuación y de la finalización de la partida.
 * 	Una vez la partida acabe se llama al módulo 'terminarJuego()' para terminar
 * 	el entorno gráfico y liberar los recursos asociados.
 */
void manejadorJuego();


/*
 * Módulo que termina el entorno gráfico y libera los recursos asociados. También da
 * 	un mensaje de despedida con la puntuación obtenida.
 */
void terminarJuego();


/*
 * Módulo para actualizar el entorno gráfico del tablero
 */
void actualizarEntorno(Tablero &t);


/*
 * Módulo que insertar una fila en el tablero y actualiza el entorno grafico
 */
void juegoInsertarFila(Tablero &t);


/*
 * Módulo que borra una ficha y actualiza el entorno gráfico
 */
void juegoBorrarFicha(Tablero &t, int pos_x, int pos_y);


/*
 * Módulo que voltea una ficha y actualiza el entorno gráfico
 */

void juegoFichaVoltear(Tablero &t, int pos_x, int pos_y);


/*
 * Módulo que compara dos fichas del tablero y devuelve si son iguales o no
 */
bool juegoCompararFichas(Tablero t, int pos_x1, int pos_x2, int pos_y1, int pos_y2);

#endif /* JUEGO_H_ */
