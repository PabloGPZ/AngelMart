/*
 * pruebas.cpp
 * Autor: Juan Pablo García Plaza Pérez (jgarciapft)
 *
 */

#include "entorno.h"
#include "pruebaCelda.h"
#include "pruebaTablero.h"
#include <iostream>

using namespace std;

void pruebasEntorno() {
	int tamanoTablero;  //guardará el número de filas y columnas del tablero, rol: valor fijo
	int tiempoJugada;   //guardará el tiempo de una jugada, rol: valor fijo
	int seg;	  		//almacena los segundos del cronometro, rol: más reciente
	int puntosPista; 	//guardara el número de puntos que se restan en algunas ampliaciones, rol: valor fijo
	string mensaje;  	//almacena los diferentes mensajes que aparecen durante la ejecucion, rol: valor fijo
	bool salir;			//controla la salida del bucle, rol: bandera
	TipoTecla tecla;	//almacena las teclas pulsadas, rol: mas reciente
	int fila, col;		//almacena la posición de la celda seleccionada, rol: transformación

	if(entornoCargarConfiguracion(tamanoTablero,tiempoJugada,puntosPista)){
			if(entornoIniciar(tamanoTablero)){
				mensaje = "Vamos a poner en el marcador una puntación igual a 100";
				entornoMostrarMensaje (Zona1,mensaje);
				entornoPonerPuntuacion(100);
				entornoPausa(2);

				mensaje = "Vamos a colocar tres fichas del derecho y dos del revés";
				entornoMostrarMensaje (Zona2,mensaje);
				mensaje = "La primera es un Bono (7), la segunda una Bomba (5), la última es normal";
				entornoMostrarMensaje (Zona3,mensaje);

				//Colocamos varias fichas sobre el tablero
				entornoFichaBono(6,1,7);
				entornoFichaBomba(6,3,5);
				entornoFichaReves(6,5);
				entornoFichaReves(6,7);
				entornoFichaAnverso(6,9,3);
				entornoPausa(3);

				mensaje = "Vamos a probar el desplazamiento por el tablero:";
				entornoMostrarMensaje (Zona1,mensaje);
				mensaje = "usa las flechas y, para salir, pulsa Escape";
				entornoMostrarMensaje (Zona2,mensaje);
				mensaje = "Probaremos el funcionamiento del cronómetro que se inicializa cada 10 seg.";
				entornoMostrarMensaje (Zona3,mensaje);


				//las siguentes instrucciones simulan el desplazamiento por el tablero
				//utilizando las teclas de movimiento: arriba, abajo, derecha e izquierda
				salir = false;
				fila = tamanoTablero-1;
				col = 0;
				entornoActivarCelda(fila, col);
				seg = 0; //se inician los segundos del cronómetro
				while(!salir){
						entornoTiempo(seg,10); //se actualizan y muestran los segundos del cronómetro
						if(seg == 10){    //al llegar a 10 segundos, el cronómetro se vuelve a iniciar
							seg = 0;
						}

						tecla = entornoLeerTecla();
						switch(tecla) {
							case TEnter:
								break;
							case TDerecha:
								entornoDesactivarCelda(fila, col);
								if (col < tamanoTablero - 1)
									col++;
								entornoActivarCelda(fila, col);
								break;
							case TIzquierda:
								entornoDesactivarCelda(fila, col);
								if (col > 0)
									col--;
								entornoActivarCelda(fila, col);
								break;
							case TArriba:
								entornoDesactivarCelda(fila, col);
								if (fila > 0)
									fila--;
								entornoActivarCelda(fila, col);
								break;
							case TAbajo:
								entornoDesactivarCelda(fila, col);
								if (fila < tamanoTablero - 1)
									fila++;
								entornoActivarCelda(fila, col);
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
							} //acaba el switch
				}// acaba el while

				mensaje = "                 ¡¡¡Adios!!!";
				entornoMostrarMensajeFin(mensaje);
				entornoPausa(1);
				entornoTerminar();

			}
		}
}

void pruebas(){
	pruebasEntorno();
	pruebasTADCelda();
	pruebasTADTablero();
}
