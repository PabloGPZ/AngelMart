/*
 * Juego.cpp
 * Autor: jgarciapft
 *
 */

#include "Juego.h"
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

			manejadorJuego();
		}
	}
}

//v1.1
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

	while(!salir){
		/*
		 * Manejador de tiempo
		 */
		entornoTiempo(seg,tiempoJugada); //se actualizan y muestran los segundos del cronómetro
		if(seg == tiempoJugada){ //al llegar a 'tiempoJugada' segundos, el cronómetro se vuelve a iniciar
			seg = 0;
		}

		/*
		 * Manejador de entrada de usuario
		 */
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
			if(!celdaEstaVacia(t, j, i)){
				entornoFichaReves(i, j);
			}else if(celdaEstaVacia(t, j, i) && celdaObtenerValor(t, j, i) != VALOR_PREDEFINIDO){
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

//v1.0
void juegoBorrarFicha(Tablero &t, int pos_x, int pos_y){
	eliminarFicha(t, pos_x, pos_y);
	actualizarEntorno(t);
}

//v1.0
void juegoFichaVoltear(Tablero &t, int pos_x, int pos_y){
	if(fichaVoltear(t, pos_x, pos_y)){
		entornoFichaCanto(pos_y, pos_x);
		entornoPausa(1);
		entornoFichaAnverso(pos_y, pos_x, celdaObtenerValor(t, pos_x, pos_y));
	}else{
		entornoFichaCanto(pos_y, pos_x);
		entornoPausa(1);
		entornoFichaReves(pos_y, pos_x);
	}
}

//v1.0
bool juegoCompararFichas(Tablero t, int pos_x1, int pos_x2, int pos_y1, int pos_y2){
	return sonIguales(t.v[pos_y1][pos_x1], t.v[pos_y2][pos_x2]);
}
