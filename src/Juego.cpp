/*
 * Juego.cpp
 * Autor: jgarciapft
 *
 */

#include "Juego.h"
#include "entorno.h"
#include "pruebas.h"

int tamanoTablero;  				//guardará el número de filas y columnas del tablero, rol: valor fijo
int tiempoJugada;   				//guardará el tiempo de una jugada, rol: valor fijo
int puntosPista; 					//guardara el número de puntos que se restan en algunas ampliaciones, rol: valor fijo
int seg;	  						//almacena los segundos del cronometro, rol: más reciente
int puntuacion;						//almacena la puntuación
string mensaje;  					//almacena los diferentes mensajes que aparecen durante la ejecucion, rol: valor fijo
bool salir;							//controla la salida del bucle, rol: bandera
TipoTecla tecla;					//almacena las teclas pulsadas, rol: mas reciente
int pos_x, pos_y;					//almacena la posición de la celda seleccionada, rol: transformación
int sel_x1, sel_y1, sel_x2, sel_y2; //almacenan las posiciones de las dos fichas seleccionadas
int seleccionadas;					//almacena el numero de fichas seleccionadas
Tablero t;							//almacena el tablero en memoria

int main() { //cargarJuego()
	//Llamada a todas las pruebas
	//pruebas();

	//Carga la configuración e inicia el Tablero
	if(entornoCargarConfiguracion(tamanoTablero,tiempoJugada,puntosPista)){
		if(entornoIniciar(tamanoTablero)){
			iniciarTablero(t, tamanoTablero);
			manejadorJuego();
		}
	}
}

//v1.2
void manejadorJuego() {
	/*
	 * INICIALIZACIÓN
	 */
	salir = false;
	puntuacion = 0;
	seg = 0; //se inician los segundos del cronómetro
	for(int i=0; i<FILAS_INICIALES; i++){ //inserta un número de filas iniciales en tablero
		juegoInsertarFila(t);
	}
	pos_x = 0;
	pos_y = tamanoTablero-1;
	entornoActivarCelda(pos_y, pos_x);
	entornoPonerPuntuacion(puntuacion);

	/*
	 * Bucle que mantiene el procesamiento de la lógica del juego
	 */
	while(!salir){
		/*
		 * Manejador de tiempo
		 */
		entornoTiempo(seg,tiempoJugada); //se actualizan y muestran los segundos del cronómetro
		if(seg == tiempoJugada){ //al llegar a 'tiempoJugada' segundos, el cronómetro se vuelve a iniciar
			seg = 0;
			if(cabeFila(t)) //Comprueba si cabe una fila adicional en el tablero
				juegoInsertarFila(t);
			else
				salir = true;
		}

		/*
		 * Manejador de entrada de usuario
		 */
		tecla = entornoLeerTecla();
		switch(tecla) {
			case TEnter:
				juegoFichaVoltear(t, pos_x, pos_y);
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
				juegoBorrarFicha(t, pos_x, pos_y);
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

		/*
		 * Manejador de final por vaciar tablero
		 */
		if(estaVacio(t))
			salir = true;
	}

	/*
	 * Manejador de final de juego
	 */
	if(salir)
		terminarJuego();
}

void terminarJuego() {
	if(estaVacio(t))
		puntuacion = puntuacion + PTOS_FINAL_TABLERO_VACIO;//Si la partida termina por vaciar el tablero se dan ptos extra
	mensaje = "             Puntuación final : " + toString(puntuacion) + " ptos";
	entornoMostrarMensajeFin(mensaje);
	entornoPausa(1);
	entornoTerminar();
}

//v1.0
void actualizarEntorno(Tablero &t){
	for(int i=0; i<obtenerTamanoTablero(t); i++){
		for(int j=0; j<obtenerTamanoTablero(t); j++){
			if(!celdaEstaVacia(t, j, i)){ //Muestra las fichas que deben estar del reves
				entornoFichaReves(i, j);
			}else if(celdaEstaVacia(t, j, i) && celdaObtenerValor(t, j, i) != VALOR_PREDEFINIDO){ //borra las fichas que fueron borradas de la memoria del tablero
				entornoBorrarCelda(i, j);
			}
		}
	}
}

//v1.0
void juegoInsertarFila(Tablero &t){
	insertarFila(t);
	actualizarEntorno(t);
}

//v1.1
void juegoBorrarFicha(Tablero &t, int pos_x, int pos_y){
	if(!celdaEstaVacia(t, pos_x, pos_y)){ //si la celda esta vacia no hace nada
		eliminarFicha(t, pos_x, pos_y);
		actualizarEntorno(t);
	}
}

//v1.1
void juegoFichaVoltear(Tablero &t, int pos_x, int pos_y){
	if(!celdaEstaVacia(t, pos_x, pos_y)){ //si la celda esta vacia no hace nada
		if(fichaVoltear(t, pos_x, pos_y)){
			entornoFichaCanto(pos_y, pos_x);
			entornoPausa(TIEMPO_TRANSICION_ESTADOS);
			entornoFichaAnverso(pos_y, pos_x, celdaObtenerValor(t, pos_x, pos_y));
		}else{
			entornoFichaCanto(pos_y, pos_x);
			entornoPausa(TIEMPO_TRANSICION_ESTADOS);
			entornoFichaReves(pos_y, pos_x);
		}
	}
}

//v1.1
bool juegoCompararFichas(Tablero t, int pos_x1, int pos_x2, int pos_y1, int pos_y2){
	bool iguales = false;
	if(!celdaEstaVacia(t, pos_x, pos_y)) //si la celda esta vacia devuelve false
		iguales = sonIguales(t.v[pos_y1][pos_x1], t.v[pos_y2][pos_x2]);
	return iguales;
}
