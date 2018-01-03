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

/*
 * Punto de entrada del programa. Llama a todas las pruebas y carga la configuración
 * 	inicial para iniciar el entorno gráfico. Si se realiza correctamente llama al
 * 	siguiente módulo 'manejadorJuego()'.
 */
int main();


/*
 * Módulo que maneja toda la lógica del juego: entorno gráfico, entrada del usuario,
 * 	manejo del tablero, del cronómetro, de la puntuación y de la finalización de la
 * 	partida. Una vez la partida acabe se llama al módulo 'terminarJuego()' para terminar
 * 	el entorno gráfico y liberar los recursos asociados.
 */
void manejadorJuego();


/*
 * Módulo que termina el entorno gráfico y libera los recursos asociados. También da
 * 	un mensaje de despedida con la puntuación obtenida.
 */
void terminarJuego();

#endif /* JUEGO_H_ */
