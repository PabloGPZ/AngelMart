/*
 * Juego.cpp
 * Autor: jgarciapft
 *
 */

#include "Juego.h"
#include "Tablero.h"
#include "entorno.h"
#include "pruebas.h"

int tamanoTablero;  //guardará el número de filas y columnas del tablero, rol: valor fijo
int tiempoJugada;   //guardará el tiempo de una jugada, rol: valor fijo
int puntosPista; 	//guardara el número de puntos que se restan en algunas ampliaciones, rol: valor fijo
int seg;	  		//almacena los segundos del cronometro, rol: más reciente
int puntuacion;		//almacena la puntuación
string mensaje;  	//almacena los diferentes mensajes que aparecen durante la ejecucion, rol: valor fijo
bool salir;			//controla la salida del bucle, rol: bandera
TipoTecla tecla;	//almacena las teclas pulsadas, rol: mas reciente
int pos_x, pos_y;	//almacena la posición de la celda seleccionada, rol: transformación
Tablero t;			//almacena el tablero en memoria

int main() { //cargarJuego()
	//Llamada a todas las pruebas
	//pruebas();

	//Carga la configuración e inicia el Tablero
	if(entornoCargarConfiguracion(tamanoTablero,tiempoJugada,puntosPista)){
		if(entornoIniciar(tamanoTablero)){
			iniciarTablero(t, tamanoTablero);
			for(int i=0; i<FILAS_INICIALES; i++){ //inserta un número de filas iniciales en tablero
				insertarFila(t);
			}
			manejadorJuego();
		}
	}
}

//v1.1
void manejadorJuego() {
	/*
	 * Las siguentes instrucciones simulan el desplazamiento por el tablero
	 * utilizando las teclas de movimiento: arriba, abajo, derecha e izquierda
	 */
	salir = false;
	puntuacion = 0;
	pos_x = 0;
	pos_y = tamanoTablero-1;
	entornoPonerPuntuacion(puntuacion);
	entornoActivarCelda(pos_y, pos_x);
	seg = 0; //se inician los segundos del cronómetro

	while(!salir){
		entornoTiempo(seg,tiempoJugada); //se actualizan y muestran los segundos del cronómetro
		if(seg == tiempoJugada){ //al llegar a 'tiempoJugada' segundos, el cronómetro se vuelve a iniciar
			seg = 0;
		}

		tecla = entornoLeerTecla();
		switch(tecla) {
			case TEnter:
				break;
			case TDerecha:
				entornoDesactivarCelda(pos_y, pos_x);
				if (pos_x < tamanoTablero - 1)
					pos_x++;
				entornoActivarCelda(pos_y, pos_x);
				break;
			case TIzquierda:
				entornoDesactivarCelda(pos_y, pos_x);
				if (pos_x > 0)
					pos_x--;
				entornoActivarCelda(pos_y, pos_x);
				break;
			case TArriba:
				entornoDesactivarCelda(pos_y, pos_x);
				if (pos_y > 0)
					pos_y--;
				entornoActivarCelda(pos_y, pos_x);
				break;
			case TAbajo:
				entornoDesactivarCelda(pos_y, pos_x);
				if (pos_y < tamanoTablero - 1)
					pos_y++;
				entornoActivarCelda(pos_y, pos_x);
				break;
			case TX:
				break;
			case TY:
				break;
			case TZ:
				break;
			case TSalir:
				salir = true;
				break;
			case TNada:
				break;
		}
	}
	if(salir)
		terminarJuego();
}

void terminarJuego() {
	mensaje = "             Puntuación final : " + toString(puntuacion) + " ptos";
	entornoMostrarMensajeFin(mensaje);
	entornoPausa(1);
	entornoTerminar();
}
