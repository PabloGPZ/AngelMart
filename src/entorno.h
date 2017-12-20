/**

	INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
	Curso 2017/2018

	Nombre: entorno.h
	Descripción: Especificación del TAD Entorno para el proyecto Angel Mart
	     	 	 Encargado del manejo de la interfaz del juego.
	     	 	 versión allegro 5
	Autor:	Profesores de las asignaturas
	Fecha:  11/11/2017

*/

#ifndef ENTORNO_H_
#define ENTORNO_H_

#include <string>
using namespace std;
// -------------------------------------------------------------
// Definición de constantes públicas
// -------------------------------------------------------------


// Dimensiones máximas  del tablero
const int MAXTAMANO	= 10;


// -------------------------------------------------------------
// Definicion de tipos
// -------------------------------------------------------------

/**
 *   Este es el tipo devuelto por la operacion LeerTecla que indica la tecla
 *   de los cursores o teclas válidas que se ha pulsado
 */
enum TipoTecla{TNada, TEnter, TIzquierda, TDerecha, TArriba, TAbajo, TSalir,  TX, TY, TZ};


/**
 *   Zonas en el entorno para imprimir mensajes. Existen 3 zonas delimitadas para imprimir un
 *   mensaje en la pantalla del entorno. Se pueden usar para imprimir mensajes de estado de
 *   diferentes tipos
 */
enum TipoZona{Zona1, Zona2, Zona3};


// -------------------------------------------------------------
// Declaración de la interfaz de los módulos públicos
// -------------------------------------------------------------


 /*
  *	PRE:  4 <= tam <= MAXTAMANO, tam debe ser un número par
  *	POST: Inicia la pantalla de juego, incluyendo una rejilla cuadrada de tam*tam
  *	      Si este inicio del entorno gráfico se realiza correctamente, devuelve "true",
  *	      en caso contrario, devuelve "false"
  */
bool entornoIniciar(int tam);


 /*
  *	POST: Libera los recursos usados por el entorno gráfico
  */
void entornoTerminar();


 /*
  *	PRE: Archivo AngelMart.cnf correcto y en la carpeta raíz del proyecto
  *	     (NO SE COMPRUEBAN ERRORES EN LOS DATOS)
  *	POST: Devuelve:
  *	         TRUE:  si se carga correctamente la configuración del juego,
  *		     FALSE: en caso contrario.
  *   PARÁMETROS:
  *		Si la configuración se lee de forma correcta, devuelve "true" y además se devolverá:
  *		   tamano:		  número de filas y columnas del tablero
  *		   tiempo:        segundos que deben transcurrir antes de que aparezca una nueva fila
  *		   ptosARestar:   puntos a restar por el uso de la pista
  *		Si el fichero no existe, devuelve "false"
  *		Por omisión, el archivo AngelMart.cnf se encuentra en el directorio  del proyecto
  */
bool entornoCargarConfiguracion(int &tamano, int &tiempo, int &ptosARestar);


 /*
  * PRE: { 0 <= fila < MAXTAMANO }
  *      { 0 <= columna < MAXTAMANO}
  * POST: Muestra en la celda que se encuentra en la posición (fila,columna) el reverso de una ficha
  */
void entornoFichaReves(int fila, int columna);


/*
  * PRE: { 0 <= fila < MAXTAMANO }
  *      { 0 <= columna < MAXTAMANO}
  *      { 0 <= numero <= 9}
  * POST: Muestra en la celda que se encuentra en la posición (fila,columna) el anverso de una ficha con el numero indicado
  */
void entornoFichaAnverso(int fila, int columna, int numero);

/*
  * PRE: { 0 <= fila < MAXTAMANO }
  *      { 0 <= columna < MAXTAMANO}
  * POST: Muestra en la celda que se encuentra en la posición (fila,columna) el canto de una ficha.
  *       Se utiliza para dar sensación de movimiento al darle la vuelta a una ficha
  */
void entornoFichaCanto(int fila, int columna);


/*
  * PRE: { 0 <= fila < MAXTAMANO }
  *      { 0 <= columna < MAXTAMANO}
  *      { 0 <=  numero <= 9}
  * POST: Muestra en la celda que se encuentra en la posición (fila,columna) el anverso de una ficha con el numero indicado
  *       El número aparece en color rojo para indicar que es una ficha especial (bono)
  *       Solo se utilizará en el caso de realizar la ampliación "Bonos y bombas"
  */
void entornoFichaBono(int fila, int columna, int numero);


/*
  * PRE: { 0 <= fila < MAXTAMANO }
  *      { 0 <= columna < MAXTAMANO}
  *      { 0 <=  numero <= 9}
  * POST: Muestra en la celda que se encuentra en la posición (fila,columna) el anverso de una ficha con el numero indicado
  *       El número aparece en rojo con fondo de color negro para indicar que es una ficha especial (bomba)
  *       Solo se utilizará en el caso de realizar la ampliación "Bonos y bombas"
  */
void entornoFichaBomba(int fila, int columna, int numero);


/*
  *	PRE:  0 <= fila < MAXTAMANO,
  * PRE:  0 <= columna < MAXTAMANO,
  * POST: Borra la ficha que se encuentra en la posición (fila, columna)
  */
void entornoBorrarCelda(int fila, int columna);


  /*
   * PRE:  0 <= fila < MAXTAMANIO,
   * PRE:  0 <= columna < MAXTAMANIO,
   * POST: Enmarca la celda que ocupa la posición (fila, columna) con un borde rojo
   */
void entornoActivarCelda(int fila, int columna);


  /*
   * PRE:  0 <= fila < MAXTAMANIO,
   * PRE:  0 <= columna < MAXTAMANIO,
   * POST: Elimina el marco de la celda que ocupa la posición (fila, columna)
   */
void entornoDesactivarCelda(int fila, int columna);


  /*
   * PRE:
   * POST: Muestra la puntuación, indicada por el parámetro "valor",
   *       en el marcador situado encima de la cuadrícula
   */
void entornoPonerPuntuacion(int valor);


 /*
  * POST:Devuelve un valor enumerado de TipoTecla con la tecla que se ha pulsado
  */
TipoTecla entornoLeerTecla();


 /*
  * PRE: 	{zona pertenece al conjunto {Zona1, Zona2, Zona3}}
  * POST:	Escribe el mensaje, indicado por el parámetro msg, en el lugar de la pantalla indicado por zona
  */
void entornoMostrarMensaje(TipoZona zona, string msg);


 /*
  * POST: Muestra el mensaje "msg" en el centro de la rejilla para indicar que ha finalizado el juego
  */
void entornoMostrarMensajeFin(string msg);


 /*
  * PRE: 0 < pausa  (tiempo en segundos que dura la pausa)
  * POST: lleva a cabo una pausa en la ejecución del juego,
  *       puede utilizarse para ralentizar algún movimiento sobre el tablero
  */
void entornoPausa(float pausa);


 /* PRE:
  * POST: convierte un número, indicado por el parámetro "numero", en una cadena de caracteres
  */
string toString(int numero);


/* PRE:  contador > 0, seg >=0
 * POST: actualiza, en tiempo real, el parámetro "seg" a modo de cronómetro, con los segundos transcurridos,
 *       y además, muestra este valor en el entorno, sobre la rejilla.
 *       Cuando el número de segundos transcurridos coincide con "contador"
 *       el número de segundos se muestra en color rojo.
 */
void entornoTiempo(int &seg, int contador);

#endif
